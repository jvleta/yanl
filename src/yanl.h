#pragma once

#include <algorithm>
#include <memory>
#include <ostream>
#include <vector>

namespace yanl {
template <typename T> class Vector {
private:
  std::vector<T> data;
  int size_ = 0;
  Vector() = default;

public:
  Vector(int size, T value) {
    size_ = size;
    data.resize(size, value);
  }
  const std::vector<T> get() { return data; }

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

template <typename T> std::unique_ptr<Vector<T>> zeros(int size) {
  auto vec = std::make_unique<Vector<T>>(size, 0);
  return vec;
}

template <typename T> std::unique_ptr<Vector<T>> ones(int size) {
  auto vec = std::make_unique<Vector<T>>(size, 1);
  return vec;
}

} // namespace yanl