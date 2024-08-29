#pragma once

#include <functional>
#include <tuple>

namespace yanl::optimize {

struct BisectionMethodResult {
  double root = std::numeric_limits<double>::max();
  bool converged = false;
  int num_iterations = 0;
  std::string message{};
};

constexpr char kLeftEndPointMustBeLessThanRightEndpoint[] =
    "The left end point must be less than right end point.\n";
constexpr char kInitialFunctionEvaluationsMustDifferInSign[] =
    "The values obtained from evaluating the function at the "
    "specified endpoints must differ in sign.\n";
constexpr char kConvergenceNotAchieved[] = "Convergence was not achieved.\n";

BisectionMethodResult bisect(std::function<double(double)> func,
                             double left_endpoint, double right_endpoint,
                             double tolerance, int max_iterations) {
  BisectionMethodResult result{};

  if (left_endpoint >= right_endpoint) {
    result.message = kLeftEndPointMustBeLessThanRightEndpoint;
    std::cerr << result.message;
    return result;
  }

  if (func(left_endpoint) * func(right_endpoint) > 0) {
    result.message = kInitialFunctionEvaluationsMustDifferInSign;
    std::cerr << result.message;
    return result;
  }

  int iteration_count = 1;
  constexpr double one_half = 0.5;
  while (iteration_count <= max_iterations) {
    double midpoint = one_half * (left_endpoint + right_endpoint);
    if (func(midpoint) == 0.0 ||
        one_half * (right_endpoint - left_endpoint) < tolerance) {
      result.root = midpoint;
      result.num_iterations = iteration_count;
      result.converged = true;
      return result;
    }
    ++iteration_count;
    if (func(midpoint) * func(left_endpoint) > 0) {
      left_endpoint = midpoint;
    } else {
      right_endpoint = midpoint;
    }
  }

  result.message = kConvergenceNotAchieved;
  return result;
}

} // namespace yanl::optimize
