WITH list AS (
  SELECT reviewer.name
  FROM reviewer
  UNION SELECT movie.title
        FROM movie
)
SELECT * FROM list
ORDER BY 1;
