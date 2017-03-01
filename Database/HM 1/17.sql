SELECT
  movie.title,
  max(rating.stars)
FROM movie
  JOIN rating ON (movie.mid = rating.mid)
GROUP BY movie.title
HAVING count(*) > 1
ORDER BY movie.title;
