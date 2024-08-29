#pragma once

#include <algorithm>
#include <memory>
#include <ostream>
#include <random>
#include <vector>

namespace yanl {
template <typename T> class matrix {
private:
  int num_rows_ = 0;
  int num_cols_ = 0;
  int size_ = 0;

  std::vector<int> skyline_indices_;

  void set_skyline_indices() {
    for (int i = 0; i < num_rows_; ++i) {
      for (int j = 0; j < num_cols_; ++j) {
        skyline_indices_.push_back(num_cols_ * i + j);
      }
    }
  }

public:
  std::vector<int> get_indices() { return skyline_indices_; }
  std::vector<T> data_;

  std::pair<int, int> shape() { return {num_rows_, num_cols_}; }

  int size() { return num_rows_ * num_cols_; }

  matrix(int num_rows, int num_cols) {
    size_ = num_rows * num_cols;
    num_rows_ = num_rows;
    num_cols_ = num_cols;
    data_.resize(size_, 0);
    set_skyline_indices();
  }

  matrix(int num_rows, int num_cols, T value) {
    size_ = num_rows * num_cols;
    num_rows_ = num_rows;
    num_cols_ = num_cols;
    data_.resize(size_, value);
    set_skyline_indices();
  }

  T &operator()(const int row, const int column) {
    return data_[num_cols_ * row + column];
  }

  const T &operator()(const int row, const int column) const {
    return data_[num_cols_ * row + column];
  }

  friend matrix<T> operator+(matrix<T> &matrix1, matrix<T> &matrix2) {
    auto [num_rows, num_cols] = matrix1.shape();
    auto result = matrix<T>(num_rows, num_cols, 0);
    const auto &indices = result.get_indices();
    std::for_each(indices.begin(), indices.end(), [&](int index) {
      result.data_[index] = matrix1.data_[index] + matrix2.data_[index];
    });
    return result;
  }

  friend matrix<T> operator-(matrix<T> &matrix1, matrix<T> &matrix2) {
    auto [num_rows, num_cols] = matrix1.shape();
    auto result = matrix<T>(num_rows, num_cols, 0);
    const auto &indices = result.get_indices();
    std::for_each(indices.begin(), indices.end(), [&](int index) {
      result.data_[index] = matrix1.data_[index] - matrix2.data_[index];
    });
    return result;
  }

  friend matrix<T> operator*(matrix<T> &matrix1, matrix<T> &matrix2) {
    auto [matrix1_rows, matrix1_cols] = matrix1.shape();
    auto [matrix2_rows, matrix2_cols] = matrix2.shape();
    auto result = matrix<T>(matrix1_rows, matrix2_cols, 0);
    for (int i = 0; i < matrix1_rows; ++i) {
      for (int j = 0; j < matrix2_cols; ++j) {
        for (int k = 0; k < matrix1_rows; ++k) {
          result(i, j) += matrix1(i, k) * matrix2(k, j);
        }
      }
    }
    return result;
  }

  friend std::ostream &operator<<(std::ostream &out_stream,
                                  const matrix<T> &matrix_in) {
    for (int i = 0; i < matrix_in.num_rows_; ++i) {
      out_stream << " [ ";
      for (int j = 0; j < matrix_in.num_cols_; ++j) {
        out_stream << matrix_in(i, j);
        out_stream << " ";
      }
      out_stream << "]\n";
    }
    return out_stream;
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

template <typename T> matrix<T> rand(int num_rows, int num_cols) {
  std::random_device rand;
  std::mt19937 gen(rand());
  std::uniform_real_distribution<T> dist(0, 1);
  auto mat = matrix<T>(num_rows, num_cols);
  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < num_cols; ++j) {
      mat(i, j) = dist(gen);
    }
  }
  return mat;
}

} // namespace yanl