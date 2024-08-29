#pragma once

#include <algorithm>
#include <ostream>
#include <vector>

namespace yanl {

template <typename T> class Vector {
private:
  std::vector<T> data;
  int size_ = 0;
  Vector() = default;

public:
  Vector(int size, T value) : size_(size) {
    data.resize(size, value);
  }
  
  void set_data(std::vector<T> data) { this->data = data; }
  int size() { return size_; }
  std::vector<T> get() { return data; }

  friend Vector<T> operator+(Vector<T> &matrix1, Vector<T> &matrix2) {
    int size = matrix1.size();
    auto result = Vector<T>(size, 0);
    for (int i = 0; i < size; ++i) {
      result(i) = matrix1(i) + matrix2(i);
    }
    return result;
  }

  friend Vector<T> operator-(Vector<T> &matrix1, Vector<T> &matrix2) {
    int size = matrix1.size();
    auto result = Vector<T>(size, 0);
    for (int i = 0; i < size; ++i) {
      result(i) = matrix1(i) - matrix2(i);
    }
    return result;
  }

  T &operator()(const int index) { return data[index]; }

  const T &operator()(const int index) const { return data[index]; }

  friend std::ostream &operator<<(std::ostream &out_stream,
                                  const Vector<T> &vec) {
    out_stream << "[ ";
    std::for_each(vec.data.begin(), vec.data.end(), [&](auto element) {
      out_stream << element;
      out_stream << " ";
    });
    out_stream << "]\n";
    return out_stream;
  }
};

template <typename T> T dot(Vector<T> vec1, Vector<T> vec2) {
  T result = 0;
  int num_elements = vec1.size();
  for (int i = 0; i < num_elements; ++i) {
    result += vec1(i) * vec2(i);
  }
  return result;
}

template <typename T> Vector<T> zeros(int size) { return Vector<T>(size, 0); }

template <typename T> Vector<T> ones(int size) { return Vector<T>(size, 1); }

template <typename T> Vector<T> linspace(T xmin, T xmax, int size) {
  auto result = Vector<T>(size, 0);
  T step_size = (xmax - xmin) / (size - 1);
  for (int i = 0; i < size; ++i) {
    result(i) = xmin + i * step_size;
  }
  return result;
}

} // namespace yanl