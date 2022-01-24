#pragma once

#include <algorithm>
#include <memory>
#include <ostream>
#include <vector>

namespace yanl {
template <typename T> class Vector {
protected:
  std::vector<T> data;
  int size_ = 0;
  Vector() = default;

public:
  Vector(int size, T value) {
    size_ = size;
    data.resize(size, value);
  }
  const std::vector<T> get() { return data; }

  T &operator()(const int index) { return data[index]; }

  const T &operator()(const int index) const { return data[index]; }

  friend std::ostream &operator<<(std::ostream &os, const Vector<T> &vec) {
    os << "[ ";
    std::for_each(vec.data.begin(), vec.data.end(), [&](auto element) {
      os << element;
      os << " ";
    });
    os << "]\n";
    return os;
  }
};

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

// element access (row major indexation)
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

template <typename T> std::unique_ptr<Vector<T>> zeros(int size) {
  auto vec = std::make_unique<Vector<T>>(size, 0);
  return vec;
}

template <typename T>
std::unique_ptr<Matrix<T>> zeros(int num_rows, int num_cols) {
  auto matrix = std::make_unique<Matrix<T>>(num_rows, num_cols, 0);
  return matrix;
}

template <typename T> std::unique_ptr<Vector<T>> ones(int size) {
  auto vec = std::make_unique<Vector<T>>(size, 1);
  return vec;
}

template <typename T>
std::unique_ptr<Matrix<T>> ones(int num_rows, int num_cols) {
  auto matrix = std::make_unique<Matrix<T>>(num_rows, num_cols, 1);
  return matrix;
}

} // namespace yanl