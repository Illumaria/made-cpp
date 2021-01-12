#include "matrix.h"

using namespace task;

Matrix::Matrix() : rows(1), cols(1), ptr(new double*[1]) {
  ptr[0] = new double[1];
  ptr[0][0] = 1;
}

Matrix::Matrix(size_t rows, size_t cols)
    : rows(rows), cols(cols), ptr(new double*[rows]) {
  for (size_t i = 0; i < rows; ++i) ptr[i] = new double[cols];

  for (size_t i = 0; i < rows; ++i)
    for (size_t j = 0; j < cols; ++j) ptr[i][j] = (i == j) ? 1 : 0;
}

Matrix::Matrix(const Matrix& copy)
    : rows(copy.rows), cols(copy.cols), ptr(new double*[copy.rows]) {
  for (size_t i = 0; i < rows; ++i) ptr[i] = new double[cols];

  for (size_t i = 0; i < rows; ++i)
    for (size_t j = 0; j < cols; ++j) ptr[i][j] = copy[i][j];
}

Matrix& Matrix::operator=(const Matrix& a) {
  if (&a != this) {
    if (rows != a.rows || cols != a.cols) this->resize(a.rows, a.cols);

    for (size_t i = 0; i < rows; ++i)
      for (size_t j = 0; j < cols; ++j) ptr[i][j] = a[i][j];
  }

  return *this;
}

double& Matrix::get(size_t row, size_t col) {
  if (row < 0 || row >= rows || col < 0 || col >= cols)
    throw OutOfBoundsException();
  return ptr[row][col];
}

const double& Matrix::get(size_t row, size_t col) const {
  if (row < 0 || row >= rows || col < 0 || col >= cols)
    throw OutOfBoundsException();
  return ptr[row][col];
}

void Matrix::set(size_t row, size_t col, const double& value) {
  if (row < 0 || row >= rows || col < 0 || col >= cols)
    throw OutOfBoundsException();
  ptr[row][col] = value;
}

void Matrix::resize(size_t new_rows, size_t new_cols) {
  Matrix result(new_rows, new_cols);

  for (size_t i = 0; i < new_rows; ++i)
    for (size_t j = 0; j < new_cols; ++j)
      if (i >= rows || j >= cols)
        result[i][j] = 0;
      else
        result[i][j] = ptr[i][j];

  for (size_t i = 0; i < rows; ++i) delete[] ptr[i];
  delete[] ptr;

  ptr = result.ptr;
  rows = result.rows;
  cols = result.cols;
}

double* Matrix::operator[](size_t index) { return ptr[index]; }

double* Matrix::operator[](size_t index) const { return ptr[index]; }

Matrix& Matrix::operator+=(const Matrix& a) {
  if (rows != a.rows || cols != a.cols) throw SizeMismatchException();

  for (size_t i = 0; i < rows; ++i)
    for (size_t j = 0; j < cols; ++j) ptr[i][j] = ptr[i][j] + a[i][j];

  return *this;
}

Matrix& Matrix::operator-=(const Matrix& a) {
  if (rows != a.rows || cols != a.cols) throw SizeMismatchException();

  for (size_t i = 0; i < rows; ++i)
    for (size_t j = 0; j < cols; ++j) ptr[i][j] = ptr[i][j] - a[i][j];

  return *this;
}

Matrix& Matrix::operator*=(const Matrix& a) {
  if (cols != a.rows) throw SizeMismatchException();

  Matrix result(rows, a.cols);
  size_t min_dim = rows < a.cols ? rows : a.cols;
  for (size_t i = 0; i < min_dim; ++i) result[i][i] = 0;

  for (size_t r = 0; r < cols; ++r)
    for (size_t i = 0; i < rows; ++i)
      for (size_t j = 0; j < a.cols; ++j) result[i][j] += ptr[i][r] * a[r][j];

  for (size_t i = 0; i < rows; ++i) delete[] ptr[i];
  delete[] ptr;
  ptr = result.ptr;
  rows = result.rows;
  cols = result.cols;

  return *this;
}

Matrix& Matrix::operator*=(const double& number) {
  for (size_t i = 0; i < rows; ++i)
    for (size_t j = 0; j < cols; ++j) ptr[i][j] *= number;

  return *this;
}

Matrix Matrix::operator+(const Matrix& a) const {
  if (rows != a.rows || cols != a.cols) throw SizeMismatchException();

  Matrix result(rows, cols);
  for (size_t i = 0; i < rows; ++i)
    for (size_t j = 0; j < cols; ++j) result[i][j] = ptr[i][j] + a[i][j];

  return result;
}

Matrix Matrix::operator-(const Matrix& a) const {
  if (rows != a.rows || cols != a.cols) throw SizeMismatchException();

  Matrix result(rows, cols);
  for (size_t i = 0; i < rows; ++i)
    for (size_t j = 0; j < cols; ++j) result[i][j] = ptr[i][j] - a[i][j];

  return result;
}

