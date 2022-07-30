#pragma once

#include <algorithm>
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
  void set_data(std::vector<T> data) { this->data = data; }
  int size() { return size_; }
  const std::vector<T> get() { return data; }

  friend Vector<T> operator+(Vector<T> &a, Vector<T> &b) {
    int size = a.size();
    auto c = Vector<T>(size, 0);
    for (int i = 0; i < size; ++i) {
      c(i) = a(i) + b(i);
    }
    return c;
  }

  friend Vector<T> operator-(Vector<T> &a, Vector<T> &b) {
    int size = a.size();
    auto c = Vector<T>(size, 0);
    for (int i = 0; i < size; ++i) {
      c(i) = a(i) - b(i);
    }
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
};

template <typename T> T dot(Vector<T> vec1, Vector<T> vec2) {
  T result = 0;
  int n = vec1.size();
  for (int i = 0; i < n; ++i) {
    result += vec1(i) * vec2(i);
  }
  return result;
}

template <typename T> Vector<T> zeros(int size) { return Vector<T>(size, 0); }

template <typename T> Vector<T> ones(int size) { return Vector<T>(size, 1); }

template <typename T> Vector<T> linspace(T xmin, T xmax, int size) {
  auto x = Vector<T>(size, 0);
  T dx = (xmax - xmin) / (size - 1);
  for (int i = 0; i < size; ++i) {
    x(i) = xmin + i * dx;
  }
  return x;
}

} // namespace yanl