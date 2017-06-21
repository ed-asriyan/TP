SELECT movie.title
FROM movie
  LEFT JOIN rating ON movie.mid = rating.mid
  LEFT JOIN reviewer ON rating.rid = reviewer.rid
WHERE rating.rid IS NULL
ORDER BY movie.title;
