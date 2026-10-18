#include <functional>
#include <iostream>
#include <numeric>

namespace yanl::optimization {

struct BisectionMethodResult {
  double root = 0.0;
  int num_iterations = 0;
  bool converged = false;
};

BisectionMethodResult bisect(std::function<double(double)> func,
                             double lower_bound, double upper_bound);

};  // namespace yanl::optimization
