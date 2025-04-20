-- Hubert Jastrzębski | Satori F (Tworzenie i modyfikowanie tabel) | 2025-04-19
-- https://satori.tcs.uj.edu.pl/contest/9744410/problems/9891634
--zad1
CREATE TABLE zwierzeta(
                          gatunek VARCHAR(100) NOT NULL,
                          jajorodny CHAR(1) NOT NULL CHECK(jajorodny in ('T', 'N')),
                          liczba_konczyn NUMERIC(2, 0) NOT NULL,
                          data_odkrycia DATE NOT NULL
);
----
--zad2
CREATE TABLE klienci(
                        pesel CHAR(11) PRIMARY KEY,
                        adres VARCHAR(100),
                        wiek NUMERIC(2, 0) NOT NULL,
                        wspolpraca_od DATE
);
----
--zad3
CREATE TABLE uczelnie(
                         id_uczelni NUMERIC(4, 0),
                         nazwa VARCHAR(100) UNIQUE       ,
                         adres VARCHAR(100),
                         budzet NUMERIC(10, 2) NOT NULL,
                         zalozona DATE NOT NULL,
                         PRIMARY KEY (id_uczelni),
                         UNIQUE (nazwa)
);
----
--zad4
CREATE TABLE ksiazki(
                        id_ksiazki NUMERIC(10) PRIMARY KEY,
                        tytul VARCHAR(100) NOT NULL,
                        autorzy VARCHAR(100),
                        cena NUMERIC(6, 2),
                        data_wydania DATE
);
----
--zad5
CREATE TABLE pokoje(
                       numer_pokoju NUMERIC(3),
                       id_zesp NUMERIC(2) REFERENCES zespoly,
                       liczba_okien NUMERIC(1),
                       PRIMARY KEY (numer_pokoju)
);
----
--zad6
CREATE TABLE plyty_cd(
                         kompozytor CHAR(100) NOT NULL,
                         tytul_albumu CHAR(100) NOT NULL,
                         CONSTRAINT un_ko_ty UNIQUE (kompozytor, tytul_albumu),
                         data_nagrania DATE,
                         data_wydania DATE,
                         CHECK(data_wydania > data_nagrania),
                         czas_trwania INTERVAL MINUTE TO SECOND,
                         CHECK(czas_trwania >= '0 minute' AND czas_trwania < '82 minutes')
);
----
--zad7
CREATE TABLE szef_podwladny AS (
    SELECT p2.nazwisko AS szef, p.nazwisko AS podwladny
    FROM pracownicy p
             JOIN pracownicy p2 ON p.id_szefa = p2.id_prac
);
----
--zad8
CREATE TABLE plyty_cd(
                         kompozytor CHAR(100) NOT NULL,
                         tytul_albumu CHAR(100) NOT NULL,
                         CONSTRAINT un_ko_ty UNIQUE (kompozytor, tytul_albumu),
                         data_nagrania DATE,
                         data_wydania DATE,
                         CHECK(data_wydania > data_nagrania),
                         czas_trwania INTERVAL MINUTE TO SECOND,
                         CHECK(czas_trwania >= '0 minute' AND czas_trwania < '82 minutes')
);
ALTER TABLE plyty_cd
DROP CONSTRAINT un_ko_ty,
      ADD CONSTRAINT un_ko_ty PRIMARY KEY (kompozytor, tytul_albumu);
