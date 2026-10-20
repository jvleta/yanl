#include "optimization.h"

#include <cmath>
#include <functional>
#include <limits>

namespace yanl::optimization {

auto bisect(std::function<double(double)> func, double a, double b)
    -> BisectionMethodResult {
  BisectionMethodResult result{};

  constexpr double kTolerance = 1e-6;
  const int max_num_iterations = 1000;

  if (func(a) * func(b) >= 0) {
    return result;
  }

  for (int i = 0; i <= max_num_iterations; ++i) {
    double c = 0.5 * (a + b);
    double f_at_c = func(c);

    if ((b - a) <= kTolerance) {
      return {
          .root = c,
          .num_iterations = i,
          .converged = true,
      };
    }

    double f_at_a = func(a);
    double f_at_b = func(b);

    if (f_at_a * f_at_c < 0) {
      b = c;
    } else if (f_at_b * f_at_c < 0) {
      a = c;
    }
  }

  return {
      .root = -std::numeric_limits<double>::max(),
      .num_iterations = max_num_iterations,
      .converged = false,
  };
}

};  // namespace yanl::optimization
