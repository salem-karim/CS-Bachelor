#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

using namespace std::placeholders;
using std::string;
using std::vector;

using Line = vector<char>;
using Board = vector<Line>;
using Lines = vector<Line>;

// Applies a transformation function to all elements in a container and returns
// a new container of a specific type.
template <typename DestinationType>
auto transformAll = [](const auto &source, auto fn) {
  DestinationType result;
  result.reserve(source.size());
  std::transform(source.begin(), source.end(), std::back_inserter(result), fn);
  return result;
};

// Returns a range [0, 1, ..., n-1] for a collection of size n.
auto toRange = [](const auto &collection) {
  vector<int> range(collection.size());
  std::iota(range.begin(), range.end(), 0);
  return range;
};

// Returns true if all elements of the collection satisfy the given predicate.
auto all_of_collection = [](const auto &collection, auto fn) {
  return std::all_of(collection.begin(), collection.end(), fn);
};

// Returns true if any element of the collection satisfies the given predicate.
auto any_of_collection = [](const auto &collection, auto fn) {
  return std::any_of(collection.begin(), collection.end(), fn);
};

// Converts a line of characters to a string.
auto lineToString = [](const auto &line) {
  return transformAll<string>(line,
                              [](auto const token) -> char { return token; });
};

// Converts a board to a vector of strings (each line as a string).
auto boardToLinesString = [](const auto &board) {
  return transformAll<vector<string>>(board, lineToString);
};

// Converts the whole board to a single string with newlines between rows.
auto boardToString = [](const auto &board) {
  const auto linesAsString = boardToLinesString(board);
  return std::accumulate(
      linesAsString.begin(), linesAsString.end(), string{},
      [](string acc, const string &line) { return acc + line + "\n"; });
};

// Concatenates two containers.
auto concatenate = [](const auto &first, const auto &second) {
  auto result{first};
  result.insert(result.end(), std::make_move_iterator(second.begin()),
                std::make_move_iterator(second.end()));
  return result;
};

// Concatenates three containers.
auto concatenate3 = [](const auto &first, const auto &second,
                       const auto &third) {
  return concatenate(concatenate(first, second), third);
};

using Coordinate = std::pair<int, int>;

// Accesses a value in a 2D board using a coordinate.
auto accessAtCoordinates = [](const auto &board, const Coordinate &coordinate) {
  return board[coordinate.first][coordinate.second];
};

// Projects a list of coordinates to their corresponding values in the board.
auto projectCoordinates = [](const auto &board, const auto &coordinates) {
  return transformAll<Line>(coordinates,
                            std::bind(accessAtCoordinates, board, _1));
};

// Extracts a column from the board.
auto column = [](const auto &board, const auto &columnIndex) {
  vector<char> col;
  for (const auto &row : board) {
    col.push_back(row[columnIndex]);
  }
  return col;
};

// Extracts a specific line (row) from the board.
auto line = [](const auto &board, const int lineIndex) {
  return board[lineIndex];
};

// Returns all rows (lines) of the board.
auto allLines = [](const auto &board) {
  return transformAll<Lines>(toRange(board),
                             [&board](int i) { return line(board, i); });
};

// Returns all columns of the board.
auto allColumns = [](const auto &board) {
  size_t numCols = board[0].size();
  Lines columns;
  columns.reserve(numCols);
  for (size_t col = 0; col < numCols; ++col) {
    columns.push_back(column(board, col));
  }
  return columns;
};

