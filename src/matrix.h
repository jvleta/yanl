#pragma once

#include <algorithm>
#include <memory>
#include <ostream>
#include <ranges>
#include <vector>

#include "Vector.h"

namespace yanl {
template <typename T> class matrix {
private:
  int num_rows_ = 0;
  int num_cols_ = 0;
  int size_ = 0;

public:
  std::vector<T> data_;

  std::pair<int, int> shape() { return {num_rows_, num_cols_}; }

  int size() { return num_rows_ * num_cols_; }

  matrix(int num_rows, int num_cols) {
    size_ = num_rows * num_cols;
    num_rows_ = num_rows;
    num_cols_ = num_cols;
    data_.resize(size_, 0);
  }

  matrix(int num_rows, int num_cols, T value) {
    size_ = num_rows * num_cols;
    num_rows_ = num_rows;
    num_cols_ = num_cols;
    data_.resize(size_, value);
  }

  T &operator()(const int row, const int column) {
    return data_[num_cols_ * row + column];
  }

  const T &operator()(const int row, const int column) const {
    return data_[num_cols_ * row + column];
  }

  friend matrix<T> operator+(matrix<T> &a, matrix<T> &b) {
    auto [m, n] = a.shape();
    auto c = matrix<T>(m, n, 0);
    for (int i = 0; i < c.size(); ++i) {
      c.data_[i] = a.data_[i] + b.data_[i];
    }
    return c;
  }

  friend matrix<T> operator-(matrix<T> &a, matrix<T> &b) {
    auto [m, n] = a.shape();
    auto c = matrix<T>(m, n, 0);
    for (int i = 0; i < c.size(); ++i) {
      c.data_[i] = a.data_[i] - b.data_[i];
    }
    return c;
  }

  friend std::ostream &operator<<(std::ostream &os, const matrix<T> &matrix) {
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

template <typename T> matrix<T> zeros(int num_rows, int num_cols) {
  return matrix<T>(num_rows, num_cols, 0);
}

template <typename T> matrix<T> ones(int num_rows, int num_cols) {
  return matrix<T>(num_rows, num_cols, 1);
}

template <typename T> matrix<T> eye(int num_rows) {
  auto mat = matrix<T>(num_rows, num_rows, 0);
  for (int i = 0; i < num_rows; ++i) {
    mat(i,i) = 1;
  }
  return mat;
}

} // namespace yanl