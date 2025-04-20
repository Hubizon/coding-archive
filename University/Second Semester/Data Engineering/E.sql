-- Hubert Jastrzębski | Satori E (Submity z BaCy) | 2025-04-20
-- https://satori.tcs.uj.edu.pl/contest/9744410/problems/9891545
--ZAD1
SELECT name AS language, COUNT(*) AS submits FROM submits
    JOIN jezyk ON (submits.language = jezyk.id)
GROUP BY name;
----
--ZAD2
WITH sussy AS (
    SELECT
        p.shortname AS name,
        SUM(CASE WHEN st.id = 8 THEN 1 END) AS ok,
        SUM(CASE WHEN st.id = 7 THEN 1 END) AS ans,
        SUM(CASE WHEN st.id = 5 THEN 1 END) AS tle,
        SUM(CASE WHEN st.id = 4 THEN 1 END) AS rte1,
        SUM(CASE WHEN st.id = 14 THEN 1 END) AS rte2,
        SUM(CASE WHEN st.id = 3 THEN 1 END) AS rte3,
        SUM(CASE WHEN st.id = 2 THEN 1 END) AS cmp,
        SUM(CASE WHEN st.id = 10 THEN 1 END) AS rul,
        SUM(CASE WHEN st.id = 11 THEN 1 END) AS hea,
        SUM(CASE WHEN st.id = 6 THEN 1 END) AS int,
    COUNT(*) AS sus
FROM submits s
    JOIN problems p ON s.problemsid = p.id
    JOIN statusy st ON s.status = st.id
GROUP BY p.shortname
    )
SELECT
    name, ok, ans, tle, rte1 AS rte, rte2 AS rte, rte3 AS rte, cmp,
    rul, hea, int, sus AS all
FROM sussy
ORDER BY name;
----
--ZAD3
SELECT oceny.name AS name,
       NULLIF(COUNT(*) FILTER (WHERE ocena = 1), 0) AS "100",
       NULLIF(COUNT(*) FILTER (WHERE ocena >= 0.9 AND ocena < 1), 0) AS "100-90",
       NULLIF(COUNT(*) FILTER (WHERE ocena >= 0.8 AND ocena < 0.9), 0) AS "90-80",
       NULLIF(COUNT(*) FILTER (WHERE ocena >= 0.7 AND ocena < 0.8), 0) AS "80-70",
       NULLIF(COUNT(*) FILTER (WHERE ocena >= 0.6 AND ocena < 0.7), 0) AS "70-60",
       NULLIF(COUNT(*) FILTER (WHERE ocena >= 0.5 AND ocena < 0.6), 0) AS "60-50",
       NULLIF(COUNT(*) FILTER (WHERE ocena >= 0.4 AND ocena < 0.5), 0) AS "50-40",
       NULLIF(COUNT(*) FILTER (WHERE ocena >= 0.3 AND ocena < 0.4), 0) AS "40-30",
       NULLIF(COUNT(*) FILTER (WHERE ocena >= 0.2 AND ocena < 0.3), 0) AS "30-20",
       NULLIF(COUNT(*) FILTER (WHERE ocena >= 0.1 AND ocena < 0.2), 0) AS "20-10",
       NULLIF(COUNT(*) FILTER (WHERE ocena >= 0.0 AND ocena < 0.1), 0) AS "10-0",
       COUNT(*) AS "all"
FROM (
         SELECT problems.shortname AS name, MAX(ocena)::numeric AS ocena
         FROM submits
                  JOIN problems ON submits.problemsid = problems.id
         GROUP BY usersid, problems.id
     ) AS oceny
GROUP BY name
----