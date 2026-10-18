#include "optimization.h"

#include <cmath>

#include "constants.h"

namespace yanl::optimization {

auto bisect(std::function<double(double)> func, double lower_bound,
            double upper_bound) -> BisectionMethodResult {
  BisectionMethodResult result{};

  constexpr double kTolerance = 1e-6;

  const int max_num_iterations = 1000;

  if (func(lower_bound) * func(upper_bound) >= 0) {
    return result;
  }

  for (int iteration_count = 0; iteration_count <= max_num_iterations;
       ++iteration_count) {
    double midpoint = (lower_bound + upper_bound) / kTwo;
    double f_at_c = func(midpoint);

    double interval_width = upper_bound - lower_bound;

    if (interval_width <= kTolerance) {
      return {.root = midpoint,
              .num_iterations = iteration_count,
              .converged = true};
    }

    double f_at_a = func(lower_bound);
    double f_at_b = func(upper_bound);

    if (f_at_a * f_at_c < 0) {
      upper_bound = midpoint;
    } else if (f_at_b * f_at_c < 0) {
      lower_bound = midpoint;
    }
  }

  return {
      .root = -1.0, .num_iterations = max_num_iterations, .converged = false};
}

};  // namespace yanl::optimization

namespace yanl::derivative {

auto fp_fd(std::function<double(double)> func, double x_value, double h_value)
    -> double {
  return (func(x_value + h_value) - func(x_value)) / h_value;
}

auto fp_cd(std::function<double(double)> func, double x_value, double h_value)
    -> double {
  return (func(x_value + h_value) - func(x_value - h_value)) / (kTwo * h_value);
}

auto fp_bd(std::function<double(double)> func, double x_value, double h_value)
    -> double {
  return (func(x_value) - func(x_value - h_value)) / h_value;
}

auto fpp_121(std::function<double(double)> func, double x_value, double h_value)
    -> double {
  return (func(x_value + h_value) - (kTwo * func(x_value)) +
          func(x_value - h_value)) /
         std::pow(h_value, kTwo);
}

};  // namespace yanl::derivative
