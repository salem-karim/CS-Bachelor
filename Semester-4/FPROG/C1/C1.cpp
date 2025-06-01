#include <algorithm>
#include <random>
#include <string>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

using std::cout;
using std::string;
using std::vector;

using Line = vector<char>;
using Board = vector<Line>;

constexpr int ROWS = 6;
constexpr int COLS = 7;
const vector<char> validTokens = {'R', 'Y'};
const vector<char> invalidTokens = {'A', 'B', 'C', 'Z', '1', '*'};

std::mt19937 createRng() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  return std::mt19937(seed);
}

void printBoard(const Board &board) {
  size_t rows = board.size();
  size_t cols = board[0].size();

  // Print column indices
  cout << "    ";
  for (size_t col = 0; col < cols; ++col) {
    cout << col << ' ';
  }
  cout << "\n   ";
  for (size_t col = 0; col < cols; ++col) {
    cout << "--";
  }
  cout << '\n';

  // Print each row with its index
  for (size_t row = 0; row < rows; ++row) {
    cout << row << " | ";
    for (size_t col = 0; col < cols; ++col) {
      cout << board[row][col] << ' ';
    }
    cout << '\n';
  }
}

void shuffleColumns(Board &board, std::mt19937 &rng) {
  for (int col = 0; col < COLS; ++col) {
    // Extract tokens in this column (non-empty)
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

    // Place shuffled tokens at bottom (gravity)
    int fillRow = ROWS - 1;
    for (char token : tokensInCol) {
      board[fillRow--][col] = token;
    }
  }
}

char randomValidToken(std::mt19937 &rng) {
  std::uniform_int_distribution<> dist(0, 1);
  return validTokens[dist(rng)];
}

char randomInvalidToken(std::mt19937 &rng) {
  std::uniform_int_distribution<> dist(0, invalidTokens.size() - 1);
  return invalidTokens[dist(rng)];
}

Board makeEmptyBoard() { return Board(ROWS, Line(COLS, ' ')); }

bool isGravityValid(const Board &board) {
  for (int col = 0; col < COLS; ++col) {
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
}

int countTokens(const Board &board, char token) {
  int count = 0;
  for (const auto &row : board)
    count += std::count(row.begin(), row.end(), token);
  return count;
}

bool hasOnlyValidTokens(const Board &board) {
  for (const auto &row : board)
    for (char c : row)
      if (c != 'R' && c != 'Y' && c != ' ')
        return false;
  return true;
}

bool isTokenBalanceValid(const Board &board) {
  int r = countTokens(board, 'R');
  int y = countTokens(board, 'Y');
  return std::abs(r - y) <= 1;
}

bool isBoardSizeValid(const Board &board) {
  if ((int)board.size() != ROWS)
    return false;
  for (const auto &row : board)
    if ((int)row.size() != COLS)
      return false;
  return true;
}

Board generateFullyFilledCorrectBoard(std::mt19937 &rng) {
  // Create balanced tokens
  int totalCells = ROWS * COLS;
  int rCount = totalCells / 2;
  int yCount = totalCells - rCount;
  vector<char> tokens;
  tokens.insert(tokens.end(), rCount, 'R');
  tokens.insert(tokens.end(), yCount, 'Y');

  // Shuffle tokens
  std::shuffle(tokens.begin(), tokens.end(), rng);

  // Fill board column-wise bottom-up (gravity)
  Board board = makeEmptyBoard();
  int index = 0;
  for (int col = 0; col < COLS; ++col) {
    for (int row = ROWS - 1; row >= 0; --row) {
      board[row][col] = tokens[index++];
    }
  }
  return board;
}

Board generateFullyFilledErroneousBoard(std::mt19937 &rng) {
  Board board = generateFullyFilledCorrectBoard(rng);
  std::uniform_int_distribution<> distRow(0, ROWS - 1);
  std::uniform_int_distribution<> distCol(0, COLS - 1);

  // Randomly break one or more rules
  if (rng() % 2 == 0) // Break token validity
    for (int i = 0; i < 3; ++i)
      board[distRow(rng)][distCol(rng)] = randomInvalidToken(rng);

  if (rng() % 2 == 0) // Break balance
    board[0][0] = 'R';

  if (rng() % 2 == 0) // Break gravity
    board[1][1] = 'R';
  board[2][1] = ' ';

  if (rng() % 2 == 0)
    board.push_back(Line(COLS, ' ')); // empty row with correct columns

  return board;
}

Board generatePartiallyFilledCorrectBoard(std::mt19937 &rng) {
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

  // Shuffle tokens in each column independently to increase randomness
  shuffleColumns(board, rng);

  return board;
}

Board generatePartiallyFilledErroneousBoard(std::mt19937 &rng) {
  Board board = generatePartiallyFilledCorrectBoard(rng);

  // Introduce one or more errors
  if (rng() % 2 == 0) // Break balance
    board[0][0] = 'R';

  if (rng() % 2 == 0) // Break token validity
    board[0][1] = randomInvalidToken(rng);

  if (rng() % 2 == 0) // Break gravity
    board[1][2] = 'R';
  board[2][2] = ' ';

  if (rng() % 2 == 0)
    board.push_back(Line(COLS, ' ')); // empty row with correct columns

  return board;
}

Board generateWinningBoard(std::mt19937 &rng) {
  Board board = makeEmptyBoard();
  int row = rng() % ROWS;
  int startCol = rng() % (COLS - 3);
  char winner = randomValidToken(rng);
  for (int i = 0; i < 4; ++i)
    board[row][startCol + i] = winner;
  return board;
}

TEST_CASE("Fully filled correct board is valid in all respects") {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 rng(seed);
  Board board = generateFullyFilledCorrectBoard(rng);
  printBoard(board);
  CHECK(isGravityValid(board));
  CHECK(isTokenBalanceValid(board));
  CHECK(hasOnlyValidTokens(board));
  CHECK(isBoardSizeValid(board));
}

TEST_CASE("Fully filled erroneous board has at least one problem") {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 rng(seed);
  Board board = generateFullyFilledErroneousBoard(rng);
  printBoard(board);
  CHECK(!(isGravityValid(board) && isTokenBalanceValid(board) &&
          hasOnlyValidTokens(board) && isBoardSizeValid(board)));
}

TEST_CASE(
    "Partially filled correct board has balanced tokens and valid gravity") {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 rng(seed);
  Board board = generatePartiallyFilledCorrectBoard(rng);
  printBoard(board);
  CHECK(isGravityValid(board));
  CHECK(isTokenBalanceValid(board));
  CHECK(hasOnlyValidTokens(board));
  CHECK(isBoardSizeValid(board));
}

TEST_CASE("Partially filled erroneous board has at least one problem") {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 rng(seed);
  Board board = generatePartiallyFilledErroneousBoard(rng);
  printBoard(board);
  CHECK(!(isGravityValid(board) && isTokenBalanceValid(board) &&
          hasOnlyValidTokens(board) && isBoardSizeValid(board)));
}

TEST_CASE("Winning board contains a horizontal win pattern") {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 rng(seed);
  Board board = generateWinningBoard(rng);
  char token = 'R';
  bool win = false;
  for (const auto &line : board)
    for (size_t i = 0; i <= line.size() - 4; ++i)
      if (line[i] == token && line[i + 1] == token && line[i + 2] == token &&
          line[i + 3] == token)
        win = true;
  printBoard(board);
  CHECK(win);
}
