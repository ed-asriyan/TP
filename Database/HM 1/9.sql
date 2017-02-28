SELECT
  reviewer.name,
  movie.title,
  rating.stars
FROM movie
  JOIN rating ON (movie.mid = rating.mid)
  JOIN reviewer ON (rating.rid = reviewer.rid AND movie.director = reviewer.name);