// Returns all diagonals of length >= 4 in both directions from the board.
auto allDiagonals = [](const Board &board) -> Lines {
  Lines diagonals;
  size_t rows = board.size();
  size_t cols = board[0].size();

  // Top-left to bottom-right diagonals
  for (size_t start_col = 0; start_col < cols; ++start_col) {
    vector<char> diagonal;
    for (size_t row = 0, col = start_col; row < rows && col < cols;
         ++row, ++col) {
      diagonal.push_back(board[row][col]);
    }
    if (diagonal.size() >= 4)
      diagonals.push_back(diagonal);
  }

  for (size_t start_row = 1; start_row < rows; ++start_row) {
    vector<char> diagonal;
    for (size_t row = start_row, col = 0; row < rows && col < cols;
         ++row, ++col) {
      diagonal.push_back(board[row][col]);
    }
    if (diagonal.size() >= 4)
      diagonals.push_back(diagonal);
  }

  // Top-right to bottom-left diagonals
  for (size_t start_col = 0; start_col < cols; ++start_col) {
    vector<char> diagonal;
    for (size_t row = 0, col = start_col;
         row < rows && col < cols && col < cols;
         ++row, col = (col == 0) ? cols : col - 1) {
      diagonal.push_back(board[row][col]);
      if (col == 0)
        break; // Avoid underflow
    }
    if (diagonal.size() >= 4)
      diagonals.push_back(diagonal);
  }

  for (size_t start_row = 1; start_row < rows; ++start_row) {
    vector<char> diagonal;
    for (size_t row = start_row, col = cols - 1; row < rows && col < cols;
         ++row, col = (col == 0) ? cols : col - 1) {
      diagonal.push_back(board[row][col]);
      if (col == 0)
        break; // Avoid underflow
    }
    if (diagonal.size() >= 4)
      diagonals.push_back(diagonal);
  }

  return diagonals;
};

// Checks if a line contains 4 or more consecutive tokens of the same type.
auto checkLineForWin = [](const Line &line, char token) {
  int count = 0;
  for (char t : line) {
    if (t == token)
      count++;
    else
      count = 0;
    if (count >= 4)
      return true;
  }
  return false;
};

// Checks if a player with a specific token has won.
auto checkWin = [](const Board &board, char token) {
  auto lines = allLines(board);
  auto columns = allColumns(board);
  auto diagonals = allDiagonals(board);
  Lines all = concatenate3(lines, columns, diagonals);
  return std::any_of(all.begin(), all.end(), [&token](const Line &line) {
    return checkLineForWin(line, token);
  });
};

// Checks whether the number of tokens between two players differs by at most 1.
auto checkTokenBalance = [](const Board &board, char token1, char token2) {
  int count1 = 0, count2 = 0;
  for (const auto &line : board) {
    count1 += std::count(line.begin(), line.end(), token1);
    count2 += std::count(line.begin(), line.end(), token2);
  }
  return std::abs(count1 - count2) <= 1;
};

// Verifies that all tokens in the board are part of the allowed set.
auto checkForCorrectTokens = [](const Board &board,
                                const vector<char> &validTokens) {
  return std::all_of(
      board.begin(), board.end(), [&validTokens](const Line &line) {
        return std::all_of(
            line.begin(), line.end(), [&validTokens](char token) {
              return std::find(validTokens.begin(), validTokens.end(), token) !=
                     validTokens.end();
            });
      });
};

// Verifies the board has expected number of rows and columns.
auto checkBoardDimensions = [](const Board &board, size_t expectedRows,
                               size_t expectedCols) {
  if (board.size() != expectedRows)
    return false;
  for (const auto &line : board) {
    if (line.size() != expectedCols)
      return false;
  }
  return true;
};

// Convenience wrappers to check for winner.
auto xWins = [](const Board &board) { return checkWin(board, 'X'); };
auto oWins = [](const Board &board) { return checkWin(board, 'O'); };

// -------------------- TEST CASES --------------------

TEST_CASE("Token balance is maintained") {
  Board board = {
      {'X', 'O', 'X', 'X', 'O', 'X', 'O'}, {'O', 'X', 'O', 'O', 'X', 'O', 'X'},
      {'X', 'O', 'X', 'X', 'O', 'X', 'O'}, {'O', 'X', 'O', 'O', 'X', 'O', 'X'},
      {'X', 'O', 'X', 'X', 'O', 'X', 'O'}, {'O', 'X', 'O', 'O', 'X', 'O', 'X'}};
  CHECK(checkTokenBalance(board, 'X', 'O'));
}

