CREATE TABLE Movie (mID INT, title TEXT, year INT, director TEXT);
CREATE TABLE Reviewer (rID INT, name TEXT);
CREATE TABLE Rating (rID INT, mID INT, stars INT, ratingDate DATE);

INSERT INTO Movie (mID, title, year, director) VALUES (101, 'Gone with the Wind', 1939, 'Victor Fleming');
INSERT INTO Movie (mID, title, year, director) VALUES (102, 'Star Wars', 1977, 'George Lucas');
INSERT INTO Movie (mID, title, year, director) VALUES (103, 'The Sound of Music', 1965, 'Robert Wise');
INSERT INTO Movie (mID, title, year, director) VALUES (104, 'E.T.', 1982, 'Steven Spielberg');
INSERT INTO Movie (mID, title, year, director) VALUES (105, 'Titanic', 1997, 'James Camerong');
INSERT INTO Movie (mID, title, year, director) VALUES (106, 'Snow White', 1937, null);
INSERT INTO Movie (mID, title, year, director) VALUES (107, 'Avatar', 2009, 'James Cameron');
INSERT INTO Movie (mID, title, year, director) VALUES (108, 'Raiders of the Lost Ark', 1981, 'Steven Spielberg');

INSERT INTO Reviewer (rID, name) VALUES (201, 'Sarah Martinez');
INSERT INTO Reviewer (rID, name) VALUES (202, 'Daniel Lewis');
INSERT INTO Reviewer (rID, name) VALUES (203, 'Brittany Harrisz');
INSERT INTO Reviewer (rID, name) VALUES (204, 'Mike Anderson');
INSERT INTO Reviewer (rID, name) VALUES (205, 'Chris Jackson');
INSERT INTO Reviewer (rID, name) VALUES (206, 'Elizabeth Thomas');
INSERT INTO Reviewer (rID, name) VALUES (207, 'James Cameron');
INSERT INTO Reviewer (rID, name) VALUES (208, 'Ashley White');

INSERT INTO Rating (rID, mID, stars, ratingDate) VALUES (201, 101, 2, DATE '2011-01-22');
INSERT INTO Rating (rID, mID, stars, ratingDate) VALUES (201, 101, 4, DATE '2011-01-27');
INSERT INTO Rating (rID, mID, stars, ratingDate) VALUES (202, 106, 4, null);
INSERT INTO Rating (rID, mID, stars, ratingDate) VALUES (203, 103, 2, DATE '2011-01-20');
INSERT INTO Rating (rID, mID, stars, ratingDate) VALUES (203, 108, 4, DATE '2011-01-12');
INSERT INTO Rating (rID, mID, stars, ratingDate) VALUES (203, 108, 2, DATE '2011-01-30');
INSERT INTO Rating (rID, mID, stars, ratingDate) VALUES (204, 101, 3, DATE '2011-01-09');
INSERT INTO Rating (rID, mID, stars, ratingDate) VALUES (205, 103, 3, DATE '2011-01-27');
INSERT INTO Rating (rID, mID, stars, ratingDate) VALUES (205, 104, 2, DATE '2011-01-22');
INSERT INTO Rating (rID, mID, stars, ratingDate) VALUES (205, 108, 4, null);
INSERT INTO Rating (rID, mID, stars, ratingDate) VALUES (206, 107, 3, DATE '2011-01-15');
INSERT INTO Rating (rID, mID, stars, ratingDate) VALUES (206, 106, 5, DATE '2011-01-19');
INSERT INTO Rating (rID, mID, stars, ratingDate) VALUES (207, 107, 5, DATE '2011-01-20');
INSERT INTO Rating (rID, mID, stars, ratingDate) VALUES (208, 104, 3, DATE '2011-01-02');

