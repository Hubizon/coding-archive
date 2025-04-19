-- Hubert Jastrzębski | Satori D (Podzapytania) | 2025-04-05
-- https://satori.tcs.uj.edu.pl/contest/9744410/problems/9865890
--zad1
SELECT id_egzemplarza, k.tytul
FROM ksiazki k JOIN egzemplarze e
                    ON k.id_ksiazki = e.id_ksiazki
WHERE autor = 'J.R.R. Tolkien'
ORDER BY 1, 2;
----
--zad2
SELECT kat.nazwa, COUNT(*)
FROM kategorie kat JOIN ksiazki ks
                        ON kat.id_kategorii = ks.id_kategorii
GROUP BY kat.id_kategorii
ORDER BY 1;
----
--zad3
SELECT tytul, autor
FROM ksiazki ks NATURAL JOIN egzemplarze eg
                NATURAL JOIN wypozyczenia
WHERE data_oddania IS NULL
GROUP BY tytul, autor
ORDER BY 1;
----
--zad4
SELECT autor AS "autor", COUNT(eg.id_egzemplarza) AS "liczba egzemplarzy"
FROM ksiazki ks LEFT JOIN egzemplarze eg
                          ON ks.id_ksiazki = eg.id_ksiazki
GROUP BY autor
ORDER BY 2 DESC, 1 ASC;
----
--zad5
SELECT cz1.imie, cz1.nazwisko, cz2.imie, cz2.nazwisko, cz1.miasto
FROM czytelnicy cz1 JOIN czytelnicy cz2
                         ON cz1.miasto = cz2.miasto
WHERE cz1.id_czytelnika < cz2.id_czytelnika
ORDER BY 1, 2, 3, 4, 5;
----
--zad6
SELECT ks.id_ksiazki, tytul, COUNT(eg.id_egzemplarza) <> COUNT(wyp)
FROM ksiazki ks
         LEFT JOIN egzemplarze eg USING (id_ksiazki)
         LEFT JOIN wypozyczenia wyp ON wyp.id_egzemplarza = eg.id_egzemplarza AND wyp.data_oddania IS NULL
GROUP BY ks.id_ksiazki
ORDER BY 1, 2, 3;
----
--zad7
SELECT imie, nazwisko, COUNT(*)
FROM czytelnicy JOIN wypozyczenia USING (id_czytelnika)
GROUP BY id_czytelnika
HAVING COUNT(*) - COUNT(data_oddania) > 0
ORDER BY 1, 2, 3;
----
--zad8
SELECT imie, nazwisko
FROM czytelnicy JOIN wypozyczenia USING (id_czytelnika)
WHERE data_oddania > oczekiwana_data_oddania OR data_oddania IS NULL
GROUP BY id_czytelnika
ORDER BY 1, 2;
----
--zad9
SELECT id_czytelnika, imie, nazwisko, id_wypozyczenia
FROM czytelnicy NATURAL JOIN wypozyczenia wyp
WHERE wyp.id_wypozyczenia & (wyp.id_wypozyczenia - 1) = 0
ORDER BY id_wypozyczenia;
----
--zad10
SELECT kat.nazwa
FROM wypozyczenia
         JOIN egzemplarze USING (id_egzemplarza)
         JOIN ksiazki USING (id_ksiazki)
         JOIN kategorie kat USING (id_kategorii)
GROUP BY kat.id_kategorii
ORDER BY COUNT(*) DESC, kat.id_kategorii ASC
    LIMIT 1;
----
--zad11
SELECT tytul, autor, COUNT(*)
FROM ksiazki ks
         JOIN egzemplarze eg USING (id_ksiazki)
         RIGHT JOIN wypozyczenia wyp
                    ON eg.id_egzemplarza = wyp.id_egzemplarza
GROUP BY ks.id_ksiazki
ORDER BY 3 DESC, 1, 2;
----
--zad12
SELECT cz.imie, cz.nazwisko, COALESCE(kat.nazwa, 'Brak')
FROM czytelnicy cz
         LEFT JOIN czytelnik_zainteresowania czza ON cz.id_czytelnika = czza.id_czytelnika
         LEFT JOIN kategorie kat ON czza.id_kategorii = kat.id_kategorii
ORDER BY 1, 2, 3;
----
--zad13
SELECT cz.imie, cz.nazwisko, ks.tytul, ks.autor
FROM czytelnicy cz
         JOIN czytelnik_zainteresowania czza ON cz.id_czytelnika = czza.id_czytelnika
         JOIN ksiazki ks ON czza.id_kategorii = ks.id_kategorii
WHERE cz.nazwisko LIKE 'K%'
ORDER BY 1, 2, 3, 4;
----
--zad14
SELECT imie, nazwisko, COUNT(*),
       CASE WHEN COUNT(*) > 20 THEN 'mól książkowy'
            ELSE 'niedzielny czytelnik' END
FROM czytelnicy cz
         NATURAL JOIN wypozyczenia wyp
WHERE date_part('year', data_wypozyczenia) = 2023
GROUP BY id_czytelnika
HAVING COUNT(*) >= 3
ORDER BY 3 DESC, 1, 2;
----
--zad15
SELECT cz.id_czytelnika, cz.imie, cz.nazwisko, ks.id_ksiazki, ks.tytul, ks.autor,
       CASE
           WHEN COUNT(data_wypozyczenia) = 0 THEN 'NIE'
           ELSE 'TAK'
           END AS "wypożyczona"
FROM czytelnicy cz CROSS JOIN ksiazki ks
                   LEFT JOIN egzemplarze USING (id_ksiazki)
                   LEFT JOIN wypozyczenia USING (id_egzemplarza, id_czytelnika)
GROUP BY cz.id_czytelnika, ks.id_ksiazki
ORDER BY cz.id_czytelnika, ks.id_ksiazki;
----
--zad16
SELECT imie AS "imię", nazwisko,
       COUNT(DISTINCT
             CASE
                 WHEN ksiazki.id_ksiazki IS NULL THEN NULL
                 WHEN id_kategorii IS NULL THEN -1001
                 ELSE id_kategorii
                 END) AS "liczba różnych kategorii"
FROM czytelnicy cz
         LEFT JOIN wypozyczenia USING (id_czytelnika)
         LEFT JOIN egzemplarze USING (id_egzemplarza)
         LEFT JOIN ksiazki USING (id_ksiazki)
GROUP BY id_czytelnika
ORDER BY 1, 2, 3;
----