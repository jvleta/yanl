#pragma once

#include <algorithm>
#include <memory>
#include <ostream>
#include <ranges>
#include <vector>

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

struct PermutationResults {
  int count = 0;
  std::vector<int> indices;
  PermutationResults(int size) {
    for (int i = 0; i < size; ++i) {
      indices.push_back(i);
    }
  }
};

template <typename T>
std::pair<matrix<T>, PermutationResults> lu_decompose(matrix<T> A) {
  // https://en.wikipedia.org/wiki/LU_decomposition
  auto [M, N] = A.shape();
  PermutationResults permutation{N};
  auto &p = permutation.indices;
  p.resize(N, 1);

  auto LU = A;
  for (int i = 0; i < N; ++i) {
    int row_index_of_max_value = i;
    double max_value_in_column = 0.0;
    for (int row_index = i; row_index < N; ++row_index) {
      if (auto value = std::abs(LU(row_index, i));
          value > max_value_in_column) {
        max_value_in_column = value;
        row_index_of_max_value = row_index;
      }
    }

    if (max_value_in_column < 0.001) {
      std::cout << "you get nothing!";
    }

    if (row_index_of_max_value != i) {
      // Pivot p.
      std::swap(p[row_index_of_max_value], p[i]);

      // Pivot all the rows in A.
      for (int col_index = 0; col_index < N; ++col_index) {
        std::swap(LU(row_index_of_max_value, col_index), LU(i, col_index));
      }

      // Increment pivot count.
      ++permutation.count;
    }

    for (int row_index = i + 1; row_index < N; ++row_index) {
      LU(row_index, i) /= LU(i, i);
      for (int col_index = i + 1; col_index < N; ++col_index) {
        LU(row_index, col_index) -= (LU(row_index, i) * LU(i, col_index));
      }
    }
  }

  return {LU, permutation};
}

template <typename T> T det(matrix<T> mat) {
  auto [M, N] = mat.shape();
  auto [lu, pr] = lu_decompose(mat);
  T value = lu(0, 0);
  for (int i = 1; i < N; i++) {
    value *= lu(i, i);
  }
  return pr.count % 2 == 0 ? value : -value;
}

} // namespace yanl