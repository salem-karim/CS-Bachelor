#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <optional>
#include <vector>

using namespace std;

using Matrix = vector<vector<double>>;

// Maybe Monad with bind operation
template <typename Type> struct Maybe {
  const optional<Type> value;
  Maybe(optional<Type> val) : value(val) {}
  // typedef
  using OperationType = function<optional<Type>(const Type)>;
  // Apply operation if value exists, otherwise return nullopt
  optional<Type> apply(const OperationType operation) const {
    if (value == nullopt)
      return nullopt;
    return operation(value.value());
  }
  // bind, make new Monad and bind the operation to it
  template <typename NewType>
  Maybe<NewType> bind(function<optional<NewType>(const Type)> operation) const {
    if (value == nullopt)
      return Maybe<NewType>(nullopt);
    return Maybe<NewType>(operation(value.value()));
  }
};

// Helper functions for Maybe construction
template <typename T> Maybe<T> some(T value) {
  return Maybe<T>(make_optional(value));
}

template <typename T> Maybe<T> none() { return Maybe<T>(nullopt); }

// Structure to hold two matrices for division operation
struct MatrixPair {
  Matrix A; // Dividend matrix
  Matrix B; // Divisor matrix

  MatrixPair(const Matrix &a, const Matrix &b) : A(a), B(b) {}
  MatrixPair() = default;
};

// Structure to hold matrix analysis results
struct MatrixAnalysis {
  Matrix matrix;
  double determinant;
  Matrix cofactor_matrix;

  MatrixAnalysis(const Matrix &m, double det, const Matrix &cofactors)
      : matrix(m), determinant(det), cofactor_matrix(cofactors) {}
  MatrixAnalysis() = default;
};

// Structure to hold division context (A and B^(-1))
struct DivisionContext {
  Matrix A;
  Matrix B_inverse;

  DivisionContext(const Matrix &a, const Matrix &b_inv)
      : A(a), B_inverse(b_inv) {}
  DivisionContext() = default;
};

// Utility function to print matrix
auto printMatrix = [](const Matrix &matrix) -> void {
  cout << fixed << setprecision(4);
  for (const auto &row : matrix) {
    cout << "[ ";
    for (size_t j = 0; j < row.size(); ++j) {
      cout << setw(8) << row[j];
      if (j < row.size() - 1)
        cout << ", ";
    }
    cout << " ]" << endl;
  }
};

// Lambda to validate matrix pair for division
auto validateMatrixPair = [](const MatrixPair &pair) -> optional<MatrixPair> {
  const Matrix &A = pair.A;
  const Matrix &B = pair.B;

  // Check if matrices are not empty
  if (A.empty() || B.empty()) {
    cout << "Error: One or both matrices are empty" << endl;
    return nullopt;
  }

  const size_t cols_A = A[0].size();
  const size_t rows_B = B.size();
  const size_t cols_B = B[0].size();

  // Check if B is square (required for inversion)
  if (rows_B != cols_B) {
    cout << "Error: Matrix B must be square for division" << endl;
    return nullopt;
  }

  // Check if dimensions are compatible for multiplication A * B^(-1)
  if (cols_A != rows_B) {
    cout << "Error: Incompatible dimensions: A columns (" << cols_A
         << ") != B rows (" << rows_B << ")" << endl;
    return nullopt;
  }

  // Reject 3x3 matrices
  if (rows_B == 3 || cols_B == 3) {
    cout << "Error: 3x3 matrices are not allowed for this demonstration"
         << endl;
    return nullopt;
  }

  if (rows_B < 2) {
    cout << "Error: Matrix must be at least 2x2 for inversion" << endl;
    return nullopt;
  }

  return make_optional(pair);
};

