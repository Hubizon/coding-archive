-- Hubert Jastrzębski | Satori K (Ciekawostki) | 2025-05-25
-- https://satori.tcs.uj.edu.pl/contest/9744410/problems/10043997
--ZAD1
CREATE OR REPLACE FUNCTION cast_int(x varchar)
    RETURNS int
    LANGUAGE plpgsql
AS
$$
DECLARE
res int;
BEGIN
BEGIN
        res := x::int;
EXCEPTION WHEN others THEN
            res := NULL;
END;
return res;
END
$$;
----
--ZAD2
SELECT
    string_to_array(
            trim(both '()' FROM row(tab.*)::text),
            ','
    ) AS wynik
FROM tab;
----
--ZAD3
CREATE OR REPLACE FUNCTION nulls(VARIADIC args anyarray)
    RETURNS int
    LANGUAGE plpgsql
AS
$$
DECLARE
el text;
    res int;
BEGIN
    res := 0;
FOR el IN SELECT unnest(args)::text
    LOOP
        IF el IS NULL THEN
            res := res + 1;
END IF;
END LOOP;
return res;
END
$$;
----
--ZAD4
CREATE OR REPLACE FUNCTION remove_duplicates(tname text)
    RETURNS void
    LANGUAGE plpgsql
AS
$$
BEGIN
EXECUTE format(
        $sql$
            DELETE FROM %1$I AS t1
      USING %1$I AS t2
      WHERE ROW(t1.*) = ROW(t2.*) AND t1.ctid < t2.ctid
    $sql$,
        tname);
END
$$;
----
--ZAD5
CREATE OR REPLACE FUNCTION array_intersect(arr1 anyarray, arr2 anyarray)
    RETURNS anyarray
    LANGUAGE plpgsql
AS
$$
DECLARE
result arr1%TYPE;
BEGIN
SELECT array_agg(DISTINCT el ORDER BY el)
INTO result
FROM (
         SELECT a1 AS el
         FROM unnest(arr1) a1
                  JOIN unnest(arr2) a2 ON a1 = a2
     ) e;
return result;
END;
$$;
----
--ZAD6
CREATE OR REPLACE FUNCTION array_sort(arr anyarray)
    RETURNS anyarray
    LANGUAGE plpgsql
AS
$$
DECLARE
result arr%TYPE;
BEGIN
SELECT array_agg(el ORDER BY el)
INTO result
FROM (
         SELECT a1 AS el
         FROM unnest(arr) a1
     ) e;
return result;
END;
$$;
----
--ZAD7
WITH numbered AS (
    SELECT *, row_number() OVER (ORDER BY t.CTID) AS numer
    FROM tab t
)
SELECT *
FROM numbered
WHERE numer % 3 = 1;
----
--ZAD8
SELECT *
FROM zwierzeta
ORDER BY (rodzaj <> 'pies'), (rodzaj <> 'kot'), nazwa;
----
--ZAD9
ALTER TABLE tab
DROP CONSTRAINT IF EXISTS tab_b_check,
    ALTER COLUMN b TYPE boolean
    USING (b = 'tak');
----
--ZAD10
SELECT tablename
FROM pg_catalog.pg_tables
WHERE schemaname = 'public';
----
--ZAD11
CREATE OR REPLACE FUNCTION remove_all()
    RETURNS VOID
    LANGUAGE plpgsql
AS
$$
DECLARE
tname text;
BEGIN
FOR tname IN (SELECT tablename FROM pg_catalog.pg_tables WHERE schemaname = 'public') LOOP
        EXECUTE format(
            $sql$
              DROP TABLE public.%1$I CASCADE;
            $sql$,
            tname);
END LOOP;
END;
$$;

SELECT remove_all();
----
--ZAD12
SELECT tablename AS table_name, pg_total_relation_size('public.' || tablename) AS total_size
FROM pg_tables
WHERE schemaname = 'public';
----