-- Hubert Jastrzębski | Satori D (Podzapytania) | 2025-04-05
-- https://satori.tcs.uj.edu.pl/contest/9744410/problems/9865890
--ZAD1
SELECT nazwa
FROM produkty
WHERE id_kategoria = (SELECT id_kategoria FROM produkty WHERE nazwa = 'Piórnik duży');
----
--ZAD2
SELECT nazwa
FROM produkty p
WHERE EXISTS (
    SELECT *
    FROM kategorie k
    WHERE k.id_kategoria = p.id_kategoria AND k.nadkategoria IS NOT NULL
);
----
--ZAD3a
SELECT kat.nazwa
FROM kategorie kat
WHERE (SELECT COUNT(*) FROM produkty WHERE kat.id_kategoria = produkty.id_kategoria) >= 3
ORDER BY 1;
----
--ZAD3b
SELECT (SELECT kat.nazwa FROM kategorie kat WHERE kat.id_kategoria = p.id_kategoria)
FROM produkty p
GROUP BY p.id_kategoria
HAVING COUNT(*) >= 3
ORDER BY 1;
----
--ZAD3c
SELECT kat.nazwa
FROM kategorie kat
         JOIN produkty p ON kat.id_kategoria = p.id_kategoria
GROUP BY kat.id_kategoria
HAVING COUNT(*) >= 3
ORDER BY 1;
----
--ZAD4
SELECT *
FROM rabaty
WHERE data_do - data_od = (SELECT MAX(data_do - data_od) FROM rabaty);
----
--ZAD5
SELECT *
FROM kategorie kat
WHERE kat.VAT < ANY (
    SELECT VAT
    FROM kategorie kat2
    WHERE kat2.nadkategoria = kat.id_kategoria
);
----
--ZAD6
SELECT id_zamowienia
FROM produkty_zamowienia
GROUP BY id_zamowienia
HAVING SUM(ilosc) >= ALL(
    SELECT SUM(ilosc)
    FROM produkty_zamowienia
    GROUP BY id_zamowienia);
----
--ZAD7
WITH zmiany AS (
    SELECT hc2.kod_produktu, COUNT(*) AS zmiany
    FROM historia_cen hc2
    WHERE EXTRACT('month' FROM data_wprowadzenia) = 4
    GROUP BY hc2.kod_produktu
)
SELECT p.nazwa, zmiany.zmiany
FROM zmiany
         LEFT JOIN public.produkty p ON p.kod_produktu = zmiany.kod_produktu
WHERE zmiany.zmiany >= 2;
----
--ZAD8
WITH RECURSIVE kategorie_rec AS (
    SELECT *, k.nazwa AS najwyzsza
    FROM kategorie k
    WHERE nadkategoria IS NULL

    UNION ALL

    SELECT k2.*, kr.najwyzsza AS najwyzsza
    FROM kategorie k2
             JOIN kategorie_rec kr ON kr.id_kategoria = k2.nadkategoria
)
SELECT nazwa, najwyzsza FROM kategorie_rec;
----
--ZAD9
SELECT p.nazwa, ROUND(hc.cena_netto * (1 + k.vat/100), 2)
FROM produkty p
         JOIN kategorie k ON p.id_kategoria = k.id_kategoria
         JOIN (
    SELECT kod_produktu, MAX(data_wprowadzenia) AS ostatnia_data
    FROM historia_cen
    GROUP BY kod_produktu
) AS ostatnie ON p.kod_produktu = ostatnie.kod_produktu
         JOIN historia_cen hc
              ON hc.kod_produktu = ostatnie.kod_produktu AND hc.data_wprowadzenia = ostatnie.ostatnia_data;
----
--ZAD10
SELECT p.nazwa, ROUND(hc.cena_netto * (1 + k.vat/100) - SUM(COALESCE(r.znizka, 0)), 2)
FROM produkty p
         JOIN kategorie k ON p.id_kategoria = k.id_kategoria
         JOIN (
    SELECT kod_produktu, MAX(data_wprowadzenia) AS ostatnia_data
    FROM historia_cen
    GROUP BY kod_produktu
) AS ostatnie ON p.kod_produktu = ostatnie.kod_produktu
         JOIN historia_cen hc
              ON hc.kod_produktu = ostatnie.kod_produktu AND hc.data_wprowadzenia = ostatnie.ostatnia_data
         LEFT JOIN rabaty_produkty rp ON p.kod_produktu = rp.id_produktu
         LEFT JOIN rabaty r ON rp.id_rabatu = r.id_rabatu AND r.data_od <= ostatnie.ostatnia_data AND r.data_do >= ostatnie.ostatnia_data
