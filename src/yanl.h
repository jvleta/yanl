#pragma once

#include <algorithm>
#include <memory>
#include <ostream>
#include <ranges>
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
  int size() { return size_; }
  const std::vector<T> get() { return data; }

  friend Vector<T> operator+(Vector<T> &a, Vector<T> &b) {
    int size = a.size();
    auto indices = std::ranges::iota_view{0, size};
    auto c = Vector<T>(size, 0);
    std::for_each(indices.begin(), indices.end(),
                  [&a, &b, &c](int i) { c(i) = a(i) + b(i); });
    return c;
  }

  friend Vector<T> operator-(Vector<T> &a, Vector<T> &b) {
    int size = a.size();
    auto indices = std::ranges::iota_view{0, size};
    auto c = Vector<T>(size, 0);
    std::for_each(indices.begin(), indices.end(),
                  [&a, &b, &c](int i) { c(i) = a(i) - b(i); });
    return c;
  }

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

  T dot(Vector<T> vec2) {
    T result = 0;
    for (int i = 0; size_; ++i) {
      result += data[i] * vec2(i);
    }
    return result;
  }
};

template <typename T> T dot(Vector<T> vec1, Vector<T> vec2) {
  return vec1.dot(vec2);
}
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

template <typename T> Vector<T> zeros(int size) { return Vector<T>(size, 0); }

template <typename T> Matrix<T> zeros(int num_rows, int num_cols) {
  return Matrix<T>(num_rows, num_cols, 0);
}

template <typename T> Vector<T> ones(int size) { return Vector<T>(size, 1); }

template <typename T>
std::unique_ptr<Matrix<T>> ones(int num_rows, int num_cols) {
  return Matrix<T>(num_rows, num_cols, 1);
}

} // namespace yanl