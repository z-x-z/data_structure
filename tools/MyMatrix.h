#ifndef TOOLS_MYMATRIX_H
#define TOOLS_MYMATRIX_H

#include "tools/DescException.h"
#include <vector>
#include <sstream>  
#include <iostream>
#include <cstring>

template <typename T>
class Matrix
{
private:
  unsigned int rows, cols;
  std::vector<std::vector<T>> matrix;

  void trimToSize(unsigned int _rows, unsigned int _cols)
  {
    rows = _rows;
    cols = _cols;
    matrix.resize(_rows);
    for (int i = 0; i < _rows; i++)
      matrix[i].resize(_cols);
  }

public:
  Matrix(unsigned _rows, unsigned _cols) : rows(_rows), cols(_cols), matrix(rows, std::vector<T>(cols))
  {
  }

  Matrix(unsigned n) : Matrix(n, n)
  {
  }

  Matrix() : Matrix(0)
  {
  }

  Matrix(const std::vector<std::vector<T>> &_matrix) : rows(_matrix.size()), cols(_matrix[0].size()), matrix(_matrix)
  {
  }

  Matrix(const Matrix<T> &m) : Matrix(m.matrix)
  {
  }

  Matrix(unsigned rows, unsigned cols, const std::vector<T> &elemnts) : Matrix(rows, cols)
  {
    int count = 0;
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++)
        matrix[i][j] = elemnts[count++];
  }

  Matrix(unsigned _rows, unsigned _cols, T value) : rows(_rows), cols(_cols), matrix(rows, std::vector<T>(cols, value))
  {
  }

  inline std::vector<T> &operator[](unsigned _rows)
  {
    if (_rows >= rows)
      throw ArrayIndexOutofRangeException();
    return matrix[_rows];
  }
  inline const std::vector<T> &operator[](unsigned _rows) const
  {
    if (_rows >= rows)
      throw ArrayIndexOutofRangeException();
    return matrix[_rows];
  }
  Matrix<T> operator+(const Matrix &m) const
  {
    if (rows != m.rows || cols != m.cols)
      throw IllegalOperationException(); // 处理异常
    Matrix<T> result(rows, cols);
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++)
        result.matrix[i][j] = matrix[i][j] + m.matrix[i][j];
    return result;
  }
  Matrix<T> operator-(const Matrix &m) const
  {
    if (rows != m.rows || cols != m.cols)
      throw IllegalOperationException(); // 处理异常
    Matrix<T> result(rows, cols);
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++)
        result.matrix[i][j] = matrix[i][j] + m.matrix[i][j];
    return result;
  }
  Matrix<T> operator*(const Matrix &m) const
  {
    if (cols != m.rows)
      throw IllegalOperationException(); // 处理异常
    Matrix<T> result(rows, m.cols);
    for (int i = 0; i < result.rows; i++)
      for (int j = 0; j < result.cols; j++)
      {
        T tmp = 0;
        for (int k = 0; k < cols; k++)
          tmp += matrix[i][k] * m.matrix[k][j];
        result.matrix[i][j] = tmp;
      }
    return result;
  }
  Matrix<T> operator^(int n) const
  {
    if (rows != cols)
      throw IllegalOperationException();
    if (n <= 2)
    {
      if (n == 2)
        return (*this) * (*this);
      else
        return *this;
    }
    else
    {
      // M^n = (M^(n/2))^2
      if (n % 2 == 0)
        return ((*this) ^ (n / 2)) ^ 2;
      else
        return (((*this) ^ (n / 2)) ^ 2) * (*this);
    }
  }

  inline Matrix<T> pow(int n) const
  {
    return (*this) ^ n;
  }
  Matrix<T> inverse() const
  {
    if (rows != cols)
      throw IllegalOperationException();
    Matrix<T> inverseResult(rows, cols);
    /*
    TO DO
    */
    return inverseResult;
  }

  friend std::ostream &operator<<(std::ostream &os, const Matrix &m)
  {
    os << "[ ";
    for (int i = 0; i < m.rows; i++)
    {
      if (i != 0)
        os << "\n  ";
      for (int j = 0; j < m.cols; j++)
        os << m.matrix[i][j] << " ";
    }
    os << "]\n";
    return os;
  }
  friend std::istream &operator>>(std::istream &is, Matrix &m)
  {
    int _rows, _cols;
    is >> _rows >> _cols;
    m.trimToSize(_rows, _cols);
    for (int i = 0; i < _rows; i++)
      for (int j = 0; j < _cols; j++)
        is >> m.matrix[i][j];
    return is;
  }

  std::string toString()
  {
    std::stringstream s; // 需要引入头文件<sstream>
    s << (*this);
    return s.str();
  }

  void rowExchange(unsigned row1, unsigned row2)
  {
    if (row1 >= rows || row2 >= rows)
      throw ArrayIndexOutofRangeException();
    if (row1 != row2)
    {
      auto v1 = std::move(matrix[row1]);
      matrix[row1] = matrix[row2];
      matrix[row2] = v1;
    }
  }

  static Matrix<T> zero(unsigned n)
  {
    return Matrix<T>(n, n, 0);
  }
  static Matrix<T> eye(unsigned n)
  {
    Matrix<T> eyeMatrix(n, n, 0);
    for (int i = 0; i < n; i++)
      eyeMatrix.matrix[i][i] = 1;
    return eyeMatrix;
  }
};

#endif