----
--zad9
CREATE TABLE plyty_cd(
                         kompozytor CHAR(100) NOT NULL,
                         tytul_albumu CHAR(100) NOT NULL,
                         CONSTRAINT un_ko_ty UNIQUE (kompozytor, tytul_albumu),
                         data_nagrania DATE,
                         data_wydania DATE,
                         CHECK(data_wydania > data_nagrania),
                         czas_trwania INTERVAL MINUTE TO SECOND,
                         CHECK(czas_trwania >= '0 minute' AND czas_trwania < '82 minutes')
);
ALTER TABLE plyty_cd DROP CONSTRAINT un_ko_ty;
INSERT INTO plyty_cd VALUES ('a','b',to_date('01-01-2000','DD-MM-YYYY'), to_date('01-01-2001','DD-MM-YYYY'), '10 minutes');
INSERT INTO plyty_cd VALUES ('a','b',to_date('01-01-2001','DD-MM-YYYY'), to_date('01-01-2002','DD-MM-YYYY'), '20 minutes');
ALTER TABLE plyty_cd ADD CONSTRAINT un_ko_ty PRIMARY KEY (kompozytor, tytul_albumu);
----
--zad10
CREATE TABLE zwierzeta(
                          gatunek VARCHAR(100) NOT NULL,
                          jajorodny CHAR(1) NOT NULL CHECK(jajorodny in ('T', 'N')),
                          liczba_konczyn NUMERIC(2, 0) NOT NULL,
                          data_odkrycia DATE NOT NULL
);
ALTER TABLE zwierzeta RENAME TO gatunki;
DROP TABLE gatunki;
----
--zad11
CREATE TABLE projekty(
                         id_projektu NUMERIC(4, 0) PRIMARY KEY,
                         opis_projektu CHAR(20) NOT NULL UNIQUE,
                         data_rozpoczecia DATE DEFAULT NOW(),
                         data_zakonczenia DATE CHECK(data_zakonczenia > data_rozpoczecia),
                         fundusz NUMERIC(7, 2)
);
----
--zad12
CREATE TABLE projekty(
                         id_projektu NUMERIC(4, 0) PRIMARY KEY,
                         opis_projektu CHAR(20) NOT NULL UNIQUE,
                         data_rozpoczecia DATE DEFAULT NOW(),
                         data_zakonczenia DATE CHECK(data_zakonczenia > data_rozpoczecia),
                         fundusz NUMERIC(7, 2)
);
CREATE TABLE przydzialy(
                           id_projektu NUMERIC(4, 0) REFERENCES projekty(id_projektu),
                           id_prac NUMERIC(4, 0),
                           od DATE DEFAULT NOW(),
                           "do" DATE CHECK(przydzialy.do > przydzialy.od),
                           stawka NUMERIC(7, 2),
                           rola CHAR(20) CHECK(rola in ('KIERUJACY', 'ANALITYK', 'PROGRAMISTA')),
                           FOREIGN KEY (id_prac) REFERENCES pracownicy(id_prac),
                           PRIMARY KEY (id_projektu, id_prac)
);
----
--zad13
CREATE TABLE projekty(
                         id_projektu NUMERIC(4, 0) PRIMARY KEY,
                         opis_projektu CHAR(20) NOT NULL UNIQUE,
                         data_rozpoczecia DATE DEFAULT NOW(),
                         data_zakonczenia DATE CHECK(data_zakonczenia > data_rozpoczecia),
                         fundusz NUMERIC(7, 2)
);
CREATE TABLE przydzialy(
                           id_projektu NUMERIC(4, 0) REFERENCES projekty(id_projektu),
                           id_prac NUMERIC(4, 0),
                           od DATE DEFAULT NOW(),
                           "do" DATE CHECK(przydzialy.do > przydzialy.od),
                           stawka NUMERIC(7, 2),
                           rola CHAR(20) CHECK(rola in ('KIERUJACY', 'ANALITYK', 'PROGRAMISTA')),
                           FOREIGN KEY (id_prac) REFERENCES pracownicy(id_prac),
                           PRIMARY KEY (id_projektu, id_prac)
);
ALTER TABLE przydzialy ADD godziny NUMERIC;
----
--zad14
CREATE TABLE projekty(
                         id_projektu NUMERIC(4, 0) PRIMARY KEY,
                         opis_projektu CHAR(20) NOT NULL UNIQUE,
                         data_rozpoczecia DATE DEFAULT NOW(),
                         data_zakonczenia DATE CHECK(data_zakonczenia > data_rozpoczecia),
                         fundusz NUMERIC(7, 2)
);
ALTER TABLE projekty
DROP CONSTRAINT projekty_opis_projektu_key;
ALTER TABLE projekty
    ADD CONSTRAINT  projekty_opis_projektu_key UNIQUE (opis_projektu);
----
--zad15
CREATE TABLE projekty(
                         id_projektu NUMERIC(4, 0) PRIMARY KEY,
                         opis_projektu CHAR(20) NOT NULL UNIQUE,
                         data_rozpoczecia DATE DEFAULT NOW(),
                         data_zakonczenia DATE CHECK(data_zakonczenia > data_rozpoczecia),
                         fundusz NUMERIC(7, 2)
);
ALTER TABLE projekty
ALTER COLUMN opis_projektu TYPE CHAR(30);
----
--zad16
INSERT INTO pracownicy VALUES (1000, 'Kowalski', 'Zupa', 'PROFESOR', 100,
                               to_date('01-01-2000','DD-MM-YYYY'), 1000, 100, 10);
ALTER TABLE pracownicy ADD CONSTRAINT unique_nazwisko UNIQUE (nazwisko);
----
--zad17
ALTER TABLE pracownicy
DROP COLUMN imie;
----
--zad18
CREATE TABLE pracownicy_zespoly AS
SELECT nazwisko, etat, 12 * placa_pod AS "roczna_placa", zespoly.nazwa AS "zespol", zespoly.adres AS "adres_pracy"
FROM pracownicy
         NATURAL JOIN zespoly;
----