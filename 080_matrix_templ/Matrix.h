#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!

template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix();
  Matrix(int r, int c);
  Matrix(const Matrix & rhs);
  Matrix & operator=(const Matrix & rhs);
  int getRows() const;
  int getColumns() const;
  const std::vector<T> & operator[](int index) const;
  std::vector<T> & operator[](int index);
  bool operator==(const Matrix & rhs) const;
  Matrix operator+(const Matrix & rhs) const;

  template<typename R>
  friend std::ostream & operator<<(std::ostream & s, const Matrix<R> & rhs);
};

template<typename T>
Matrix<T>::Matrix() : numRows(0), numColumns(0) {
}

template<typename T>
Matrix<T>::Matrix(int r, int c) : numRows(r), numColumns(c) {
  rows.resize(r);
  for (int i = 0; i < r; i++) {
    rows[i].resize(c);
  }
}

template<typename T>
Matrix<T>::Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
  rows.resize(rhs.numRows);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      rows[i].push_back(rhs.rows[i][j]);
    }
  }
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix & rhs) {
  if (this == &rhs) {
    return *this;
  }
  if (numRows != 0) {
    rows.clear();
  }
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows.resize(rhs.numRows);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      rows[i].push_back(rhs.rows[i][j]);
    }
  }
  return *this;
}

template<typename T>
int Matrix<T>::getRows() const {
  return this->numRows;
}

template<typename T>
int Matrix<T>::getColumns() const {
  return this->numColumns;
}

template<typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return this->rows[index];
}

template<typename T>
std::vector<T> & Matrix<T>::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return this->rows[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix & rhs) const {
  if (numRows != rhs.numRows || numColumns != rhs.numColumns)
    return false;

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      if (rows[i] != rhs.rows[i])
        return false;
    }
  }
  return true;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  Matrix result(numRows, numColumns);

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      result.rows[i][j] = (rows[i][j] + rhs.rows[i][j]);
    }
  }

  return result;
}

template<typename R>
std::ostream & operator<<(std::ostream & s, const Matrix<R> & rhs) {
  s << "[ ";
  std::string delim;
  for (int i = 0; i < rhs.getRows(); i++) {
    s << delim << "{";
    std::string delimin;
    for (typename std::vector<R>::const_iterator it = rhs.rows[i].begin();
         it != rhs.rows[i].end();
         ++it) {
      s << delimin << *it;
      delimin = ", ";
    }
    delim = "},\n";
    if (i == rhs.getRows() - 1)
      s << "}";
  }
  s << " ]";
  return s;
}

#endif
