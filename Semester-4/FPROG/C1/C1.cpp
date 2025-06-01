#include <algorithm>
#include <random>
#include <string>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

using std::string;
using std::vector;

using Line = vector<char>;
using Board = vector<Line>;

constexpr int ROWS = 6;
constexpr int COLS = 7;
const vector<char> validTokens = {'R', 'Y'};
const vector<char> invalidTokens = {'A', 'B', 'C', 'Z', '1', '*'};

// --- Utility lambdas reused from your style ---

auto transformAll = [](const auto &source, auto fn) {
  using DestinationType = std::decay_t<decltype(source)>;
  DestinationType result;
  result.reserve(source.size());
  std::transform(source.begin(), source.end(), std::back_inserter(result), fn);
  return result;
};

auto toRange = [](int start, int end) {
  if (end <= start)
    return vector<int>{};
  vector<int> range(end - start);
  std::iota(range.begin(), range.end(), start);
  return range;
};

auto all_of_collection = [](const auto &collection, auto fn) {
  return std::all_of(collection.begin(), collection.end(), fn);
};

auto any_of_collection = [](const auto &collection, auto fn) {
  return std::any_of(collection.begin(), collection.end(), fn);
};

// Checks if token is valid
auto isValidToken = [](char c) {
  return std::find(validTokens.begin(), validTokens.end(), c) !=
         validTokens.end();
};

// Counts tokens in the board
auto countTokens = [](const Board &board, char token) {
  int count = 0;
  for (const auto &line : board)
    count += std::count(line.begin(), line.end(), token);
  return count;
};

// --- Token generators ---
auto randomValidToken = [](std::mt19937 &rng) {
  std::uniform_int_distribution<> dist(0, validTokens.size() - 1);
  return validTokens[dist(rng)];
};

auto randomInvalidToken = [](std::mt19937 &rng) {
  std::uniform_int_distribution<> dist(0, invalidTokens.size() - 1);
  return invalidTokens[dist(rng)];
};

// --- Board generation helpers ---

auto makeEmptyBoard = []() { return Board(ROWS, Line(COLS, ' ')); };

auto isGravityValid = [](const Board &board) {
  for (int col : toRange(0, COLS)) {
    bool foundEmpty = false;
    for (int row = ROWS - 1; row >= 0; --row) {
      char cell = board[row][col];
      if (cell == ' ')
        foundEmpty = true;
      else if (foundEmpty)
        return false;
    }
  }
  return true;
};

// --- Generators ---

auto generateFullyFilledCorrectBoard = [](std::mt19937 &rng) {
  Board board(ROWS, Line(COLS));
  for (int col : toRange(0, COLS)) {
    for (int row = ROWS - 1; row >= 0; --row) {
      board[row][col] = randomValidToken(rng);
    }
  }
  return board;
};

auto generateFullyFilledErroneousBoard = [](std::mt19937 &rng) {
  Board board = generateFullyFilledCorrectBoard(rng);
  std::uniform_int_distribution<> distRow(0, ROWS - 1);
  std::uniform_int_distribution<> distCol(0, COLS - 1);
  for (int i : toRange(0, 5)) {
    int r = distRow(rng), c = distCol(rng);
    board[r][c] = randomInvalidToken(rng);
  }
  return board;
};

auto generatePartiallyFilledCorrectBoard = [](std::mt19937 &rng) {
  Board board = makeEmptyBoard();
  for (int col : toRange(0, COLS)) {
    int height = rng() % (ROWS + 1);
    for (int i : toRange(0, height)) {
      board[ROWS - 1 - i][col] = randomValidToken(rng);
    }
  }

  // Fix token balance to be within 1
  int count_R = countTokens(board, 'R');
  int count_Y = countTokens(board, 'Y');
  if (std::abs(count_R - count_Y) > 1) {
    char over = count_R > count_Y ? 'R' : 'Y';
    for (int col = 0; col < COLS && std::abs(count_R - count_Y) > 1; ++col) {
      for (int row = 0; row < ROWS; ++row) {
        if (board[row][col] == over) {
          board[row][col] = ' ';
          // Shift everything above down
          for (int r = row - 1; r >= 0; --r) {
            board[r + 1][col] = board[r][col];
          }
          board[0][col] = ' ';
          over == 'R' ? --count_R : --count_Y;
          break; // Only remove one token per column per iteration
        }
      }
    }
  }

  return board;
};

auto generatePartiallyFilledErroneousBoard = [](std::mt19937 &rng) {
  Board board = generatePartiallyFilledCorrectBoard(rng);
  char add = 'R';
  for (int i : toRange(0, 3)) {
    int col = rng() % COLS;
    for (int row = ROWS - 1; row >= 0; --row) {
      if (board[row][col] == ' ') {
        board[row][col] = add;
        break;
      }
    }
  }
  return board;
};

auto generateWinningBoard = [](std::mt19937 &rng) {
  Board board = makeEmptyBoard();
  int row = rng() % ROWS;
  int startCol = rng() % (COLS - 3);
  char winner = randomValidToken(rng);
  for (int i : toRange(0, 4)) {
    board[row][startCol + i] = winner;
  }
  return board;
};

// --- Tests ---

TEST_CASE("Fully filled correct board passes checks") {
  std::mt19937 rng(42);
  Board board = generateFullyFilledCorrectBoard(rng);
  CHECK(isGravityValid(board));
  CHECK(countTokens(board, 'R') + countTokens(board, 'Y') == ROWS * COLS);
}

TEST_CASE("Fully filled erroneous board fails token check") {
  std::mt19937 rng(123);
  Board board = generateFullyFilledErroneousBoard(rng);
  CHECK_FALSE(all_of_collection(board, [](const Line &line) {
    return all_of_collection(
        line, [](char c) { return c == 'R' || c == 'Y' || c == ' '; });
  }));
}

TEST_CASE(
    "Partially filled correct board has balanced tokens and valid gravity") {
  std::mt19937 rng(456);
  Board board = generatePartiallyFilledCorrectBoard(rng);
  int r = countTokens(board, 'R');
  int y = countTokens(board, 'Y');
  CHECK(std::abs(r - y) <= 1);
  CHECK(isGravityValid(board));
}

TEST_CASE("Partially filled erroneous board has bad token balance") {
  std::mt19937 rng(789);
  Board board = generatePartiallyFilledErroneousBoard(rng);
  int r = countTokens(board, 'R');
  int y = countTokens(board, 'Y');
  CHECK(std::abs(r - y) > 1);
}

TEST_CASE("Winning board contains a win pattern") {
  std::mt19937 rng(1337);
  Board board = generateWinningBoard(rng);
  char token = 'R';
  bool win = false;
  for (const auto &line : board) {
    for (size_t i = 0; i <= line.size() - 4; ++i) {
      if (line[i] == token && line[i + 1] == token && line[i + 2] == token &&
          line[i + 3] == token) {
        win = true;
      }
    }
  }
  CHECK(win);
}
