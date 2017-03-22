SELECT reviewer.name
FROM reviewer
  JOIN rating ON reviewer.rid = rating.rid
WHERE rating.ratingdate IS NULL;
