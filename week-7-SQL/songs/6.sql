SELECT name FROM songs WHERE id IS (SELECT id FROM artists WHERE name LIKE 'Post Malone');

