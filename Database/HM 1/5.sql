SELECT
  reviewer.name,
  movie.title,
  rating.stars,
  rating.ratingdate
FROM movie
  JOIN rating ON (movie.mid = rating.mid)
  JOIN reviewer ON (rating.rid = reviewer.rid)
ORDER BY reviewer.name, movie.title, rating.stars;
