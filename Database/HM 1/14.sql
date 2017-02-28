SELECT reviewer.name
FROM movie
JOIN rating ON (movie.mid = rating.mid)
JOIN reviewer ON (reviewer.rid = rating.rid)
GROUP BY reviewer.name
HAVING COUNT(*) >= 3
ORDER BY reviewer.name;
