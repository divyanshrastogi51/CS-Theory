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
  port: 3306
          
});


 app.get("/", function(req, res){
  // Find count of users in DB
  var q = "SELECT COUNT(*) AS count FROM users";
  connection.query(q, function(err, results){
      if(err) throw err;
      var count = results[0].count; 
      res.render("home", {data: count});
  });
});

app.post('/register', function(req,res){
  var person = {email: req.body.email};
  connection.query('INSERT INTO users SET ?', person, function(err, result) {
  console.log(err);
  console.log(result);
  res.redirect("/");
  });
 });


 app.get("/db", function(req, res){
  // Find count of users in DB
  var q = "SELECT * FROM users";
  connection.query(q, function(err, results){
    if(err) throw err;
    var count = results; 
    res.render("db", {data: count});
      
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

//  app.post('/sort', function(req,res){
//   var person = {id: req.body.id};
//   connection.query('delete from users where id =?', person.id, function(err, result) {
//   console.log(err);
//   console.log(result);
//   res.redirect("/");
//   });
//  });

app.get("/sort", function(req, res){
  // Find count of users in DB
  var q = "SELECT * FROM users ORDER BY created_at";
  connection.query(q, function(err, results){
    if(err) throw err;
    var count = results; 
    res.render("db", {data: count});
      
  });
});

app.listen(8080, function () {
 console.log('App listening on port 8080!');
});
