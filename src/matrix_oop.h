#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>

#define MIN_ROWS 1
#define MIN_COLS 1
#define ACCURACY 1E-7

class Matrix {
 private:
  int rows_;
  int cols_;
  double** matrix_;

 protected:
  void CreateMatrix();
  void Swap(Matrix& other);
  double Minor(int i, int j) const;

 public:
  Matrix() noexcept;
  explicit Matrix(int rows, int cols);
  Matrix(const Matrix& other) noexcept;
  Matrix(Matrix&& other) noexcept;
  Matrix& operator=(const Matrix& other) noexcept;
  Matrix& operator=(Matrix&& other) noexcept;
  ~Matrix() noexcept;

  int getRows() const noexcept;
  int getCols() const noexcept;
  void setRows(int new_rows);
  void setCols(int new_cols);

  bool EqMatrix(const Matrix& other) const noexcept;
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const Matrix& other);
  Matrix Transpose() const noexcept;
  Matrix CalcComplements() const;
  double Determinant() const;
  Matrix InverseMatrix() const;

  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  Matrix& operator*=(const double num);
  bool operator==(const Matrix& other);

  double& operator()(int i, int j) &;
  double& operator()(int i, int j) && = delete;
  const double& operator()(int i, int j) const&;
  const double& operator()(int i, int j) const&& = delete;
};

Matrix operator+(Matrix left, const Matrix& right);
Matrix operator-(Matrix left, const Matrix& right);
Matrix operator*(Matrix left, const Matrix& right);
Matrix operator*(Matrix other, const double num);
Matrix operator*(const double num, Matrix other);
