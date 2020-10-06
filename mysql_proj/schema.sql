create database join_us;
use join_us;
CREATE TABLE users
(
	id int not null primary key auto_increment,
    email VARCHAR(255) ,
	created_at TIMESTAMP DEFAULT NOW()
);
INSERT INTO users (email) VALUES('Katiedsfsd34@yahoo.com'), ('Tunsdfsdsdgsdde@gmail.com');
select * from users;
DELETE FROM users WHERE id > 25;