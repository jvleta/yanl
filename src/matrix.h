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

  friend matrix<T> operator*(matrix<T> &a, matrix<T> &b) {
    auto [m, n] = a.shape();
    auto c = matrix<T>(m, n);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          c(i, j) += a(i, k) * b(k, j);
        }
      }
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
    mat(i, i) = 1;
  }
  return mat;
}

template <typename T>
std::pair<matrix<T>, std::vector<int>> lu_decompose(matrix<T> A) {
  // https://en.wikipedia.org/wiki/LU_decomposition
  auto [M, N] = A.shape();
  std::vector<int> p(N + 1, 1);

  auto LU = A;

  double maxA = 0.0;

  int imax = 0;
  for (int i = 0; i < N; ++i) {
    imax = i;

    for (int k = i; k < N; ++k) {
      if (auto absA = std::abs(LU(k, i)); absA > maxA) {
        maxA = absA;
        imax = k;
      }
    }

    if (maxA < 0.001) {
      std::cout << "you get nothing!";
    }

    if (imax != i) {
      // Pivot p.
      std::swap(p[imax], p[i]);

      // Pivot all the rows in A.
      for (int index = 0; index < N; ++index) {
        std::swap(LU(imax, index), LU(i, index));
      }

      // Increment pivot count.
      ++p[N];
    }

    for (int j = i + 1; j < N; j++) {
      LU(j, i) /= LU(i, i);
      for (int k = i + 1; k < N; k++) {
        LU(j, k) -= (LU(j, i) * LU(i, k));
      }
    }
  }

  return {LU, p};
}

template <typename T> T det(matrix<T> mat) {
  auto [M, N] = mat.shape();
  auto [lu, p] = lu_decompose(mat);
  T value = lu(0, 0);
  for (int i = 1; i < N; i++) {
    value *= lu(i, i);
  }
  return (p[N] - N) % 2 == 0 ? value : -value;
}

} // namespace yanl