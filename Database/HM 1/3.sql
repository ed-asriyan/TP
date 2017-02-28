SELECT title
FROM movie
WHERE movie.mid NOT IN (
  SELECT mid
  FROM rating
)
ORDER BY movie.title;
