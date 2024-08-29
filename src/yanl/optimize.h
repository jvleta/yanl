#pragma once

#include <functional>
#include <tuple>

namespace yanl::optimize {
struct Options {
  static constexpr int DEFAULT_MAX_ITERATIONS = 1000;
  static constexpr double DEFAULT_TOLERANCE = 1e-6;
  int max_iterations = DEFAULT_MAX_ITERATIONS;
  double tolerance = DEFAULT_TOLERANCE;
};

struct Output {
  double root = std::numeric_limits<double>::max();
  int iterations = -1;
  bool converged = false;
};

Output bisect(std::function<double(double)> func,
              std::pair<double, double> bounds, Options opts) {
  auto [left_endpoint, right_endpoint] = bounds;
  constexpr double one_half = 0.50;
  int iteration_count = 0;
  bool converged = false;
  while (iteration_count <= opts.max_iterations && !converged) {
    double midpoint = one_half * (left_endpoint + right_endpoint);

    converged =
        func(midpoint) == 0.0 || (midpoint - left_endpoint) < opts.tolerance;
    
    if (converged) {
      return Output{midpoint, iteration_count, converged};
    }
    ++iteration_count;
    if (func(left_endpoint) * func(midpoint) > 0) {
      left_endpoint = midpoint;
    } else {
      right_endpoint = midpoint;
    }
  }
  return Output{};
}

} // namespace yanl::optimize
