WITH r1 AS (
    SELECT
      reviewer.name,
      reviewer.rid,
      rating.mid
    FROM rating
      JOIN reviewer ON (rating.rid = reviewer.rid)
)
SELECT DISTINCT
  a.name,
  b.name
FROM r1 AS a
  JOIN r1 AS b ON (
    a.mid = b.mid AND a.name < b.name
    )
ORDER BY a.name, b.name;
