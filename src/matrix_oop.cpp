#include "matrix_oop.h"

void Matrix::CreateMatrix() {
  matrix_ = new double *[rows_];
  matrix_[0] = new double[rows_ * cols_]{};
  for (int i = 1; i < rows_; ++i) {
    matrix_[i] = matrix_[i - 1] + cols_;
  }
}

void Matrix::Swap(Matrix &other) {
  std::swap(other.rows_, this->rows_);
  std::swap(other.cols_, this->cols_);
  std::swap(other.matrix_, this->matrix_);
}

Matrix::Matrix() noexcept : rows_(1), cols_(1) { this->CreateMatrix(); }

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < MIN_ROWS || cols_ < MIN_COLS) {
    throw std::invalid_argument(
        "A matrix must have at least 1 row and 1 column");
  }
  this->CreateMatrix();
}

Matrix::Matrix(const Matrix &other) noexcept
    : rows_(other.rows_), cols_(other.cols_) {
  this->CreateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

Matrix::Matrix(Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

Matrix &Matrix::operator=(const Matrix &other) noexcept {
  Matrix(other).Swap(*this);
  return *this;
}

Matrix &Matrix::operator=(Matrix &&other) noexcept {
  Matrix result(std::move(other));
  result.Swap(*this);
  return *this;
}

Matrix::~Matrix() noexcept {
  if (matrix_ != nullptr) {
    delete[] matrix_[0];
  }
  delete[] matrix_;
}

int Matrix::getRows() const noexcept { return rows_; }

int Matrix::getCols() const noexcept { return cols_; }

void Matrix::setRows(int new_rows) {
  if (new_rows < MIN_ROWS) {
    throw std::invalid_argument("A matrix must have at least 1 row");
  }
  if (new_rows != rows_) {
    Matrix tmp(new_rows, cols_);
    int min_rows_value = (rows_ > new_rows) ? new_rows : rows_;
    for (int i = 0; i < min_rows_value; ++i) {
      for (int j = 0; j < cols_; ++j) {
        tmp.matrix_[i][j] = matrix_[i][j];
      }
    }
    tmp.Swap(*this);
  }
}

void Matrix::setCols(int new_cols) {
  if (new_cols < MIN_COLS) {
    throw std::invalid_argument("A matrix must have at least 1 column");
  }
  if (new_cols != cols_) {
    Matrix tmp(rows_, new_cols);
    int min_cols_value = (cols_ > new_cols) ? new_cols : cols_;
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < min_cols_value; ++j) {
        tmp.matrix_[i][j] = matrix_[i][j];
      }
    }
    tmp.Swap(*this);
  }
}

bool Matrix::EqMatrix(const Matrix &other) const noexcept {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > ACCURACY) {
          return false;
        }
      }
    }
  } else {
    return false;
  }
  return true;
}
void Matrix::SumMatrix(const Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrices must have the same size to add one to another");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void Matrix::SubMatrix(const Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrices must have the same size to substract one from another");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void Matrix::MulMatrix(const Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Cannot multiplicate matrices with first.cols_ != second.rows_");
  }
  Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  result.Swap(*this);
}

Matrix Matrix::Transpose() const noexcept {
  Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

Matrix Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Cannot calculate complements for non-square matrix");
  }
  Matrix result(rows_, cols_);
  if (rows_ > 1) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        result.matrix_[i][j] = this->Minor(i, j);
        result.matrix_[i][j] *= pow(-1, (i + j + 2));
      }
    }
  } else {
    result.matrix_[0][0] = matrix_[0][0];
  }
  return result;
}

double Matrix::Minor(int i, int j) const {
  Matrix temp(rows_ - 1, cols_ - 1);
  int row_counter = 0, col_counter = 0;
  for (int r = 0; r < rows_; ++r) {
    if (i == r) continue;
    for (int c = 0; c < cols_; ++c) {
      if (j == c) continue;
      temp.matrix_[row_counter][col_counter] = matrix_[r][c];
      ++col_counter;
    }
    ++row_counter;
    col_counter = 0;
  }
  return temp.Determinant();
}

double Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Cannot calculate determinant for non-square matrix");
  }
  double result = 0.0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else {
    for (int j = 0; j < cols_; ++j) {
      double cur_minor = Minor(0, j);
      result += std::pow(-1, j + 2) * matrix_[0][j] * cur_minor;
    }
  }
  return result;
}

Matrix Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Canot calculate inverse matrix for non-square matrix");
  }
  double det = Determinant();
  if (std::abs(det) < ACCURACY) {
    throw std::invalid_argument(
        "Cannot calculate inverse matrix: determinant equals 0");
  }
  Matrix complements = CalcComplements();
  Matrix result = complements.Transpose();
  result.MulNumber(1 / det);
  return result;
}

Matrix &Matrix::operator+=(const Matrix &other) {
  SumMatrix(other);
  return *this;
}

Matrix operator+(Matrix left, const Matrix &right) { return left += right; }

Matrix &Matrix::operator-=(const Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

Matrix operator-(Matrix left, const Matrix &right) { return left -= right; }

Matrix &Matrix::operator*=(const Matrix &other) {
  MulMatrix(other);
  return *this;
}

Matrix operator*(Matrix left, const Matrix &right) { return left *= right; }

Matrix &Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

Matrix operator*(Matrix other, const double num) { return other *= num; }

Matrix operator*(const double num, Matrix other) { return other *= num; }

bool Matrix::operator==(const Matrix &other) { return EqMatrix(other); }

double &Matrix::operator()(int i, int j) & {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("Index is out of range");
  }
  return matrix_[i][j];
}

const double &Matrix::operator()(int i, int j) const & {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("Index is out of range");
  }
  return matrix_[i][j];
}