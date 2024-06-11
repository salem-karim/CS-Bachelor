var express = require("express");
var router = express.Router();
const db = require("./db"); // Import in-memory database

router.post("/", (req, res) => {
  const { token, score } = req.body;

  if (!db.isAuthenticated(token)) {
    return res.status(401).json({ message: "Unauthorized" });
  }

  const user = db.getAuthUser(token);
  db.addHighscore(user.username, score);
  return res.status(201).json({ message: "Highscore added successfully" });
});

// GET /highscores - get all highscores
router.get("/", (req, res) => {
  const highscores = db.getHighscores();
  return res.status(200).json(highscores);
});

module.exports = router;
