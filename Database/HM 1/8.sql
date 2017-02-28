SELECT name
FROM reviewer
WHERE reviewer.rid IN (
  SELECT rid
  FROM rating
  WHERE rating.mid IN (
    SELECT mid
    FROM movie
    WHERE movie.title = 'Gone with the Wind'
  )
)
ORDER BY reviewer.name;
