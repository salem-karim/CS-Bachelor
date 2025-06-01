#pragma once
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using std::vector;

using Line = vector<char>;
using Board = vector<Line>;
using Lines = vector<Line>;

constexpr int ROWS = 6;
constexpr int COLS = 7;
const vector<char> validTokens = {'R', 'Y'};

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

auto checkTokenBalance = [](const Board &board, char token1, char token2) {
  int count1 = 0, count2 = 0;
  for (const auto &line : board) {
    count1 += std::count(line.begin(), line.end(), token1);
    count2 += std::count(line.begin(), line.end(), token2);
  }
  return std::abs(count1 - count2) <= 1;
};

// Applies a transformation function to all elements in a container and returns
// a new container of a specific type.
template <typename DestinationType>
auto transformAll = [](const auto &source, auto fn) {
  DestinationType result;
  result.reserve(source.size());
  std::transform(source.begin(), source.end(), std::back_inserter(result), fn);
  return result;
};

auto toRange = [](const auto &collection) {
  vector<int> range(collection.size());
  std::iota(range.begin(), range.end(), 0);
  return range;
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

  // \ Direction (top-left to bottom-right)
  for (int k = 0; k <= static_cast<int>(rows + cols - 2); ++k) {
    std::vector<char> diagonal;
    for (int row = 0; row <= k; ++row) {
      int col = k - row;
      if (row < rows && col < cols)
        diagonal.push_back(board[row][col]);
    }
    if (diagonal.size() >= 4)
      diagonals.push_back(diagonal);
  }

  // / Direction (top-right to bottom-left)
  for (int k = 1 - static_cast<int>(cols); k < static_cast<int>(rows); ++k) {
    std::vector<char> diagonal;
    for (int row = 0; row < rows; ++row) {
      int col = row - k;
      if (col >= 0 && col < static_cast<int>(cols))
        diagonal.push_back(board[row][col]);
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

auto checkWin = [](const Board &board, char token) {
  auto lines = allLines(board);
  auto columns = allColumns(board);
  auto diagonals = allDiagonals(board);
  Lines all = concatenate3(lines, columns, diagonals);
  return std::any_of(all.begin(), all.end(), [&token](const Line &line) {
    return checkLineForWin(line, token);
  });
};

auto printBoard = [](const Board &board) {
  size_t rows = board.size();
  size_t cols = board[0].size();

  // Print column indices
  std::cout << "    ";
  for (size_t col = 0; col < cols; ++col) {
    std::cout << col << ' ';
  }
  std::cout << "\n   ";
  for (size_t col = 0; col < cols; ++col) {
    std::cout << "--";
  }
  std::cout << '\n';

  // Print each row with its index
  for (size_t row = 0; row < rows; ++row) {
    std::cout << row << " | ";
    for (size_t col = 0; col < cols; ++col) {
      std::cout << board[row][col] << ' ';
    }
    std::cout << '\n';
  }
};

auto makeEmptyBoard = []() { return Board(ROWS, Line(COLS, ' ')); };

auto isGravityValid = [](const Board &board) {
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
};

auto countTokens = [](const Board &board, char token) {
  int count = 0;
  for (const auto &row : board)
    count += std::count(row.begin(), row.end(), token);
  return count;
};

auto hasOnlyValidTokens = [](const Board &board) {
  for (const auto &row : board)
    for (char c : row)
      if (c != 'R' && c != 'Y' && c != ' ')
        return false;
  return true;
};

auto isTokenBalanceValid = [](const Board &board) {
  int r = countTokens(board, 'R');
  int y = countTokens(board, 'Y');
  return std::abs(r - y) <= 1;
};
