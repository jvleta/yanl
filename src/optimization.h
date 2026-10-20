#include <functional>
#include <iostream>
#include <numeric>

namespace yanl::optimization {

struct BisectionMethodResult {
  double root = 0.0;
  int num_iterations = 0;
  bool converged = false;
};

BisectionMethodResult bisect(std::function<double(double)> func, double a,
                             double b);

};  // namespace yanl::optimization