Matrix Matrix::operator*(const Matrix& a) const {
  if (cols != a.rows) throw SizeMismatchException();

  Matrix result(rows, a.cols);
  size_t min_dim = rows < a.cols ? rows : a.cols;
  for (size_t i = 0; i < min_dim; ++i) result[i][i] = 0;

  for (size_t r = 0; r < cols; ++r)
    for (size_t i = 0; i < rows; ++i)
      for (size_t j = 0; j < a.cols; ++j) result[i][j] += ptr[i][r] * a[r][j];

  return result;
}

Matrix Matrix::operator*(const double& number) const {
  Matrix result(*this);
  for (size_t i = 0; i < rows; ++i)
    for (size_t j = 0; j < cols; ++j) result[i][j] *= number;

  return result;
}

Matrix Matrix::operator-() const {
  Matrix result(rows, cols);
  for (size_t i = 0; i < rows; ++i)
    for (size_t j = 0; j < cols; ++j) result[i][j] = -ptr[i][j];

  return result;
}

Matrix Matrix::operator+() const {
  Matrix result(*this);

  return result;
}

double Matrix::det() const {
  if (rows != cols) throw SizeMismatchException();

  Matrix temp(*this);

  double coeff, result = 1.0;
  for (size_t row_n = 0; row_n < rows - 1; ++row_n) {
    coeff = temp[row_n][row_n];
    result *= coeff;
    for (size_t col_n = row_n; col_n < cols; ++col_n)
      temp[row_n][col_n] /= coeff;

    for (size_t next_row_n = row_n + 1; next_row_n < rows; ++next_row_n) {
      coeff = temp[next_row_n][row_n] / temp[row_n][row_n];

      for (size_t col_n = 0; col_n < cols; ++col_n)
        temp[next_row_n][col_n] -= coeff * temp[row_n][col_n];
    }
  }

  result *= temp[rows - 1][cols - 1];

  return result;
}

void Matrix::transpose() {
  Matrix result(cols, rows);

  for (size_t i = 0; i < rows; ++i)
    for (size_t j = 0; j < cols; ++j) result[j][i] = ptr[i][j];

  for (size_t i = 0; i < rows; ++i) delete[] ptr[i];
  delete[] ptr;
  ptr = result.ptr;
  size_t temp = rows;
  rows = cols;
  cols = temp;
}

Matrix Matrix::transposed() const {
  Matrix result(cols, rows);

  for (size_t i = 0; i < rows; ++i)
    for (size_t j = 0; j < cols; ++j) result[j][i] = ptr[i][j];

  return result;
}

double Matrix::trace() const {
  if (rows != cols) throw SizeMismatchException();

  double result;
  for (size_t i = 0; i < rows; ++i) result += ptr[i][i];

  return result;
}

std::vector<double> Matrix::getRow(size_t row) {
  if (row < 0 || row >= rows) throw OutOfBoundsException();

  std::vector<double> result(cols);
  for (size_t i = 0; i < cols; ++i) result[i] = ptr[row][i];

  return result;
}

std::vector<double> Matrix::getColumn(size_t column) {
  if (column < 0 || column >= cols) throw OutOfBoundsException();

  std::vector<double> result(rows);
  for (size_t i = 0; i < rows; ++i) result[i] = ptr[i][column];

  return result;
}

bool Matrix::operator==(const Matrix& a) const {
  if (rows != a.rows || cols != a.cols) return false;

  for (size_t i = 0; i < rows; ++i)
    for (size_t j = 0; j < cols; ++j)
      if ((ptr[i][j] - a[i][j]) * (ptr[i][j] - a[i][j]) > EPS * EPS)
        return false;

  return true;
}

bool Matrix::operator!=(const Matrix& a) const { return !(*this == a); }

const size_t Matrix::getRows() const { return rows; }

const size_t Matrix::getCols() const { return cols; }

Matrix task::operator*(const double& a, const Matrix& b) {
  Matrix result(b);
  return result *= a;
}

std::ostream& task::operator<<(std::ostream& output, const Matrix& matrix) {
  for (size_t i = 0; i < matrix.getRows(); ++i) {
    for (size_t j = 0; j < matrix.getCols(); ++j) output << matrix[i][j] << " ";
    output << "\n";
  }

  return output;
}

std::istream& task::operator>>(std::istream& input, Matrix& matrix) {
  size_t rows, cols;
  input >> rows >> cols;
  if (rows < 0 || cols < 0) return input;
  matrix.resize(rows, cols);

  double value;
  for (size_t i = 0; i < rows; ++i)
    for (size_t j = 0; j < cols; ++j) {
      input >> value;
      matrix[i][j] = value;
    }

  return input;
}
