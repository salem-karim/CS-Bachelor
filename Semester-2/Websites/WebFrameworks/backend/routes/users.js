var express = require("express");
var router = express.Router();
const db = require("./db"); // Import in-memory database

// POST Request to /users to create a new user
router.post("/", (req, res) => {
  const { username, password } = req.body;

  if (db.signup(username, password)) {
    const credentials = db.login(username, password);
    return res.status(201).json({
      // 201 create new User
      message: "User registered successfully",
      sessionToken: credentials.token,
    });
  } else {
    // 409 conflict E-Mail already exists
    return res.status(409).json({ message: "E-Mail already exists" });
  }
});

module.exports = router;
