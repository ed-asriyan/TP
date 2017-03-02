SELECT
  movie.title,
  max(rating.stars) - min(rating.stars) AS "spread"
FROM movie
  JOIN rating ON (rating.mid = movie.mid)
GROUP BY movie.title
ORDER BY "spread" DESC, movie.title;