TEST_CASE("Only correct tokens are present") {
  Board board = {
      {'X', 'O', 'X', 'X', 'O', 'X', 'O'}, {'O', 'X', 'O', 'O', 'X', 'O', 'X'},
      {'X', 'O', 'X', 'X', 'O', 'X', 'O'}, {'O', 'X', 'O', 'O', 'X', 'O', 'X'},
      {'X', 'O', 'X', 'X', 'O', 'X', 'O'}, {'O', 'X', 'O', 'O', 'X', 'O', 'X'}};
  vector<char> validTokens = {'X', 'O', ' '};
  CHECK(checkForCorrectTokens(board, validTokens));
}

TEST_CASE("No incorrect tokens are present") {
  Board board = {
      {'X', 'O', 'X', 'X', 'O', 'A', 'O'}, // 'A' is invalid
      {'O', 'X', 'O', 'O', 'X', 'O', 'X'}, {'X', 'O', 'X', 'X', 'O', 'X', 'O'},
      {'O', 'X', 'O', 'O', 'X', 'O', 'X'}, {'X', 'O', 'X', 'X', 'O', 'X', 'O'},
      {'O', 'X', 'O', 'O', 'X', 'O', 'X'}};
  vector<char> validTokens = {'X', 'O', ' '};
  CHECK_FALSE(checkForCorrectTokens(board, validTokens));
}

TEST_CASE("Board dimensions are correct") {
  Board board = {
      {'X', 'O', 'X', 'X', 'O', 'X', 'O'}, {'O', 'X', 'O', 'O', 'X', 'O', 'X'},
      {'X', 'O', 'X', 'X', 'O', 'X', 'O'}, {'O', 'X', 'O', 'O', 'X', 'O', 'X'},
      {'X', 'O', 'X', 'X', 'O', 'X', 'O'}, {'O', 'X', 'O', 'O', 'X', 'O', 'X'}};
  CHECK(checkBoardDimensions(board, 6, 7));
}

TEST_CASE("Board dimensions are incorrect") {
  Board board = {
      {'X', 'O', 'X', 'X', 'O', 'X', 'O'},
      {'O', 'X', 'O', 'O', 'X', 'O', 'X'},
      {'X', 'O', 'X', 'X', 'O', 'X', 'O'},
      {'O', 'X', 'O', 'O', 'X', 'O', 'X'},
      {'X', 'O', 'X', 'X', 'O', 'X', 'O'} // missing one row
  };
  CHECK_FALSE(checkBoardDimensions(board, 6, 7));
}

TEST_CASE("Check for win condition for X") {
  Board board = {
      {'X', 'O', 'X', 'X', 'O', 'X', 'O'}, {'O', 'X', 'O', 'O', 'X', 'O', 'X'},
      {'X', 'X', 'X', 'X', 'O', 'X', 'O'}, // X wins horizontally
      {'O', 'X', 'O', 'O', 'X', 'O', 'X'}, {'X', 'O', 'X', 'X', 'O', 'X', 'O'},
      {'O', 'X', 'O', 'O', 'X', 'O', 'X'}};
  CHECK(xWins(board));
}

TEST_CASE("Check for win condition for O") {
  Board board = {{'X', 'O', 'X', 'X', 'O', 'X', 'O'},
                 {'O', 'O', 'O', 'O', 'X', 'O', 'X'}, // O wins horizontally
                 {'X', 'O', 'X', 'X', 'O', 'X', 'O'},
                 {'O', 'X', 'O', 'O', 'X', 'O', 'X'},
                 {'X', 'O', 'X', 'X', 'O', 'X', 'O'},
                 {'O', 'X', 'O', 'O', 'X', 'O', 'X'}};
  CHECK(oWins(board));
}
