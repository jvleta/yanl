#include "optimization.h"
#include "constants.h"

#include <cmath>

namespace yanl::optimization {

BisectionMethodResult bisect(std::function<double(double)> func, double a,
                             double b) {
  BisectionMethodResult result{};

  constexpr double kTolerance = 1e-6;

  const int max_num_iterations = 1000;

  if (func(a) * func(b) >= 0) {
    return result;
  }

  for (int i = 0; i <= max_num_iterations; ++i) {
    double c = (b + a) / kTwo;
    double f_at_c = func(c);

    if ((b - a) <= kTolerance) {
      return {c, i, true};
    }

    double f_at_a = func(a);
    double f_at_b = func(b);

    if (f_at_a * f_at_c < 0) {
      b = c;
    } else if (f_at_b * f_at_c < 0) {
      a = c;
    }
  }

  return {-1.0, max_num_iterations, false};
}

}; // namespace yanl::optimization

namespace yanl::derivative {

double fp_fd(std::function<double(double)> func, double x, double h) {
  return (func(x + h) - func(x)) / h;
}

double fp_cd(std::function<double(double)> func, double x, double h) {
  return (func(x + h) - func(x - h)) / (kTwo * h);
}

double fp_bd(std::function<double(double)> func, double x, double h) {
  return (func(x) - func(x - h)) / h;
}

double fpp_121(std::function<double(double)> func, double x, double h) {
  return (func(x + h) - kTwo * func(x) + func(x - h)) / std::pow(h, kTwo);
}

}; // namespace yanl::derivative
