-- Hubert Jastrzębski | Satori I (Stare kolokwium) | 2025-05-26
-- https://satori.tcs.uj.edu.pl/contest/9744410/problems/9994155
--ZAD1
SELECT status, COUNT(*) AS liczba_zadan
FROM checks
GROUP BY status;
----
--ZAD2
WITH max_costs AS (
    SELECT DISTINCT ON (p1.problem_id, t1.task_id) p1.problem_id, t1.task_id, cost
    FROM problems p1
    LEFT JOIN tasks t1 ON p1.problem_id = t1.problem_id
    LEFT JOIN checks c1 ON t1.task_id = c1.task_id AND c1.status = 'OK'
    ORDER BY p1.problem_id, t1.task_id, c1.cost IS NULL, split_part(c1.cost, '-', 1)::numeric DESC,
             split_part(c1.cost, '-', 2)::numeric DESC
)
SELECT p.short_name, t.task_name, max_costs.cost AS "max_cost", COUNT(c.status) AS "liczba_rozwiazan"
FROM max_costs
LEFT JOIN problems p ON p.problem_id = max_costs.problem_id
LEFT JOIN tasks t ON p.problem_id = t.problem_id AND t.task_id = max_costs.task_id
LEFT JOIN checks c ON c.task_id = t.task_id AND (c.cost = max_costs.cost OR (c.cost IS NULL AND max_costs.cost IS NULL)) AND c.status = 'OK'
GROUP BY p.problem_id, t.task_id, max_costs.cost;
----
--ZAD3
WITH user_tasks AS (
    SELECT users.user_id, users.name, tasks.task_id, COALESCE(MAX(score), 0) AS "task_score", tasks.max_score
    FROM users
    CROSS JOIN tasks
    LEFT JOIN submits ON users.user_id = submits.user_id
    LEFT JOIN checks ON checks.submit_id = submits.submit_id AND checks.task_id = tasks.task_id
    GROUP BY users.user_id, tasks.task_id
), user_problems AS (
    SELECT user_tasks.user_id, problems.problem_id, SUM(user_tasks.task_score)::float / SUM(tasks.max_score)::float * 100.0 AS "problem_score"
    FROM user_tasks
    LEFT JOIN tasks ON user_tasks.task_id = tasks.task_id
    LEFT JOIN problems ON problems.problem_id = tasks.problem_id
    GROUP BY user_tasks.user_id, problems.problem_id
)
SELECT name, ROUND(SUM(user_problems.problem_score)::numeric, 2)
FROM user_problems
JOIN users ON user_problems.user_id = users.user_id
GROUP BY users.user_id;
----
--ZAD4
CREATE OR REPLACE FUNCTION collatz(n numeric)
    RETURNS numeric
    LANGUAGE plpgsql
AS
$$
DECLARE
    result numeric;
BEGIN
    result := 0;
    WHILE n > 1 LOOP
        IF mod(n, 2) = 0 THEN
            n := n / 2;
        ELSE
            n := 3 * n + 1;
        END IF;
        result := result + 1;
    END LOOP;
    RETURN result;
END;
$$;
----
--ZAD5
CREATE OR REPLACE FUNCTION wstrzymane_uprawnienia(zadana_data date)
    RETURNS table(pesel character(11), imie character varying, nazwisko character varying, data date)
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY (SELECT ogup.pesel, k.imie, k.nazwisko, MAX(ogup.od)
    FROM ograniczenia_uprawnien ogup
    JOIN kierowcy k ON ogup.pesel = k.pesel
    WHERE ogup.od <= zadana_data AND ogup.do >= zadana_data
    GROUP BY ogup.pesel, k.imie, k.nazwisko);
END;
$$;
--ZAD6
CREATE OR REPLACE FUNCTION mandaty_check()
    RETURNS trigger
    LANGUAGE plpgsql
AS $$
DECLARE
    punkty_suma numeric;
BEGIN
    SELECT SUM(punkty) INTO punkty_suma
        FROM mandaty m
        JOIN wykroczenia wyk ON m.id_wykroczenia = wyk.id
        WHERE data >= NEW.data - (interval '1 year') AND pesel = NEW.pesel;

    IF punkty_suma >= 24 THEN
        INSERT INTO ograniczenia_uprawnien(pesel, od, "do", podstawa_prawna)
            VALUES(NEW.pesel, NEW.data, NEW.data + interval '3 months' - interval '1 day', NULL);
    END IF;
    return NEW;
END;
$$;

CREATE OR REPLACE TRIGGER mandaty_check AFTER INSERT ON mandaty
FOR EACH ROW EXECUTE PROCEDURE mandaty_check();
----