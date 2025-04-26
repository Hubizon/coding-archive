-- Hubert Jastrzębski | Satori G (Modyfikacje) | 2025-04-26
-- https://satori.tcs.uj.edu.pl/contest/9744410/problems/9913740
--ZAD1
CREATE table kategorie(
    id_kategoria serial PRIMARY KEY,
    nazwa varchar(250) NOT NULL UNIQUE,
    vat numeric(3, 1) NOT NULL
);

INSERT INTO kategorie (nazwa, vat)
SELECT kategoria, MAX(vat)
FROM produkty
GROUP BY kategoria;

ALTER TABLE produkty
    ADD COLUMN id_kategoria integer REFERENCES kategorie(id_kategoria);

UPDATE produkty
SET id_kategoria = k.id_kategoria
    FROM kategorie k
WHERE produkty.kategoria = k.nazwa;

ALTER TABLE produkty
    ALTER COLUMN id_kategoria SET NOT NULL;

ALTER TABLE produkty
DROP COLUMN kategoria,
    DROP COLUMN vat;
----
--ZAD2
CREATE TABLE historia_cen AS (
    SELECT kod_produktu::NUMERIC(6), cena_netto::NUMERIC(6, 2), '2000-01-01'::DATE AS data_wprowadzenia
    FROM produkty
);

ALTER TABLE historia_cen
    ALTER COLUMN cena_netto SET NOT NULL,
    ADD CONSTRAINT pk_historia_cen PRIMARY KEY(kod_produktu, data_wprowadzenia),
    ADD CONSTRAINT fk_kod_produktu FOREIGN KEY(kod_produktu) REFERENCES produkty(kod_produktu);

ALTER TABLE produkty
DROP COLUMN cena_netto;
----
--ZAD3
ALTER TABLE zamowienia
    ALTER COLUMN id_klienta DROP NOT NULL,
DROP CONSTRAINT fk_zam_kli;
ALTER TABLE zamowienia
    ADD CONSTRAINT fk_zam_kli
        FOREIGN KEY (id_klienta) REFERENCES klienci(id_klienta)
            ON DELETE SET NULL;

ALTER TABLE rabaty_klientow
DROP CONSTRAINT fk_zam_kli,
    DROP CONSTRAINT fk_zam_pol;
ALTER TABLE rabaty_klientow
    ADD CONSTRAINT fk_zam_kli
        FOREIGN KEY (id_klienta) REFERENCES klienci(id_klienta)
            ON DELETE CASCADE;
ALTER TABLE rabaty_klientow
    ADD CONSTRAINT fk_zam_pol
        FOREIGN KEY (id_polecajacego) REFERENCES klienci(id_klienta)
            ON DELETE CASCADE;

DELETE FROM klienci;
DROP TABLE klienci CASCADE;
----
--ZAD4
--ZAD5
--ZAD6
--ZAD7
--ZAD8
--ZAD9
ALTER TABLE etaty
    ADD COLUMN pensja_od numeric(8,2) NOT NULL DEFAULT 0,
    ADD COLUMN pensja_do numeric(8,2) NOT NULL DEFAULT 0;

UPDATE etaty
SET pensja_od = LEAST(widelki[1], widelki[2]),
    pensja_do = GREATEST(widelki[1], widelki[2]);

ALTER TABLE etaty
DROP COLUMN widelki,
    ADD CONSTRAINT pensja_check CHECK (pensja_od < pensja_do);
----
--ZAD5
--ZAD6
--ZAD7
--ZAD8
--ZAD9
UPDATE pracownicy p
SET pensja = e.pensja_od
    FROM etaty e
WHERE p.etat = e.etat AND p.pensja < e.pensja_od;
----
--ZAD6
--ZAD7
--ZAD8
--ZAD9
INSERT INTO etaty (etat, pensja_od, pensja_do)
SELECT etat || ' starszy', pensja_od, 2 * pensja_do
FROM etaty;

UPDATE pracownicy p
SET etat = e.etat || ' starszy'
    FROM etaty e
WHERE p.etat = e.etat AND p.pensja > e.pensja_do;
----
--ZAD7
--ZAD8
--ZAD9
ALTER TABLE etaty
    ADD COLUMN id_etatu integer;

WITH to_id_etatu AS (
    SELECT etat, row_number() OVER (ORDER BY etat) AS rn
    FROM etaty
)
UPDATE etaty
SET id_etatu = 10 * rn
    FROM to_id_etatu tie
WHERE etaty.etat = tie.etat;

ALTER TABLE pracownicy
DROP CONSTRAINT pracownicy_etat_fkey;

UPDATE pracownicy p
SET etat = e.id_etatu
    FROM etaty e
WHERE p.etat = e.etat;

ALTER TABLE etaty
DROP CONSTRAINT etaty_pkey,
    ADD CONSTRAINT etaty_pkey PRIMARY KEY(id_etatu);

ALTER TABLE pracownicy
ALTER COLUMN etat TYPE integer USING etat::integer,
    ALTER COLUMN etat SET NOT NULL,
    ADD CONSTRAINT pracownicy_etat_fkey FOREIGN KEY (etat) REFERENCES etaty(id_etatu);
----
--ZAD8
--ZAD9
ALTER TABLE pracownicy
    ADD COLUMN dodatki numeric(8, 2);

UPDATE pracownicy p
SET dodatki = p.pensja - e.pensja_do
    FROM etaty e
WHERE p.etat = e.id_etatu AND p.pensja > e.pensja_do;

UPDATE pracownicy p
SET pensja = e.pensja_do
    FROM etaty e
WHERE p.etat = e.id_etatu AND p.dodatki IS NOT NULL;
----
--ZAD9
WITH maxp AS (
    SELECT p.id, MAX(pensja_do) AS max_pensja_do
    FROM pracownicy p
             JOIN etaty e ON p.pensja + COALESCE(p.dodatki, 0) BETWEEN e.pensja_od AND e.pensja_do
    GROUP BY p.id)
SELECT imie, nazwisko, e.etat
FROM pracownicy p
         NATURAL JOIN maxp
         CROSS JOIN etaty e
WHERE p.pensja + COALESCE(p.dodatki, 0) BETWEEN e.pensja_od AND e.pensja_do AND e.pensja_do = maxp.max_pensja_do;
----