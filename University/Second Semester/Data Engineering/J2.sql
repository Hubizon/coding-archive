-- Hubert Jastrzębski | Satori J2 (Wyzwalacze (cz. 2)) | 2025-05-16
-- https://satori.tcs.uj.edu.pl/contest/9744410/problems/10016546
--ZAD1
CREATE OR REPLACE FUNCTION pralki_check()
RETURNS trigger
LANGUAGE plpgsql
AS $$
BEGIN
    IF EXISTS(
        SELECT 1 FROM lodowki
            WHERE id_produktu = NEW.id_produktu
    ) OR NOT EXISTS (
        SELECT 1
        FROM produkty
        WHERE id = NEW.id_produktu
    ) THEN
        RAISE NOTICE 'BLAD';
END IF;
return NEW;
END;
$$;

CREATE CONSTRAINT TRIGGER pralki_check
    AFTER INSERT ON pralki
    DEFERRABLE INITIALLY DEFERRED
    FOR EACH ROW
    EXECUTE FUNCTION pralki_check();

CREATE OR REPLACE FUNCTION lodowki_check()
RETURNS trigger
LANGUAGE plpgsql
AS $$
BEGIN
    IF EXISTS(
        SELECT 1 FROM pralki
            WHERE id_produktu = NEW.id_produktu
    ) OR NOT EXISTS (
        SELECT 1
        FROM produkty
        WHERE id = NEW.id_produktu
    ) THEN
        RAISE NOTICE 'BLAD';
END IF;
return NEW;
END;
$$;

CREATE CONSTRAINT TRIGGER lodowki_check
    AFTER INSERT ON lodowki
    DEFERRABLE INITIALLY DEFERRED
    FOR EACH ROW
    EXECUTE FUNCTION lodowki_check();

CREATE OR REPLACE FUNCTION produkty_check()
RETURNS trigger
LANGUAGE plpgsql
AS $$
BEGIN
    IF (NOT EXISTS (
        SELECT 1 FROM pralki
            WHERE id_produktu = NEW.id
    ) AND NOT EXISTS (
        SELECT 1 FROM lodowki
            WHERE id_produktu = NEW.id
    )) OR (EXISTS (
        SELECT 1 FROM pralki
            WHERE id_produktu = NEW.id
    ) AND EXISTS (
        SELECT 1 FROM lodowki
            WHERE id_produktu = NEW.id
    )) THEN
        RAISE NOTICE 'BLAD';
END IF;
return NEW;
END;
$$;

CREATE CONSTRAINT TRIGGER produkty_check
    AFTER INSERT ON produkty
    DEFERRABLE INITIALLY DEFERRED
    FOR EACH ROW
    EXECUTE FUNCTION produkty_check();
----