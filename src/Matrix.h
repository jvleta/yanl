#pragma once

#include <algorithm>
#include <memory>
#include <ostream>
#include <ranges>
#include <vector>

#include "Vector.h"

namespace yanl {
template <typename T> class Matrix : public Vector<T> {
private:
  int num_rows_ = 0;
  int num_cols_ = 0;

public:
  Matrix(int num_rows, int num_cols) {
    Vector<T>::size_ = num_rows * num_cols;
    num_rows_ = num_rows;
    num_cols_ = num_cols;
    Vector<T>::data.resize(Vector<T>::size_, 0);
  }

  Matrix(int num_rows, int num_cols, T value) {
    Vector<T>::size_ = num_rows * num_cols;
    num_rows_ = num_rows;
    num_cols_ = num_cols;
    Vector<T>::data.resize(Vector<T>::size_, value);
  }

  T &operator()(const int row, const int column) {
    return Vector<T>::data[num_cols_ * row + column];
  }

  const T &operator()(const int row, const int column) const {
    return Vector<T>::data[num_cols_ * row + column];
  }
  friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix) {
    for (int i = 0; i < matrix.num_rows_; ++i) {
      os << " [ ";
      for (int j = 0; j < matrix.num_cols_; ++j) {
        os << matrix(i, j);
        os << " ";
      }
      os << "]\n";
    }
    return os;
  }
};

template <typename T> Matrix<T> zeros(int num_rows, int num_cols) {
  return Matrix<T>(num_rows, num_cols, 0);
}


template <typename T>
std::unique_ptr<Matrix<T>> ones(int num_rows, int num_cols) {
  return Matrix<T>(num_rows, num_cols, 1);
}

} // namespace yanl