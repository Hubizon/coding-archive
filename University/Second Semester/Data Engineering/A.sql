-- Hubert Jastrzębski | Satori A (Proste zapytania) | 2025-03-14
-- https://satori.tcs.uj.edu.pl/contest/9744410/problems/9768181
--ZAD1
SELECT *
FROM kierowcy;
----
--ZAD2
SELECT *
FROM wykroczenia
ORDER BY kwota, nazwa;
----
--ZAD3
SELECT imie, nazwisko
FROM kierowcy;
----
--ZAD4
SELECT imie, nazwisko
FROM kierowcy
GROUP BY imie, nazwisko
ORDER BY nazwisko, imie DESC;
----
--ZAD5
SELECT imie, nazwisko, wynagrodzenie * 12
FROM straznicy;
----
--ZAD6
SELECT imie, nazwisko, (wynagrodzenie + COALESCE(premia, 0)) * 12
FROM straznicy;
----
--ZAD7
SELECT *
FROM straznicy
WHERE wynagrodzenie >= 6000 AND wynagrodzenie <= 8000;
----
--ZAD8
SELECT *
FROM straznicy
WHERE wynagrodzenie > 6000 AND id_przelozonego IS NOT NULL;
----
--ZAD9
SELECT *
FROM wykroczenia
WHERE punkty < 10 OR punkty IS NULL
ORDER BY id;
----
--ZAD10
SELECT *
FROM kierowcy
WHERE DATE_PART('year', data_od) > 2000;
----
--ZAD11
SELECT *
FROM wykroczenia
WHERE nazwa LIKE '%Przekroczenie prędkości%'
ORDER BY id;
----
--ZAD12
SELECT *
FROM kierowcy
WHERE adres LIKE '%Grudziądz' AND data_do IS NULL
ORDER BY id;
----
--ZAD13
SELECT imie, nazwisko, adres
FROM kierowcy
WHERE data_od <= '2012-01-01' AND (data_do >= '2012-01-01' OR data_do IS NULL)
ORDER BY imie, nazwisko;
----
--ZAD14
SELECT imie || ' ' || LEFT(nazwisko, 1) || '.' AS "kierowca_bez_uprawnien"
FROM kierowcy
WHERE data_do IS NOT NULL AND data_do <= '2025-03-14'
ORDER BY id;
----
--ZAD15
SELECT FORMAT('%s pracuje jako %s i zarabia %s', nazwisko, LOWER(stanowisko), wynagrodzenie) AS "STRAŻNICY MIEJSCY"
FROM straznicy;
----
--ZAD16
SELECT nazwisko, ROUND(wynagrodzenie * 1.15)
FROM straznicy
ORDER BY nazwisko;
----
--ZAD17
SELECT RPAD(nazwisko, 40 - length(stanowisko), '.') || UPPER(stanowisko) AS "nazwisko i stanowisko"
FROM straznicy
ORDER BY id;
----
--ZAD18
SELECT UPPER(LEFT(stanowisko, 2)) || id AS "wygenerowany kod", id AS "id strażnika", nazwisko, stanowisko
FROM straznicy
ORDER BY "wygenerowany kod", "id strażnika", nazwisko, stanowisko;
----
--ZAD19
SELECT nazwisko, REGEXP_REPLACE(nazwisko, '[KkLlMm]', 'X', 'g') AS "zmienione nazwisko"
FROM straznicy
ORDER BY nazwisko, "zmienione nazwisko";
----
--ZAD20
SELECT imie || ' ' || nazwisko AS "imię i nazwisko", TO_CHAR(data_od, 'Month, DD YYYY') AS "uzyskanie uprawnień"
FROM kierowcy
WHERE AGE(data_do, data_od) < INTERVAL '5 years'
ORDER BY data_do - data_od;
----
--ZAD21
SELECT id,
       CASE
           WHEN kwota * (CASE WHEN recydywa THEN 2 ELSE 1 END) > 400 THEN 'więcej'
           WHEN kwota * (CASE WHEN recydywa THEN 2 ELSE 1 END) = 400 THEN 'równa'
           ELSE 'mniej'
           END
FROM wykroczenia
ORDER BY id;
----
--ZAD22
SELECT imie, nazwisko, premia
FROM straznicy
ORDER BY premia DESC NULLS LAST, id;
----
--ZAD23
SELECT *
FROM straznicy
ORDER BY SUBSTRING(pesel FROM 3 FOR 1) || SUBSTRING(pesel FROM 1 FOR 2) || SUBSTRING(pesel FROM 3 FOR 4)
    LIMIT 5;
----
--ZAD24
SELECT kierowcy.imie, kierowcy.nazwisko, kierowcy.pesel
FROM kierowcy
INTERSECT
SELECT straznicy.imie, straznicy.nazwisko, straznicy.pesel
FROM straznicy;
----
--ZAD25
SELECT TO_CHAR(CURRENT_DATE, 'Day') AS "dziś";
----