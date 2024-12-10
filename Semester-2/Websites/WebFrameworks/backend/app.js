var express = require("express");
var path = require("path");
var cookieParser = require("cookie-parser");
var logger = require("morgan");
var bodyParser = require("body-parser");
var cors = require("cors");

//Routers
var usersRouter = require("./routes/users");
var sessionRouter = require("./routes/sessions");
var highscoreRouter = require("./routes/highscores");

var app = express();

app.use(logger("dev"));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, "public")));
app.use(cors());

app.use("/users", usersRouter);
app.use("/sessions", sessionRouter);
app.use("/highscores", highscoreRouter);

module.exports = app;
