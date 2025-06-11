#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// 1. Define a simple Matrix type and Result monad
using Matrix = vector<vector<double>>;

template <typename T> struct Result {
  bool is_success;
  T value;
  string error_message;

  // Constructor for success
  Result(T val) : is_success(true), value(val), error_message("") {}

  // Constructor for error
  Result(const string &error)
      : is_success(false), value(T{}), error_message(error) {}

  // Monadic bind operation
  template <typename U>
  Result<U> bind(function<Result<U>(const T &)> operation) const {
    if (!is_success) {
      return Result<U>(error_message);
    }
    return operation(value);
  }

  // Map operation (transforms value if successful)
  template <typename U> Result<U> map(function<U(const T &)> transform) const {
    if (!is_success) {
      return Result<U>(error_message);
    }
    return Result<U>(transform(value));
  }
};

// Helper function to create success Result
template <typename T> Result<T> success(T value) { return Result<T>(value); }

// Helper function to create error Result
template <typename T> Result<T> error(const string &message) {
  return Result<T>(message);
}

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

// Function to validate matrix dimensions
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

// 2. Implement determinant function
function<double(const Matrix &)> calculateDeterminant =
    [](const Matrix &matrix) -> double {
  size_t n = matrix.size();

  if (n == 1) {
    return matrix[0][0];
  }

  if (n == 2) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
  }

  // For larger matrices, use cofactor expansion along first row
  double det = 0.0;
  for (size_t j = 0; j < n; ++j) {
    // Create minor matrix (remove row 0 and column j)
    Matrix minor(n - 1, vector<double>(n - 1));
    for (size_t r = 1; r < n; ++r) {
      size_t minor_col = 0;
      for (size_t c = 0; c < n; ++c) {
        if (c != j) {
          minor[r - 1][minor_col] = matrix[r][c];
          minor_col++;
        }
      }
    }

    // Recursive call for minor determinant
    double minor_det = calculateDeterminant(minor);
    double cofactor = ((j % 2 == 0) ? 1 : -1) * matrix[0][j] * minor_det;
    det += cofactor;
  }

  return det;
};

// Function to check if matrix is invertible
auto checkInvertible = [](const Matrix &matrix) -> Result<Matrix> {
  double det = calculateDeterminant(matrix);
  const double EPSILON = 1e-10;

  if (abs(det) < EPSILON) {
    stringstream ss;
    ss << "Matrix is not invertible (determinant = " << det
       << ", approximately zero)";
    return error<Matrix>(ss.str());
  }

  cout << "Matrix determinant: " << det << " (invertible)" << endl;
  return success(matrix);
};

// Helper function to create identity matrix
auto createIdentityMatrix = [](size_t n) -> Matrix {
  Matrix identity(n, vector<double>(n, 0.0));
  for (size_t i = 0; i < n; ++i) {
    identity[i][i] = 1.0;
  }
  return identity;
};

// 3. Immutable function to invert matrix using Gaussian elimination
auto invertMatrix = [](const Matrix &matrix) -> Result<Matrix> {
  size_t n = matrix.size();
  const double EPSILON = 1e-10;

  // Create augmented matrix [A | I]
  Matrix augmented(n, vector<double>(2 * n));

  // Fill the augmented matrix
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      augmented[i][j] = matrix[i][j];             // Original matrix
      augmented[i][j + n] = (i == j) ? 1.0 : 0.0; // Identity matrix
    }
  }

  // Forward elimination to get row echelon form
  for (size_t pivot = 0; pivot < n; ++pivot) {
    // Find the row with maximum element in current column (partial pivoting)
    size_t max_row = pivot;
    for (size_t i = pivot + 1; i < n; ++i) {
      if (abs(augmented[i][pivot]) > abs(augmented[max_row][pivot])) {
        max_row = i;
      }
    }

    // Swap rows if needed
    if (max_row != pivot) {
      swap(augmented[pivot], augmented[max_row]);
    }

    // Check for zero pivot
    if (abs(augmented[pivot][pivot]) < EPSILON) {
      return error<Matrix>("Matrix inversion failed: zero pivot encountered");
    }

    // Scale pivot row
    double pivot_val = augmented[pivot][pivot];
    for (size_t j = 0; j < 2 * n; ++j) {
      augmented[pivot][j] /= pivot_val;
    }

    // Eliminate column entries below pivot
    for (size_t i = pivot + 1; i < n; ++i) {
      double factor = augmented[i][pivot];
      for (size_t j = 0; j < 2 * n; ++j) {
        augmented[i][j] -= factor * augmented[pivot][j];
      }
    }
  }

  // Back substitution to get reduced row echelon form
  for (int pivot = n - 1; pivot >= 0; --pivot) {
    for (int i = pivot - 1; i >= 0; --i) {
      double factor = augmented[i][pivot];
      for (size_t j = 0; j < 2 * n; ++j) {
        augmented[i][j] -= factor * augmented[pivot][j];
      }
    }
  }

  // Extract the inverse matrix from the right half of augmented matrix
  Matrix inverse(n, vector<double>(n));
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      inverse[i][j] = augmented[i][j + n];
    }
  }

  return success(inverse);
};

// 4. Main function to demonstrate usage
int main() {
  cout << "=== Matrix Inversion with Result Monad Demo ===" << endl << endl;

  // Test Case 1: Valid 2x2 matrix
  cout << "Test Case 1: 2x2 Matrix" << endl;
  Matrix matrix1 = {{2.0, 1.0}, {1.0, 1.0}};

  cout << "Original matrix:" << endl;
  printMatrix(matrix1);
  cout << endl;

  auto result1 = success(matrix1)
                     .bind<Matrix>(validateMatrix)
                     .bind<Matrix>(checkInvertible)
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
                     .bind<Matrix>(checkInvertible)
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
                     .bind<Matrix>(checkInvertible)
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
                     .bind<Matrix>(checkInvertible)
                     .bind<Matrix>(invertMatrix);

  if (result4.is_success) {
    cout << "Inverted matrix:" << endl;
    printMatrix(result4.value);
  } else {
    cout << "Error: " << result4.error_message << endl;
  }

  return 0;
}
