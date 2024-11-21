-- Sample SQL file for testing
CREATE TABLE users (
    id INT PRIMARY KEY,
    name VARCHAR(50),
    email VARCHAR(100)
);

INSERT INTO users (id, name, email)
VALUES (1, 'John Doe', 'john@example.com');

SELECT name, email FROM users WHERE id = 1;
DELETE FROM users WHERE id = 2;
