-- Hubert Jastrzębski | Satori J1 (Wyzwalacze oraz reguły) | 2025-05-15
-- https://satori.tcs.uj.edu.pl/contest/9744410/problems/10016367
--ZAD1
CREATE OR REPLACE FUNCTION pesel_check()
RETURNS trigger AS $pesel_check$
BEGIN
    IF LENGTH(NEW.pesel) <> 11 OR (10 - (
        right(left(NEW.pesel, 1), 1)::int * 1 +
        right(left(NEW.pesel, 2), 1)::int * 3 +
        right(left(NEW.pesel, 3), 1)::int * 7 +
        right(left(NEW.pesel, 4), 1)::int * 9 +
        right(left(NEW.pesel, 5), 1)::int * 1 +
        right(left(NEW.pesel, 6), 1)::int * 3 +
        right(left(NEW.pesel, 7), 1)::int * 7 +
        right(left(NEW.pesel, 8), 1)::int * 9 +
        right(left(NEW.pesel, 9), 1)::int * 1 +
        right(left(NEW.pesel, 10), 1)::int * 3
    ) % 10) % 10 <> right(NEW.pesel, 1)::int THEN
        RAISE EXCEPTION 'Niepoprawny PESEL';
END IF;
RETURN NEW;
END;
$pesel_check$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER pesel_check BEFORE INSERT OR UPDATE ON pacjenci
                                                                         FOR EACH ROW EXECUTE PROCEDURE pesel_check();
----
--ZAD2
CREATE OR REPLACE FUNCTION visit_check()
RETURNS trigger AS $visit_check$
BEGIN
    IF NEW.data_zakonczenia IS NULL THEN
        NEW.data_zakonczenia := NEW.data_rozpoczecia + INTERVAL '30 minutes';
END IF;
RETURN NEW;
END;
$visit_check$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER visit_check BEFORE INSERT ON wizyty
FOR EACH ROW EXECUTE PROCEDURE visit_check();
----
--ZAD3
CREATE OR REPLACE FUNCTION visit_delete_check()
RETURNS trigger AS $visit_delete_check$
BEGIN
    IF OLD.data_zakonczenia >= NOW() - INTERVAL '5 years' THEN
        RETURN NULL;
END IF;
RETURN OLD;
END;
$visit_delete_check$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER visit_delete_check BEFORE DELETE ON wizyty
FOR EACH ROW EXECUTE PROCEDURE visit_delete_check();
----
--ZAD4
CREATE OR REPLACE FUNCTION visit_hour_check()
RETURNS trigger AS $visit_hour_check$
BEGIN
    IF NEW.data_zakonczenia > NEW.data_rozpoczecia + INTERVAL '1 hour' THEN
        RETURN NULL;
END IF;
    IF EXISTS (SELECT * FROM wizyty WHERE data_rozpoczecia <= NEW.data_zakonczenia AND data_zakonczenia >= NEW.data_rozpoczecia) THEN
        RETURN NULL;
END IF;
RETURN NEW;
END;
$visit_hour_check$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER visit_hour_check BEFORE INSERT ON wizyty
FOR EACH ROW EXECUTE PROCEDURE visit_hour_check();
----
--ZAD5
CREATE TABLE lekarze_prowadzacy(
                                   pesel char(11),
                                   lekarz integer,
                                   PRIMARY KEY (pesel, lekarz),
                                   FOREIGN KEY (pesel) REFERENCES pacjenci(pesel),
                                   FOREIGN KEY (lekarz) REFERENCES lekarze(id)
);

CREATE OR REPLACE FUNCTION family_check()
RETURNS trigger AS $family_check$
BEGIN
INSERT INTO lekarze_prowadzacy(pesel, lekarz)
SELECT NEW.pesel, lekarze.id
FROM lekarze
         JOIN specjalizacje ON lekarze.id = specjalizacje.id_lekarza
         LEFT JOIN (SELECT lekarz, COUNT(pesel) AS cnt
                    FROM lekarze_prowadzacy
                    GROUP BY lekarz) lekarze_counts
                   ON lekarze.id = lekarze_counts.lekarz
WHERE specjalizacja = 'Medycyna rodzinna'
ORDER BY COALESCE(lekarze_counts.cnt, 0), id
    LIMIT 1;
return NEW;
END;
$family_check$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER family_check AFTER INSERT ON pacjenci
FOR EACH ROW EXECUTE PROCEDURE family_check();
----
--ZAD6
CREATE OR REPLACE VIEW pediatrzy AS
SELECT lekarze.id, lekarze.imie, lekarze.nazwisko FROM lekarze
                                                           JOIN specjalizacje ON lekarze.id = specjalizacje.id_lekarza
WHERE specjalizacje.specjalizacja = 'Pediatria';

CREATE OR REPLACE RULE pediatrzy_add AS ON INSERT TO pediatrzy
DO INSTEAD (
    INSERT INTO lekarze(id, imie, nazwisko)
    VALUES (NEW.id, NEW.imie, NEW.nazwisko);
    INSERT INTO specjalizacje(id_lekarza, specjalizacja)
    VALUES (NEW.id, 'Pediatria');
);
----
--ZAD7
CREATE OR REPLACE VIEW chirurdzy AS
SELECT lekarze.id, lekarze.imie, lekarze.nazwisko FROM lekarze
                                                           JOIN specjalizacje ON lekarze.id = specjalizacje.id_lekarza
WHERE specjalizacja = 'Chirurgia';

CREATE OR REPLACE RULE chirurdzy_delete AS ON DELETE TO chirurdzy
DO INSTEAD NOTHING;
----
--ZAD8
CREATE OR REPLACE RULE chirurdzy_delete AS ON DELETE TO lekarze
WHERE EXISTS (
    SELECT * FROM specjalizacje
             WHERE id_lekarza = OLD.id AND specjalizacje.specjalizacja = 'Chirurgia'
) DO INSTEAD NOTHING;
----
--ZAD9
CREATE OR REPLACE RULE pacjenci_erase AS ON DELETE TO pacjenci
DO ALSO (
    DELETE FROM wizyty
        WHERE pacjent = OLD.pesel;
);
----
--ZAD10
CREATE OR REPLACE VIEW terminarz AS
SELECT wizyty.pacjent AS pacjent,
       specjalizacje.specjalizacja AS specjalista,
       wizyty.data_rozpoczecia AS termin_od,
       wizyty.data_zakonczenia AS termin_do
FROM wizyty
         JOIN lekarze ON wizyty.lekarz = lekarze.id
         JOIN specjalizacje ON lekarze.id = specjalizacje.id_lekarza
WHERE FALSE;

CREATE OR REPLACE RULE terminarz_add AS ON INSERT TO terminarz
DO INSTEAD (
    INSERT INTO wizyty(lekarz, pacjent, data_rozpoczecia, data_zakonczenia)
        SELECT lekarze.id, NEW.pacjent, NEW.termin_od, NEW.termin_do
        FROM lekarze
        JOIN specjalizacje ON lekarze.id = specjalizacje.id_lekarza
        WHERE specjalizacje.specjalizacja = NEW.specjalista
            AND NOT EXISTS(SELECT *
                           FROM wizyty
                           WHERE wizyty.lekarz = lekarze.id
                              AND data_rozpoczecia < NEW.termin_do
                              AND data_zakonczenia > NEW.termin_od
            )
        ORDER BY lekarze.id
        LIMIT 1;
);
----