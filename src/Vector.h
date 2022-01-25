#pragma once

#include <algorithm>
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
};

template <typename T> T dot(Vector<T> vec1, Vector<T> vec2) {
  T result = 0;
  int n = vec1.size();
  for (int i = 0; n; ++i) {
    result += vec1(i) * vec2(i);
  }
  return result;
}

template <typename T> Vector<T> zeros(int size) { return Vector<T>(size, 0); }

template <typename T> Vector<T> ones(int size) { return Vector<T>(size, 1); }


} // namespace yanl