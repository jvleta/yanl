#pragma once

#include <algorithm>
#include <ostream>
#include <vector>

namespace yanl {

template <typename T> class Vector {
private:
  std::vector<T> data;

  Vector() = default;

public:
  std::vector<T> get() { return data; }

  static Vector<T> zeros(int size) {
    auto vec = Vector<T>();
    vec.data.resize(size, 0);
    return vec;
  };

  static Vector<T> ones(int size) {
    auto vec = Vector<T>();
    vec.data.resize(size, 1);
    return vec;
  };

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

} // namespace yanl