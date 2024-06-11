var express = require("express");
var router = express.Router();
const db = require("./db"); // Import in-memory database

// POST /users Route für User-Registrierung
router.post("/", (req, res) => {
  const { username, password } = req.body;

  if (db.signup(username, password)) {
    const credentials = db.login(username, password);
    return res.status(201).json({
      // 201 created
      message: "User registered successfully",
      sessionToken: credentials.token,
    });
  } else {
    return res.status(409).json({ message: "Username already exists" }); // 409 conflict
  }
});

module.exports = router;
