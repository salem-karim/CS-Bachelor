const mongoose = require("mongoose");

const UserSchema = new mongoose.Schema(
  {
    username: { type: String, unique: true, required: true, lowercase: true },
    password: { type: String, required: true, minLength: 8 },
  },
  { Collection: "User" }, // Makes it a list of users
);

const HighScoreSchema = new mongoose.Schema(
  {
    username: { type: String, required: true, lowercase: true },
    score: { type: Number, required: true },
  },
  { Collection: "HighScore" }, // Collection so its like a list of high scores
);

// const User = mongoose.model("User", UserSchema);
// const HighScore = mongoose.model("HighScore", HighScoreSchema);
