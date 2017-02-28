SELECT
  movie.title,
  avg(rating.stars) AS "stars"
FROM movie
  JOIN rating ON (movie.mid = rating.mid)
GROUP BY movie.title
ORDER BY "stars", movie.title;

