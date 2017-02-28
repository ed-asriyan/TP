SELECT movie.year
FROM movie
WHERE movie.mid IN (
  SELECT mID
  FROM rating
  WHERE rating.stars = 5 OR rating.stars = 4
)
ORDER BY movie.year;
