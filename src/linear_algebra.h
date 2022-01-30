#pragma once

#include "matrix.h"

namespace yanl::linear_algebra {
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

} // namespace yanl::linear_algebra