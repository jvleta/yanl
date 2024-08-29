#pragma once

#include <algorithm>
#include <numeric>

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
std::pair<matrix<T>, PermutationResults> lu_decompose(matrix<T> matrix_in) {
  // https://en.wikipedia.org/wiki/LU_decomposition
  auto [M, N] = matrix_in.shape();
  PermutationResults permutation{N};
  permutation.indices.resize(N, 1);

  auto lu_factored_matrix = matrix_in;
  for (int i = 0; i < N; ++i) {
    int row_index_of_max_value = i;
    double max_value_in_column = 0.0;
    for (int row_index = i; row_index < N; ++row_index) {
      if (auto value = std::abs(lu_factored_matrix(row_index, i));
          value > max_value_in_column) {
        max_value_in_column = value;
        row_index_of_max_value = row_index;
      }
    }

    constexpr double tolerance = 0.001;
    if (max_value_in_column < tolerance) {
      std::cout << "you get nothing!";
    }

    if (row_index_of_max_value != i) {
      // Pivot p.
      std::swap(permutation.indices[row_index_of_max_value],
                permutation.indices[i]);

      // Pivot all the rows in A.
      for (int col_index = 0; col_index < N; ++col_index) {
        std::swap(lu_factored_matrix(row_index_of_max_value, col_index),
                  lu_factored_matrix(i, col_index));
      }

      // Increment pivot count.
      ++permutation.count;
    }

    for (int row_index = i + 1; row_index < N; ++row_index) {
      lu_factored_matrix(row_index, i) /= lu_factored_matrix(i, i);
      for (int col_index = i + 1; col_index < N; ++col_index) {
        lu_factored_matrix(row_index, col_index) -=
            (lu_factored_matrix(row_index, i) *
             lu_factored_matrix(i, col_index));
      }
    }
  }

  return {lu_factored_matrix, permutation};
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

template <typename T>
matrix<T> solve(matrix<T> lhs_matrix, matrix<T> rhs_matrix) {
  auto [num_rows, num_cols] = lhs_matrix.shape();

  auto [LU, permutation_data] = lu_decompose(lhs_matrix);
  auto result = matrix<T>(num_rows, 1);

  for (int i = 0; i < num_rows; ++i) {
    result(i, 0) = rhs_matrix(permutation_data.indices[i], 0);
    for (int k = 0; k < i; ++k) {
      result(i, 0) -= LU(i, k) * result(k, 0);
    }
  }

  for (int i = num_rows - 1; i >= 0; --i) {
    for (int k = i + 1; k < num_rows; ++k) {
      result(i, 0) -= LU(i, k) * result(k, 0);
    }
    result(i, 0) /= LU(i, i);
  }

  return result;
}

template <typename T> T norm(matrix<T> &mat) {
  const auto &data = mat.data_;
  double dotproduct =
      std::inner_product(data.begin(), data.end(), data.begin(), 0);
  return std::sqrt(dotproduct);
}

} // namespace yanl::linear_algebra