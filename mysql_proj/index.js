var express = require('express');
var session = require('express-session');
var faker = require('faker');
var mysql = require('mysql');
var bodyParser  = require("body-parser");
var app = express();

app.set("view engine", "ejs");
app.use(session({
	secret: 'secret',
	resave: true,
	saveUninitialized: true
}));
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
        request.session.loggedin = true;
        request.session.username = email;
        if(request.session.username == "admin")
        {response.redirect('/db');}
        else{
				response.redirect('/profile');}
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

app.get('/profile', function(request, response) {
	if (request.session.loggedin ) {
    
    connection.query('SELECT * FROM users where email=?; SELECT * FROM newsletters ORDER BY name; Select * from newsletters  join (Select * from users join subscriber on users.u_id = subscriber.user_id )as us on newsletters.n_id=us.news_id where email=?; ',[request.session.username,request.session.username], function(err, results){
      if(err) throw err; 
      response.render("profile", {data1: results[0] , data2: results[1] , data3: request.session.username , data4:results[2]});
        
    });
  }
  
});

 app.get("/db", function(req, res){
  // Find count of users in DB
  if (req.session.loggedin && req.session.username == "admin" ) {
  connection.query('SELECT * FROM users ; Select *,count(news_id) as c from newsletters  left join (Select * from users join subscriber on users.u_id = subscriber.user_id )as us on newsletters.n_id=us.news_id group by n_id; ', [1, 2], function(err, results){
    if(err) throw err; 
    res.render("db", {data1: results[0] , data2: results[1]});
      
  });
}
});

app.get("/regpage", function(req, res){
  var q = "SELECT COUNT(*) AS count FROM users";
  connection.query(q, function(err, results){
      if(err) throw err;
      var count = results[0].count; 
      res.render("register", {data: count});
  });
});



app.get("/unsub", function(req, res){
 
  if (req.session.loggedin) { 
  connection.query("Select * from newsletters  join (Select * from users join subscriber on users.u_id = subscriber.user_id )as us on newsletters.n_id=us.news_id ; select * from newsletters", [1,2], function(err, results){
    if(err) throw err; 
    res.render("unsub", {data1: results[0],data2: results[1]});
      
  });
}
});

app.post('/unsubsucc', function(req,res){
  if (req.session.loggedin) {
  var person = {id1: req.body.id1,id2: req.body.id2};
  connection.query('delete from subscriber where user_id =? and news_id= ?', [person.id1,person.id2] ,function(err, result) {
  console.log(err);
  console.log(result);
  res.redirect("/profile");
  });
}
 });


app.get("/sort", function(req, res){
  connection.query("SELECT * FROM users ORDER BY created_at desc ; Select *,count(news_id) as c from newsletters  left join (Select * from users join subscriber on users.u_id = subscriber.user_id )as us on newsletters.n_id=us.news_id group by n_id", [1,2], function(err, results){
    if(err) throw err;
    res.render("db", {data1: results[0] ,data2: results[1]});
      
  });
});


app.get("/news", function(req, res){
  
  if (req.session.loggedin) {
  connection.query("Select * from newsletters  join (Select * from users join subscriber on users.u_id = subscriber.user_id )as us on newsletters.n_id=us.news_id ; select * from newsletters", [1,2], function(err, results){
    if(err) throw err; 
    res.render("news", {data1: results[0],data2: results[1]});
      
  });
}
});


app.get("/newsletter", function(req, res){
  
  if (req.session.loggedin) {
  connection.query("select * from newsletters", [1,2], function(err, results){
    if(err) throw err; 
    res.render("newsletter", {data1: results[0]});
      
  });
}
});

app.post('/addnews', function(req,res){
  if (req.session.loggedin) {
  var person = req.body.name;
  connection.query("INSERT INTO newsletters (name) VALUES ('"+person+"')" ,function(err, result) {
  console.log(err);
  console.log(result);
  res.redirect("/db");
  });
}
 });

app.post('/subscribe', function(req,res){
  if (req.session.loggedin) {
  connection.query("INSERT INTO subscriber (user_id,news_id) VALUES ("+req.body.id1+","+req.body.id2+")", function(err, result) {
  console.log(err);
  console.log(result);
  res.redirect("/profile");
  });
}
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
