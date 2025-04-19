-- Hubert Jastrzębski | Satori B (Połączenia) | 2025-04-03
-- https://satori.tcs.uj.edu.pl/contest/9744410/problems/9833071
--zad1
SELECT ROUND(MIN(cena_netto * (1 + vat/100)), 2) AS "min", ROUND(MAX(cena_netto * (1 + vat/100)), 2) AS "max"
FROM produkty;
----
--zad2
SELECT id_zamowienia, SUM(ile)
FROM produkty_zamowienia
GROUP BY id_zamowienia
ORDER BY 1;
----
--zad3
SELECT produkt
FROM produkty_zamowienia
GROUP BY produkt
HAVING SUM(ile) >= 40
ORDER BY 1;
----
--zad4
SELECT kategoria, ROUND(AVG(waga), 2)
FROM produkty
GROUP BY kategoria
HAVING COUNT(*) >= 2
ORDER BY 2 DESC, 1;
----
--zad5
SELECT kategoria, MIN(cena_netto), MAX(cena_netto), MAX(cena_netto) - MIN(cena_netto)
FROM produkty
GROUP BY kategoria
ORDER BY 1;
----
--zad6
SELECT kategoria, COUNT(*) FILTER (WHERE vat <> 18) as "liczba produktów"
FROM produkty
GROUP BY kategoria
ORDER BY 1;
----
--zad7
SELECT COUNT(*)
FROM produkty
WHERE waga < 1000;
----
--zad8
SELECT SUM(cena_netto)
FROM produkty
HAVING MAX(cena_netto) >= 300;
----
--zad9
SELECT
    CASE
        WHEN COUNT(DISTINCT adres_dostawy) = COUNT(ALL adres_dostawy) THEN 'TAK'
        ELSE 'NIE'
        END
FROM zamowienia;
----
--zad10
SELECT id_klienta
FROM zamowienia
GROUP BY id_klienta
HAVING COUNT(*) > 1
ORDER BY 1;
----
--zad11
SELECT kategoria
FROM produkty
GROUP BY kategoria
HAVING COUNT(*) = COUNT(rabat)
ORDER BY 1;
----
--zad12
SELECT kategoria
FROM produkty
WHERE vat = 8
GROUP BY kategoria
HAVING COUNT(*) = COUNT(rabat)
ORDER BY 1;
----
--zad13
SELECT kategoria,
       ROUND(COALESCE(VAR_SAMP(cena_netto), 0), 2) AS "wariancja",
       ROUND(COALESCE(STDDEV_SAMP(cena_netto), 0), 2) AS "odchylenie standardowe"
FROM produkty
GROUP BY kategoria
ORDER BY 1;
----
--zad14
SELECT COUNT(*)
FROM produkty
WHERE kategoria = 'Artykuły piśmiennicze';
----
--zad15a
SELECT ARRAY_AGG(numer_telefonu) AS "lista telefonów"
FROM klienci
WHERE numer_telefonu IS NOT NULL;
----
--zad15b
SELECT ARRAY_AGG(numer_telefonu ORDER BY numer_telefonu) AS "lista telefonów"
FROM klienci
WHERE numer_telefonu IS NOT NULL;
----
--zad16
SELECT produkt, COUNT(*)
FROM produkty_zamowienia
GROUP BY produkt
HAVING COUNT(*) >= 1
ORDER BY 2 DESC, 1;
----
--zad17
SELECT (CASE WHEN nip IS NULL THEN 'Brak' ELSE 'Podany' END) AS "NIP", COUNT(*) AS "liczba klientów"
FROM klienci
GROUP BY "NIP"
ORDER BY 1;
----
--zad18
SELECT COUNT(email)
FROM klienci
WHERE email like '%@onet.eu';
----
--zad19
SELECT TO_CHAR(data_zlozenia, 'Month') AS "miesiąc", COUNT(*) AS "liczba zamówień"
FROM zamowienia
GROUP BY "miesiąc"
ORDER BY 1;
----