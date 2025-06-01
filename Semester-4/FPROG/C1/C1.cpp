#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "./board_utils.hpp"

using std::string;
using std::vector;

const vector<char> invalidTokens = {'A', 'B', 'C', 'Z', '1', '*'};

auto createRng = []() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  return std::mt19937(seed);
};

auto shuffleColumns = [](Board &board, std::mt19937 &rng) {
  for (int col = 0; col < COLS; ++col) {
    // Extract non empty tokens from board
    vector<char> tokensInCol;
    for (int row = 0; row < ROWS; ++row) {
      char c = board[row][col];
      if (c != ' ')
        tokensInCol.push_back(c);
    }

    // Shuffle tokens in this column
    std::shuffle(tokensInCol.begin(), tokensInCol.end(), rng);

    // Clear column
    for (int row = 0; row < ROWS; ++row)
      board[row][col] = ' ';

    // Fill that column with the shuffled tokens
    int fillRow = ROWS - 1;
    for (char token : tokensInCol) {
      board[fillRow--][col] = token;
    }
  }
};

auto randomValidToken = [](std::mt19937 &rng) {
  std::uniform_int_distribution<> dist(0, 1);
  return validTokens[dist(rng)];
};

auto randomInvalidToken = [](std::mt19937 &rng) {
  std::uniform_int_distribution<> dist(0, invalidTokens.size() - 1);
  return invalidTokens[dist(rng)];
};

auto generateFullyFilledCorrectBoard = [](std::mt19937 &rng) {
  // Make a char vector with balanced amount of tokens
  int totalCells = ROWS * COLS;
  int rCount = totalCells / 2;
  int yCount = totalCells - rCount;
  vector<char> tokens;
  tokens.insert(tokens.end(), rCount, 'R');
  tokens.insert(tokens.end(), yCount, 'Y');

  // Shuffle tokens
  std::shuffle(tokens.begin(), tokens.end(), rng);

  // Fill board by column from the bottom
  Board board = makeEmptyBoard();
  int index = 0;
  for (int col = 0; col < COLS; ++col) {
    for (int row = ROWS - 1; row >= 0; --row) {
      board[row][col] = tokens[index++];
    }
  }
  return board;
};

auto generateFullyFilledErroneousBoard = [](std::mt19937 &rng) {
  Board board = generateFullyFilledCorrectBoard(rng);
  std::uniform_int_distribution<> distRow(0, ROWS - 1);
  std::uniform_int_distribution<> distCol(0, COLS - 1);
  bool hasError = false;

  // Randomly break one or more rules
  if (rng() % 2 == 0) { // Break token validity
    for (int i = 0; i < 3; ++i)
      board[distRow(rng)][distCol(rng)] = randomInvalidToken(rng);
    hasError = true;
  }
  if (rng() % 2 == 0) // Break balance
    board[0][0] = 'R';
  // don't set to true as it does not always lead to imbalance
  if (rng() % 2 == 0) { // Break gravity
    board[1][1] = 'R';
    board[2][1] = ' ';
    hasError = true;
  }

  if (!hasError) {
    // Apply all errors if none were applied
    for (int i = 0; i < 3; ++i)
      board[distRow(rng)][distCol(rng)] = randomInvalidToken(rng);
    board[0][0] = 'R';
    board[1][1] = 'R';
    board[2][1] = ' ';
  }

  return board;
};

auto generatePartiallyFilledCorrectBoard = [](std::mt19937 &rng) {
  Board board = makeEmptyBoard();
  int r = 0, y = 0;
  for (int col = 0; col < COLS; ++col) {
    int height = rng() % (ROWS + 1);
    for (int i = 0; i < height; ++i) {
      char token = (r <= y) ? 'R' : 'Y';
      board[ROWS - 1 - i][col] = token;
      token == 'R' ? ++r : ++y;
    }
  }

  // Shuffle tokens in each column
  shuffleColumns(board, rng);

  return board;
};

auto generatePartiallyFilledErroneousBoard = [](std::mt19937 &rng) {
  Board board = generatePartiallyFilledCorrectBoard(rng);
  bool hasError = false;

  // Introduce one or more errors
  if (rng() % 2 == 1) {
    board[0][0] = 'R';
    // don't set to true as it does not always lead to imbalance
  } // Break balance

  if (rng() % 2 == 0) { // Break token validity
    board[0][1] = randomInvalidToken(rng);
    hasError = true;
  }

  if (rng() % 2 == 0) { // Break gravity
    board[1][2] = 'R';
    board[2][2] = ' ';
    hasError = true;
  }

  if (!hasError) {
    board[1][2] = 'R';
    board[2][2] = ' ';
    board[0][1] = randomInvalidToken(rng);
    board[0][0] = 'R';
  }

  return board;
};

auto generateWinningBoard = [](std::mt19937 &rng, char winningToken) {
  Board board = makeEmptyBoard();

  // Pick a random column (0 to COLS-1)
  std::uniform_int_distribution<int> colDist(0, COLS - 1);
  int winCol = colDist(rng);

  // Place 4 winning tokens at the bottom of that column
  for (int i = 0; i < 4; ++i) {
    board[ROWS - 1 - i][winCol] = winningToken;
  }

  // Add 3 of the other token to maintain balance (4 vs 3 = difference of 1)
  char otherToken = (winningToken == 'R') ? 'Y' : 'R';

  // Pick a different column for the other tokens
  std::uniform_int_distribution<int> otherColDist(0, COLS - 1);
  int otherCol;
  do {
    otherCol = otherColDist(rng);
  } while (otherCol == winCol); // Make sure it's a different column

  // Place 3 of the other token at the bottom of that column
  for (int i = 0; i < 3; ++i) {
    board[ROWS - 1 - i][otherCol] = otherToken;
  }

  return board;
};

TEST_CASE("Fully filled correct board is valid in all respects") {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 rng(seed);
  Board board = generateFullyFilledCorrectBoard(rng);
  CHECK(isGravityValid(board));
  CHECK(isTokenBalanceValid(board));
  CHECK(hasOnlyValidTokens(board));
}

TEST_CASE("Fully filled erroneous board has at least one problem") {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 rng(seed);
  Board board = generateFullyFilledErroneousBoard(rng);
  CHECK(!(isGravityValid(board) && isTokenBalanceValid(board) &&
          hasOnlyValidTokens(board)));
}

TEST_CASE(
    "Partially filled correct board has balanced tokens and valid gravity") {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 rng(seed);
  Board board = generatePartiallyFilledCorrectBoard(rng);
  CHECK(isGravityValid(board));
  CHECK(isTokenBalanceValid(board));
  CHECK(hasOnlyValidTokens(board));
}

TEST_CASE("Partially filled erroneous board has at least one problem") {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 rng(seed);
  Board board = generatePartiallyFilledErroneousBoard(rng);
  CHECK(!(isGravityValid(board) && isTokenBalanceValid(board) &&
          hasOnlyValidTokens(board)));
}

TEST_CASE("Winning board is valid and contains a winning token pattern") {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 rng(seed);

  std::uniform_int_distribution<int> tokenDist(0, 1);
  char winningToken = validTokens[tokenDist(rng)];
  Board board = generateWinningBoard(rng, winningToken);

  // Check the board satisfies all correctness properties
  CHECK(hasOnlyValidTokens(board));
  CHECK(isTokenBalanceValid(board));
  CHECK(isGravityValid(board));
  CHECK(checkWin(board, winningToken));
}