GROUP BY p.kod_produktu, hc.cena_netto, k.vat;
----
--ZAD11
WITH ostatnie_daty AS (
    SELECT z.id_zamowienia, p.kod_produktu, MAX(hc.data_wprowadzenia) AS data_wprowadzenia_max
    FROM zamowienia z
             JOIN produkty_zamowienia pz ON z.id_zamowienia = pz.id_zamowienia
             JOIN produkty p ON pz.produkt = p.kod_produktu
             JOIN historia_cen hc ON hc.kod_produktu = p.kod_produktu
    WHERE hc.data_wprowadzenia <= z.data_zlozenia
    GROUP BY z.id_zamowienia, p.kod_produktu
)
SELECT z.id_zamowienia, ROUND(SUM(hc.cena_netto * (1 + vat/100) * pz.ilosc), 2)
FROM zamowienia z
         JOIN produkty_zamowienia pz ON z.id_zamowienia = pz.id_zamowienia
         JOIN produkty p ON pz.produkt = p.kod_produktu
         JOIN kategorie k ON p.id_kategoria = k.id_kategoria
         JOIN ostatnie_daty od ON od.id_zamowienia = z.id_zamowienia AND od.kod_produktu = p.kod_produktu
         JOIN historia_cen hc ON p.kod_produktu = hc.kod_produktu AND od.data_wprowadzenia_max = hc.data_wprowadzenia
GROUP BY z.id_zamowienia;
----
--ZAD12
WITH wszystkie_znizki AS (
    WITH zniki_klienci AS (
        SELECT zamowienia.id_zamowienia, SUM(COALESCE(znizka, 0)) AS suma_znizek
        FROM zamowienia
                 LEFT JOIN rabaty_klienci ON zamowienia.id_zamowienia = rabaty_klienci.id_zamowienia
                 LEFT JOIN rabaty ON rabaty_klienci.id_rabatu = rabaty.id_rabatu AND rabaty.data_od <= zamowienia.data_zlozenia AND rabaty.data_do >= zamowienia.data_zlozenia
        GROUP BY zamowienia.id_zamowienia
    ),
         znizki_produkty AS (
             SELECT zamowienia.id_zamowienia, SUM(COALESCE(znizka, 0)) AS suma_znizek
             FROM zamowienia
                      LEFT JOIN produkty_zamowienia ON produkty_zamowienia.id_zamowienia = zamowienia.id_zamowienia
                      LEFT JOIN produkty ON produkty_zamowienia.produkt = produkty.kod_produktu
                      LEFT JOIN rabaty_produkty ON produkty.kod_produktu = rabaty_produkty.id_produktu
                 AND rabaty_produkty.min_ilosc <= produkty_zamowienia.ilosc
                      LEFT JOIN rabaty ON rabaty_produkty.id_rabatu = rabaty.id_rabatu
                 AND rabaty.data_od <= zamowienia.data_zlozenia
                 AND rabaty.data_do >= zamowienia.data_zlozenia
             GROUP BY zamowienia.id_zamowienia
         )
    SELECT z.id_zamowienia, SUM(zniki_klienci.suma_znizek) + SUM(znizki_produkty.suma_znizek) AS suma_znizek
    FROM zamowienia z
             LEFT JOIN zniki_klienci ON zniki_klienci.id_zamowienia = z.id_zamowienia
             LEFT JOIN znizki_produkty ON znizki_produkty.id_zamowienia = z.id_zamowienia
    GROUP BY z.id_zamowienia
),
     koszty_brutto AS (
         WITH ostatnie_daty AS (
             SELECT z.id_zamowienia, p.kod_produktu, MAX(hc.data_wprowadzenia) AS data_wprowadzenia_max
             FROM zamowienia z
                      JOIN produkty_zamowienia pz ON z.id_zamowienia = pz.id_zamowienia
                      JOIN produkty p ON pz.produkt = p.kod_produktu
                      JOIN historia_cen hc ON hc.kod_produktu = p.kod_produktu
             WHERE hc.data_wprowadzenia <= z.data_zlozenia
             GROUP BY z.id_zamowienia, p.kod_produktu
         )
         SELECT z.id_zamowienia, SUM(hc.cena_netto * (1 + vat/100) * pz.ilosc) AS suma_brutto
         FROM zamowienia z
                  JOIN produkty_zamowienia pz ON z.id_zamowienia = pz.id_zamowienia
                  JOIN produkty p ON pz.produkt = p.kod_produktu
                  JOIN kategorie k ON p.id_kategoria = k.id_kategoria
                  JOIN ostatnie_daty od ON od.id_zamowienia = z.id_zamowienia AND od.kod_produktu = p.kod_produktu
                  JOIN historia_cen hc ON p.kod_produktu = hc.kod_produktu AND od.data_wprowadzenia_max = hc.data_wprowadzenia
         GROUP BY z.id_zamowienia
     )
SELECT koszty_brutto.id_zamowienia, ROUND(koszty_brutto.suma_brutto - wszystkie_znizki.suma_znizek, 2)
FROM koszty_brutto
         LEFT JOIN wszystkie_znizki ON wszystkie_znizki.id_zamowienia = koszty_brutto.id_zamowienia;
----