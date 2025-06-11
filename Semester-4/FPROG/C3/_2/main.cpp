#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

using Matrix = vector<vector<double>>;

// Result Monad with bool, the value and err message
template <typename Type> struct Result {
  bool is_success;
  Type value;
  string error_message;

  // Constructor for success
  Result(Type val) : is_success(true), value(val), error_message("") {}

  // Constructor for error
  Result(const string &error)
      : is_success(false), value(Type{}), error_message(error) {}

  // Monadic bind operation
  template <typename otherType>
  Result<otherType>
  bind(function<Result<otherType>(const Type &)> operation) const {
    if (!is_success) {
      return Result<otherType>(error_message);
    }
    return operation(value);
  }

  // Map operation (transforms value if successful)
  template <typename otherType>
  Result<otherType> map(function<otherType(const Type &)> transform) const {
    if (!is_success) {
      return Result<otherType>(error_message);
    }
    return Result<otherType>(transform(value));
  }
};

// Helper function to create success Result
template <typename T> Result<T> success(T value) { return Result<T>(value); }

// Helper function to create error Result
template <typename T> Result<T> error(const string &message) {
  return Result<T>(message);
}

// Utility function to print matrix with fixed setprecision
auto printMatrix = [](const Matrix &matrix) -> void {
  // sets precision for the out stream
  cout << fixed << setprecision(4);
  for (const auto &row : matrix) {
    cout << "[ ";
    for (size_t j = 0; j < row.size(); ++j) {
      // sets width to align everything
      cout << setw(8) << row[j];
      if (j < row.size() - 1)
        cout << ", ";
    }
    cout << " ]" << endl;
  }
};

// Function to validate matrix dimensions no 3x3 Matrices
auto validateMatrix = [](const Matrix &matrix) -> Result<Matrix> {
  if (matrix.empty()) {
    return error<Matrix>("Matrix is empty");
  }

  size_t n = matrix.size();

  // Check if matrix is square
  for (const auto &row : matrix) {
    if (row.size() != n) {
      return error<Matrix>("Matrix is not square");
    }
  }

  // Reject 3x3 matrices as per requirement
  if (n == 3) {
    return error<Matrix>("3x3 matrices are not allowed for this demonstration");
  }

  if (n < 2) {
    return error<Matrix>("Matrix must be at least 2x2 for inversion");
  }

  return success(matrix);
};

// calculating the Determinant and Cofactors together,
// to avoid going through the whole matrix twice
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

  // For larger matrices, we need to calculate all cofactors
  Matrix cofactors(n, vector<double>(n));
  double det = 0.0;

  // Calculate cofactors for all positions
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      // Create minor matrix by removing row i and column j
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

      // Recursively calculate minor determinant
      auto [minor_det, _] = calculateDetAndCofactors(minor);

      // Calculate cofactor with alternating signs
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

// Structure to hold matrix computation results
struct MatrixAnalysis {
  Matrix matrix;
  double determinant;
  Matrix cofactor_matrix;

  MatrixAnalysis(const Matrix &m, double det, const Matrix &cofactors)
      : matrix(m), determinant(det), cofactor_matrix(cofactors) {}

  // Default constructor needed for Result template
  MatrixAnalysis() = default;
};

// Function to check if matrix is invertible using precomputed determinant
auto checkInvertible =
    [](const MatrixAnalysis &analysis) -> Result<MatrixAnalysis> {
  const double EPSILON = 1e-10;

  if (abs(analysis.determinant) < EPSILON) {
    stringstream ss;
    ss << "Matrix is not invertible (determinant = " << analysis.determinant
       << ", approximately zero)";
    return error<MatrixAnalysis>(ss.str());
  }

  cout << "Matrix determinant: " << analysis.determinant << " (invertible)"
       << endl;
  return success(analysis);
};

// Matrix inversion using precomputed cofactor matrix and determinant
auto invertMatrix = [](const MatrixAnalysis &analysis) -> Result<Matrix> {
  size_t n = analysis.matrix.size();

  // Create inverse by transposing cofactor matrix and dividing by determinant
  // (This combines transpose and scalar division in a single loop)
  Matrix inverse(n, vector<double>(n));
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      inverse[i][j] = analysis.cofactor_matrix[j][i] /
                      analysis.determinant; // Note: j,i for transpose
    }
  }

  return success(inverse);
};

