-- write a SQL query to list the names of all people
--      who have directed a movie that received a rating of at least 9.0.
--  Your query should output a table with a single column for the name of each person.
SELECT DISTINCT name FROM people
JOIN directors ON directors.person_id=people.id
JOIN movies ON directors.movie_id=movies.id
JOIN ratings ON ratings.movie_id=movies.id
WHERE rating >=9.0
