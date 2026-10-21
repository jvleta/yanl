#include <functional>
#include <iostream>
#include <numeric>

namespace yanl::optimization {

struct BisectionMethodResult {
  double root = -std::numeric_limits<double>::max();
	double residual = std::numeric_limits<double>::max();
  int num_iterations = 0;
  bool converged = false;
};

constexpr double kDefaultAbsoluteTolerance = 1e-12;

BisectionMethodResult bisect(
    std::function<double(double)> func, double a, double b,
    std::optional<double> xtol = kDefaultAbsoluteTolerance);

};  // namespace yanl::optimization
