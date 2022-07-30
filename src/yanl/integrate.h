#pragma once

#include <cassert>
#include <functional>
#include <type_traits>

#include "Vector.h"

namespace yanl::integrate {

template <typename T>
T quad(std::function<T(T)> func, T a, T b, int num_panels) {
  T dx = (b - a) / static_cast<T>(num_panels);

  std::vector<T> x(num_panels + 1);
  for (int i = 0; i < num_panels + 1; ++i) {
    x[i] = i * dx + a;
  }

  T sum = 0.0;
  for (int k = 1; k <= num_panels; ++k) {
    sum += (func(x[k-1]) + func(x[k]));
  }

  return 0.5 * dx * sum;
};

} // namespace yanl::integrate