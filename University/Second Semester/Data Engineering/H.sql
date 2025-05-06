-- Hubert Jastrzębski | Satori H (Sekwencje, widoki i PL/pgSQL) | 2025-05-06
-- https://satori.tcs.uj.edu.pl/contest/9744410/problems/9980754
--zad1
CREATE SEQUENCE seq MINVALUE 10 MAXVALUE 99 INCREMENT 1;
----
--zad2
INSERT INTO klienci(id, imie, nazwisko)
VALUES(nextval('seq'), 'Anna', 'Kowalska');
INSERT INTO klienci(id, imie, nazwisko)
VALUES(nextval('seq'), 'Jan', 'Kowalski');
----
--zad3
CREATE UNIQUE INDEX
    ON transakcje (z_konta, na_konto, data_zlecenia);
----
--zad4
--zad5
CREATE OR REPLACE VIEW wplaty_wyplaty AS
    WITH wyplaty AS (
        SELECT nr_konta, COUNT(transakcje.id)
        FROM konta
        JOIN transakcje ON z_konta = nr_konta
        GROUP BY nr_konta),
    wplaty AS (
        SELECT nr_konta, COUNT(transakcje.id)
        FROM konta
        JOIN transakcje ON na_konto = nr_konta
        GROUP BY nr_konta)
SELECT nr_konta AS "Konto", COALESCE(wyplaty.count, 0) AS "Ilosc wyplat", COALESCE(wplaty.count, 0) AS "Ilosc wplat"
FROM konta
         LEFT JOIN wyplaty USING (nr_konta)
         LEFT JOIN wplaty USING (nr_konta);
----
--zad5
SELECT * FROM wplaty_wyplaty;
INSERT INTO transakcje(id, data_zlecenia, z_konta, na_konto, kwota)
VALUES(200, DEFAULT, null, 1004, 500);
SELECT * FROM wplaty_wyplaty;
DROP VIEW wplaty_wyplaty;
----
--zad6
--zad7
CREATE FUNCTION oblicz_koszt(a numeric(11, 2))
    returns numeric(11, 2)
    language plpgsql
  as
$$
begin
return ROUND(0.02 * a, 2);
end;
$$;
----
--zad7
SELECT oblicz_koszt(kwota)
FROM transakcje;
----
--zad8
--zad9
--zad11
CREATE FUNCTION bilans_kont()
    returns table(konto numeric(11),
                  suma_wplat numeric(11, 2),
                  suma_wyplat numeric(11, 2))
    language plpgsql
  as
$$
begin
return query
    WITH wyplaty AS (
            SELECT nr_konta, SUM(transakcje.kwota)
            FROM konta
            JOIN transakcje ON z_konta = nr_konta
            GROUP BY nr_konta),
        wplaty AS (
            SELECT nr_konta, SUM(transakcje.kwota)
            FROM konta
            JOIN transakcje ON na_konto = nr_konta
            GROUP BY nr_konta)
SELECT nr_konta AS "Konto", COALESCE(wplaty.sum, 0), COALESCE(wyplaty.sum, 0)
FROM konta
         LEFT JOIN wyplaty USING (nr_konta)
         LEFT JOIN wplaty USING (nr_konta);
end;
$$;
----
--zad9
SELECT konto, suma_wplat - suma_wyplat AS "bilans"
FROM bilans_kont();
----
--zad10a
CREATE FUNCTION silnia(a numeric)
    returns numeric
    language plpgsql
  as
$$
declare
i numeric;
    res numeric;
begin
    res := 1;
for i IN 1..a loop
        res := res * i;
end loop;
return res;
end;
$$;
----
--zad10b
CREATE FUNCTION silnia(a numeric)
    returns numeric
    language plpgsql
  as
$$
begin
    IF a <= 1 THEN
        return 1;
END IF;
return a * silnia(a - 1);
end;
$$;
----
--zad11
CREATE SEQUENCE seq MINVALUE 1000 MAXVALUE 5000 INCREMENT 10;

CREATE FUNCTION bonus_swiateczny(p numeric DEFAULT 0.01)
    returns void
    language plpgsql
  as
$$
declare
r RECORD;
begin
FOR r IN SELECT * FROM bilans_kont() loop
    INSERT INTO transakcje (id, data_zlecenia, z_konta, na_konto, kwota)
         VALUES (nextval('seq'), now(), null, r.konto, p * r.suma_wyplat);
end loop;
end;
$$;
----
--zad12
--zad13
--zad14
CREATE OR REPLACE FUNCTION stan_konta(konto numeric(11), czas timestamp)
    returns numeric
    language plpgsql
  AS
$$
DECLARE
r record;
    res numeric;
BEGIN
    res := 0;
FOR r IN (SELECT * FROM transakcje WHERE (z_konta = konto OR na_konto = konto) ORDER BY data_zlecenia) LOOP
        EXIT WHEN r.data_zlecenia > czas;
        IF r.z_konta = konto THEN
            res := res - r.kwota;
            IF res < 0 THEN
                RAISE EXCEPTION 'Wykryto ujemny bilans konta';
END IF;
ELSE
            res := res + r.kwota;
END IF;
END LOOP;
return res;
END;
$$;
----
--zad13
CREATE OR REPLACE FUNCTION historia_konta(konto numeric(11))
    returns table(data timestamp, stan numeric(11, 2))
    language plpgsql
  AS
$$
DECLARE
r record;
BEGIN
return query(
    SELECT data_zlecenia, stan_konta(konto, data_zlecenia)
            FROM transakcje
        WHERE (z_konta = konto OR na_konto = konto)
        ORDER BY data_zlecenia
       );
END;
$$;
----
--zad14
CREATE OR REPLACE FUNCTION moment_rozspojniajacy()
    returns timestamp
    language plpgsql
  AS
$$
DECLARE
r record;
BEGIN
FOR r IN (SELECT * FROM transakcje ORDER BY data_zlecenia) LOOP
BEGIN
            PERFORM stan_konta(r.z_konta, r.data_zlecenia);
            PERFORM stan_konta(r.na_konto, r.data_zlecenia);
EXCEPTION
            WHEN OTHERS THEN
                RETURN r.data_zlecenia;
END;
END LOOP;
RETURN null;
END;
$$;
----