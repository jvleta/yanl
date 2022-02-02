#pragma once

#include <functional>
#include <tuple>

namespace yanl::optimize {
struct Options {
  int max_iterations = 1000;
  double tolerance = 1e-6;
};

struct Output {
  double root = std::numeric_limits<double>::max();
  int iterations = -1;
  bool converged = false;
};

Output bisect(std::function<double(double)> func,
              std::pair<double, double> bounds, Options opts) {
  auto [a, b] = bounds;

  int nmax = opts.max_iterations;
  double tolerance = opts.tolerance;

  int n = 0;
  while (n <= opts.max_iterations) {
    double c = 0.5 * (a + b);
    if (func(c) == 0.0 or 0.5 * (b - a) < opts.tolerance) {
      return Output{c, n, true};
    }
    ++n;
    if (func(a) * func(c) > 0) {
      a = c;
    } else {
      b = c;
    }
  }
  return Output{};
}

} // namespace yanl::optimize
