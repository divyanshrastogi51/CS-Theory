create database join_us;
use join_us;
CREATE TABLE users
(
	u_id int not null primary key auto_increment,
    email  VARCHAR(255) not null unique,
    password varchar(255) NOT NULL,
	created_at DATETIME DEFAULT NOW()
);

CREATE TABLE newsletters ( 
   n_id int PRIMARY KEY AUTO_INCREMENT, 
   name varchar(50)
);

CREATE TABLE subscriber( 
   s_id int PRIMARY KEY AUTO_INCREMENT, 
   user_id int references users.id,
   news_id int references newsletter.id,
   UNIQUE KEY (user_id,news_id)
);

INSERT INTO users (email,password) VALUES('abcd','abcd');

INSERT INTO newsletters (name) VALUES('Hello'), ('Hellooo');
INSERT INTO subscriber (user_id,news_id) VALUES(1,1), (2,2),(1,2);
select * from users;
select * from newsletters;
select * from subscriber;

SELECT * FROM users ORDER BY created_at desc;

Select * from newsletters left join (Select * from users join subscriber on users.u_id = subscriber.user_id )as us on newsletters.n_id=us.news_id;

Select *,count(news_id) from newsletters  left join (Select * from users join subscriber on users.u_id = subscriber.user_id )as us on newsletters.n_id=us.news_id group by n_id;
