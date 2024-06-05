var express = require("express");
var router = express.Router();
const db = require("./db"); // Import in-memory database

// POST /sessions route
router.post("/", (req, res) => {
  const { username, password } = req.body;
  const credentials = db.login(username, password);

  if (credentials) {
    res.status(200).send({
      message: "Authentication successful",
      sessionToken: credentials.token,
    });
  } else {
    res.status(401).send({ message: "Invalid email or password" }); // 401 unauthorized
  }
});

// DELETE /sessions Route -> Logout
router.delete("/", (req, res) => {
  const { token } = req.body;
  if (!token) {
    return res.status(400).json({ message: "Token is required" }); // 400 bad request
  }

  db.deleteToken(token);
  res.status(200).json({ message: "Logout successful" }); // 200 ok
});

module.exports = router;
