WITH reviewed AS (
    SELECT rating.mid
    FROM rating
    WHERE rating.rid IN (
      SELECT reviewer.rid
      FROM reviewer
      WHERE reviewer.name = 'Chris Jackson'))
SELECT movie.title
FROM movie
WHERE movie.mid NOT IN (SELECT *
                        FROM reviewed)
ORDER BY movie.title;
