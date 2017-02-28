WITH before AS (SELECT avg(rating.stars) AS "average"
                FROM movie
                  JOIN rating ON (movie.mid = rating.mid)
                WHERE movie.year < 1980
                GROUP BY movie.title),
    after AS (SELECT avg(rating.stars) AS "average"
              FROM movie
                JOIN rating ON (movie.mid = rating.mid)
              WHERE movie.year > 1980
              GROUP BY movie.title)
SELECT avg(before.average) - avg(after.average) AS "difference" FROM before, after;