// Function to calculate determinant and cofactors
function<pair<double, Matrix>(const Matrix &)> calculateDetAndCofactors =
    [](const Matrix &matrix) -> pair<double, Matrix> {
  size_t n = matrix.size();

  if (n == 1) {
    return {matrix[0][0], Matrix(1, vector<double>(1, 1.0))};
  }

  if (n == 2) {
    double det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    Matrix cofactors = {{matrix[1][1], -matrix[1][0]},
                        {-matrix[0][1], matrix[0][0]}};
    return {det, cofactors};
  }

  // For larger matrices
  Matrix cofactors(n, vector<double>(n));
  double det = 0.0;

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      // Create minor matrix
      Matrix minor(n - 1, vector<double>(n - 1));

      size_t minor_row = 0;
      for (size_t r = 0; r < n; ++r) {
        if (r == i)
          continue;

        size_t minor_col = 0;
        for (size_t c = 0; c < n; ++c) {
          if (c == j)
            continue;

          minor[minor_row][minor_col] = matrix[r][c];
          minor_col++;
        }
        minor_row++;
      }

      auto [minor_det, _] = calculateDetAndCofactors(minor);
      double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
      cofactors[i][j] = sign * minor_det;
    }
  }

  // Calculate determinant using first row expansion
  for (size_t j = 0; j < n; ++j) {
    det += matrix[0][j] * cofactors[0][j];
  }

  return {det, cofactors};
};

// Lambda to analyze matrix B (compute determinant and cofactors)
auto analyzeMatrixB = [](const MatrixPair &pair) -> optional<MatrixAnalysis> {
  auto [det, cofactors] = calculateDetAndCofactors(pair.B);
  return make_optional(MatrixAnalysis(pair.B, det, cofactors));
};

// Lambda to check if matrix B is invertible
auto checkInvertible =
    [](const MatrixAnalysis &analysis) -> optional<MatrixAnalysis> {
  constexpr double EPSILON = 1e-10;

  if (abs(analysis.determinant) < EPSILON) {
    cout << "Error: Matrix B is not invertible (determinant = "
         << analysis.determinant << ", approximately zero)" << endl;
    return nullopt;
  }

  cout << "Matrix B determinant: " << analysis.determinant << " (invertible)"
       << endl;
  return make_optional(analysis);
};

// Lambda to invert matrix B
auto invertMatrixB = [](const MatrixAnalysis &analysis) -> optional<Matrix> {
  const size_t n = analysis.matrix.size();

  Matrix inverse(n, vector<double>(n));
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      inverse[i][j] = analysis.cofactor_matrix[j][i] / analysis.determinant;
    }
  }

  return make_optional(inverse);
};

// Lambda to create division context
auto createDivisionContext = [](const MatrixPair &pair)
    -> function<optional<DivisionContext>(const Matrix &)> {
  return [pair](const Matrix &b_inverse) -> optional<DivisionContext> {
    return make_optional(DivisionContext(pair.A, b_inverse));
  };
};

// Lambda for matrix multiplication A * B^(-1)
auto performMatrixDivision =
    [](const DivisionContext &context) -> optional<Matrix> {
  const Matrix &A = context.A;
  const Matrix &B_inv = context.B_inverse;

  const size_t rows_A = A.size();
  const size_t cols_A = A[0].size();
  const size_t cols_B_inv = B_inv[0].size();

  Matrix result(rows_A, vector<double>(cols_B_inv, 0.0));

  for (size_t i = 0; i < rows_A; ++i) {
    for (size_t j = 0; j < cols_B_inv; ++j) {
      for (size_t k = 0; k < cols_A; ++k) {
        result[i][j] += A[i][k] * B_inv[k][j];
      }
    }
  }

  return make_optional(result);
};

// Lambda function to print the result of the division
auto printDivisionResult = [](const Matrix &result) -> void {
  cout << "Result of matrix division A / B (A * B^(-1)):" << endl;
  printMatrix(result);
  cout << endl;
};

