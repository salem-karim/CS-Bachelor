var express = require("express");
var cors = require("cors");

var usersRouter = require("./routes/users");
var sessionsRouter = require("./routes/sessions");
var highscoreRouter = require("./routes/highscore");

var app = express();

app.use(cors());

app.use("/users", usersRouter);
app.use("/sessions", sessionsRouter);
app.use("/highscore", highscoreRouter);

module.exports = app;