// Function to compute matrix analysis (determinant + cofactors)
auto analyzeMatrix = [](const Matrix &matrix) -> Result<MatrixAnalysis> {
  auto [det, cofactors] = calculateDetAndCofactors(matrix);
  return success(MatrixAnalysis(matrix, det, cofactors));
};

// Main function to demonstrate usage
int main() {
  cout << "=== Optimized Matrix Inversion with Cofactor Method Demo ===" << endl
       << endl;

  // Test Case 1: Valid 2x2 matrix
  cout << "Test Case 1: 2x2 Matrix" << endl;
  Matrix matrix1 = {{2.0, 1.0}, {1.0, 1.0}};

  cout << "Original matrix:" << endl;
  printMatrix(matrix1);
  cout << endl;

  auto result1 = success(matrix1)
                     .bind<Matrix>(validateMatrix)
                     .bind<MatrixAnalysis>(analyzeMatrix)
                     .bind<MatrixAnalysis>(checkInvertible)
                     .bind<Matrix>(invertMatrix);

  if (result1.is_success) {
    cout << "Inverted matrix:" << endl;
    printMatrix(result1.value);
  } else {
    cout << "Error: " << result1.error_message << endl;
  }
  cout << endl << "----------------------------------------" << endl << endl;

  // Test Case 2: 3x3 matrix (should be rejected)
  cout << "Test Case 2: 3x3 Matrix (should be rejected)" << endl;
  Matrix matrix2 = {{1.0, 2.0, 3.0}, {0.0, 1.0, 4.0}, {5.0, 6.0, 0.0}};

  cout << "Original matrix:" << endl;
  printMatrix(matrix2);
  cout << endl;

  auto result2 = success(matrix2)
                     .bind<Matrix>(validateMatrix)
                     .bind<MatrixAnalysis>(analyzeMatrix)
                     .bind<MatrixAnalysis>(checkInvertible)
                     .bind<Matrix>(invertMatrix);

  if (result2.is_success) {
    cout << "Inverted matrix:" << endl;
    printMatrix(result2.value);
  } else {
    cout << "Error: " << result2.error_message << endl;
  }
  cout << endl << "----------------------------------------" << endl << endl;

  // Test Case 3: Singular matrix (non-invertible)
  cout << "Test Case 3: Singular 2x2 Matrix (non-invertible)" << endl;
  Matrix matrix3 = {
      {1.0, 2.0}, {2.0, 4.0} // Second row is 2 times the first row
  };

  cout << "Original matrix:" << endl;
  printMatrix(matrix3);
  cout << endl;

  auto result3 = success(matrix3)
                     .bind<Matrix>(validateMatrix)
                     .bind<MatrixAnalysis>(analyzeMatrix)
                     .bind<MatrixAnalysis>(checkInvertible)
                     .bind<Matrix>(invertMatrix);

  if (result3.is_success) {
    cout << "Inverted matrix:" << endl;
    printMatrix(result3.value);
  } else {
    cout << "Error: " << result3.error_message << endl;
  }
  cout << endl << "----------------------------------------" << endl << endl;

  // Test Case 4: Valid 4x4 matrix
  cout << "Test Case 4: 4x4 Matrix" << endl;
  Matrix matrix4 = {{4.0, 1.0, 0.0, 0.0},
                    {1.0, 3.0, 1.0, 0.0},
                    {0.0, 1.0, 2.0, 1.0},
                    {0.0, 0.0, 1.0, 1.0}};

  cout << "Original matrix:" << endl;
  printMatrix(matrix4);
  cout << endl;

  auto result4 = success(matrix4)
                     .bind<Matrix>(validateMatrix)
                     .bind<MatrixAnalysis>(analyzeMatrix)
                     .bind<MatrixAnalysis>(checkInvertible)
                     .bind<Matrix>(invertMatrix);

  if (result4.is_success) {
    cout << "Inverted matrix:" << endl;
    printMatrix(result4.value);
  } else {
    cout << "Error: " << result4.error_message << endl;
  }

  return 0;
}
