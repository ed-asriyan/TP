SELECT DISTINCT reviewer.name
FROM movie
  JOIN rating ON movie.mid = rating.mid
  JOIN reviewer ON rating.rid = reviewer.rid
WHERE movie.title = 'Gone with the Wind'
ORDER BY reviewer.name;