int main() {
  cout << "=== Matrix Left Division using Maybe Monad ===" << endl << endl;

  // Test Case 1: Valid 2x2 matrices
  cout << "Test Case 1: 2x2 Matrix Division" << endl;
  Matrix A1 = {{4.0, 2.0}, {3.0, 1.0}};
  Matrix B1 = {{2.0, 1.0}, {1.0, 1.0}};

  cout << "Matrix A:" << endl;
  printMatrix(A1);
  cout << "Matrix B:" << endl;
  printMatrix(B1);
  cout << endl;

  MatrixPair pair1(A1, B1);

  auto result1 = some(pair1)
                     .bind<MatrixAnalysis>(analyzeMatrixB)
                     .bind<MatrixAnalysis>(checkInvertible)
                     .bind<Matrix>(invertMatrixB)
                     .bind<DivisionContext>(createDivisionContext(pair1))
                     .bind<Matrix>(performMatrixDivision);

  if (result1.value.has_value()) {
    printDivisionResult(result1.value.value());
  } else {
    cout << "Division failed!" << endl;
  }

  cout << "----------------------------------------" << endl << endl;

  // Test Case 2: 3x3 matrices (should be rejected)
  cout << "Test Case 2: 3x3 Matrix Division (should be rejected)" << endl;
  Matrix A2 = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 10.0}};
  Matrix B2 = {{2.0, 1.0, 0.0}, {1.0, 1.0, 1.0}, {0.0, 1.0, 2.0}};

  cout << "Matrix A:" << endl;
  printMatrix(A2);
  cout << "Matrix B:" << endl;
  printMatrix(B2);
  cout << endl;

  MatrixPair pair2(A2, B2);

  auto result2 = some(pair2)
                     .bind<MatrixPair>(validateMatrixPair)
                     .bind<MatrixAnalysis>(analyzeMatrixB)
                     .bind<MatrixAnalysis>(checkInvertible)
                     .bind<Matrix>(invertMatrixB)
                     .bind<DivisionContext>(createDivisionContext(pair2))
                     .bind<Matrix>(performMatrixDivision);

  if (result2.value.has_value()) {
    printDivisionResult(result2.value.value());
  } else {
    cout << "Division failed!" << endl;
  }

  cout << "----------------------------------------" << endl << endl;

  // Test Case 3: Singular matrix B (non-invertible)
  cout << "Test Case 3: Singular Matrix B (non-invertible)" << endl;
  Matrix A3 = {{1.0, 2.0}, {3.0, 4.0}};
  Matrix B3 = {{1.0, 2.0}, {2.0, 4.0}}; // Singular matrix

  cout << "Matrix A:" << endl;
  printMatrix(A3);
  cout << "Matrix B:" << endl;
  printMatrix(B3);
  cout << endl;

  MatrixPair pair3(A3, B3);

  auto result3 = some(pair3)
                     .bind<MatrixPair>(validateMatrixPair)
                     .bind<MatrixAnalysis>(analyzeMatrixB)
                     .bind<MatrixAnalysis>(checkInvertible)
                     .bind<Matrix>(invertMatrixB)
                     .bind<DivisionContext>(createDivisionContext(pair3))
                     .bind<Matrix>(performMatrixDivision);

  if (result3.value.has_value()) {
    printDivisionResult(result3.value.value());
  } else {
    cout << "Division failed!" << endl;
  }

  cout << "----------------------------------------" << endl << endl;

  // Test Case 4: Valid 4x4 matrices
  cout << "Test Case 4: 4x4 Matrix Division" << endl;
  Matrix A4 = {{1.0, 2.0, 3.0, 4.0},
               {5.0, 6.0, 7.0, 8.0},
               {9.0, 10.0, 11.0, 12.0},
               {13.0, 14.0, 15.0, 17.0}};

  Matrix B4 = {{4.0, 1.0, 8.0, 0.0},
               {5.0, 3.0, 9.0, 0.0},
               {0.0, 1.0, 2.0, 1.0},
               {7.0, 0.0, 5.0, 1.0}};

  cout << "Matrix A:" << endl;
  printMatrix(A4);
  cout << "Matrix B:" << endl;
  printMatrix(B4);
  cout << endl;

  MatrixPair pair4(A4, B4);

  auto result4 = some(pair4)
                     .bind<MatrixPair>(validateMatrixPair)
                     .bind<MatrixAnalysis>(analyzeMatrixB)
                     .bind<MatrixAnalysis>(checkInvertible)
                     .bind<Matrix>(invertMatrixB)
                     .bind<DivisionContext>(createDivisionContext(pair4))
                     .bind<Matrix>(performMatrixDivision);

  if (result4.value.has_value()) {
    printDivisionResult(result4.value.value());
  } else {
    cout << "Division failed!" << endl;
  }

  return 0;
}
