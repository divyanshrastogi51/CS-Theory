var express = require('express');
var faker = require('faker');
var mysql = require('mysql');
var bodyParser  = require("body-parser");
var app = express();

app.set("view engine", "ejs");
app.use(bodyParser.urlencoded({extended: true}));
app.use(express.static(__dirname + "/public"));

var connection = mysql.createConnection({
  host     : 'localhost',
  user     : 'root',
  password: 'letdothat006',  
  database : 'join_us' ,
  port: 3306,
  multipleStatements: true     
});


 app.get("/", function(req, res){
  // Find count of users in DB
  var q = "SELECT COUNT(*) AS count FROM users";
  connection.query(q, function(err, results){
      if(err) throw err;
      var count = results[0].count; 
      res.render("login", {data: count});
  });
});

app.post('/auth', function(request, response) {
	var email = request.body.email;
	var password = request.body.password;
	if (email && password) {
		connection.query('SELECT * FROM users WHERE email = ? AND password = ?', [email, password], function(error, results, fields) {
			if (results.length > 0) {
				response.redirect('/db');
			} else {
				response.send('Incorrect Email and/or Password!');
			}			
			response.end();
		});
	} else {
		response.send('Please enter email and Password!');
		response.end();
	}
});




 app.get("/db", function(req, res){
  // Find count of users in DB

  connection.query('SELECT * FROM users ; Select *,count(n_id) as c from newsletters  join (Select * from users join subscriber on users.u_id = subscriber.user_id )as us on newsletters.n_id=us.news_id group by n_id ', [1, 2], function(err, results){
    if(err) throw err; 
    res.render("db", {data1: results[0] , data2: results[1]});
      
  });
});

app.get("/regpage", function(req, res){
  var q = "SELECT COUNT(*) AS count FROM users";
  connection.query(q, function(err, results){
      if(err) throw err;
      var count = results[0].count; 
      res.render("register", {data: count});
  });
});

app.get("/user", function(req, res){
  // Find count of users in DB

  connection.query('SELECT * FROM users ; Select *,count(n_id) as c from newsletters  join (Select * from users join subscriber on users.u_id = subscriber.user_id )as us on newsletters.n_id=us.news_id group by n_id ', [1, 2], function(err, results){
    if(err) throw err; 
    res.render("db", {data1: results[0] , data2: results[1]});
      
  });
});


app.get("/unsub", function(req, res){
  // Find count of users in DB
  var q = "SELECT * FROM users";
  connection.query(q, function(err, results){
    if(err) throw err;
    var count = results; 
    res.render("unsub", {data: count});
      
  });
});

app.post('/unsubsucc', function(req,res){
  var person = {id: req.body.id};
  connection.query('delete from users where id =?', person.id, function(err, result) {
  console.log(err);
  console.log(result);
  res.redirect("/");
  });
 });


app.get("/sort", function(req, res){
  connection.query("SELECT * FROM users ORDER BY created_at desc ; SELECT * FROM newsletters ORDER BY name", [1,2], function(err, results){
    if(err) throw err;
    res.render("db", {data1: results[0] ,data2: results[1]});
      
  });
});


app.get("/news", function(req, res){
  

  connection.query("Select * from newsletters  join (Select * from users join subscriber on users.u_id = subscriber.user_id )as us on newsletters.n_id=us.news_id ; select * from newsletters", [1,2], function(err, results){
    if(err) throw err; 
    res.render("news", {data1: results[0],data2: results[1]});
      
  });
});

app.post('/subscribe', function(req,res){
  connection.query("INSERT INTO subscriber (user_id,news_id) VALUES ("+req.body.id1+","+req.body.id2+")", function(err, result) {
  console.log(err);
  console.log(result);
  res.redirect("/db");
  });
 });

 app.post('/regi', function(req,res){
  connection.query("INSERT INTO users (email,password) values('"+req.body.email+"','"+req.body.password+"')", function(err, result) {
  console.log(err);
  console.log(result);
  res.redirect("/");
  });
 });

app.listen(8080, function () {
 console.log('App listening on port 8080!');
});
