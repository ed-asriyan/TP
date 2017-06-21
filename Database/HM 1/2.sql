SELECT DISTINCT movie.year
FROM movie
  JOIN rating ON movie.mid = rating.mid
  JOIN reviewer ON rating.rid = reviewer.rid
WHERE (rating.stars = 4 OR rating.stars = 5)
ORDER BY movie.year;
