#pragma once

#include <cassert>
#include <functional>
#include <type_traits>

#include "Vector.h"

namespace yanl::integrate {

template <typename T>
T quad(std::function<T(T)> func, T left_endpoint, T right_endpoint,
       int num_panels) {
  T step_size = (right_endpoint - left_endpoint) / static_cast<T>(num_panels);

  std::vector<T> xgrid(num_panels + 1);
  for (int i = 0; i < num_panels + 1; ++i) {
    xgrid[i] = i * step_size + left_endpoint;
  }

  constexpr double one_half = 0.5;

  T sum = 0.0;
  for (int k = 1; k <= num_panels; ++k) {
    sum += (func(xgrid[k - 1]) + func(xgrid[k]));
  }

  return one_half * step_size * sum;
};

} // namespace yanl::integrate