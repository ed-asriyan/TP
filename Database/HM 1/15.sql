WITH sorted AS (
    SELECT
      movie.title    AS title,
      movie.director AS director
    FROM movie
    ORDER BY movie.title
)
SELECT
  string_agg(sorted.title, ','
  ORDER BY sorted.title),
  sorted.director
FROM sorted
GROUP BY sorted.director
HAVING count(*) > 1
ORDER BY sorted.director;
