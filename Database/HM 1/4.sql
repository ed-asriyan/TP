SELECT name
FROM reviewer
WHERE reviewer.rid IN (
  SELECT rid
  FROM rating
  WHERE ratingdate IS NULL
)
ORDER BY reviewer.name;
