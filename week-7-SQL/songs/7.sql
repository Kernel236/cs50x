SELECT AVG(energy) FROM songs WHERE id IS (SELECT id FROM artists WHERE name LIKE 'Drake');
