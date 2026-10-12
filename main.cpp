#include <functional>
#include <iostream>
#include <numeric>

#include <gtest/gtest.h>

namespace yanl::optimization {

struct BisectionMethodResult {
  double root = 0.0;
  int num_iterations = 0;
  bool converged = false;
};

BisectionMethodResult bisect(std::function<double(double)> func, double a,
                             double b) {
  BisectionMethodResult result{};

  double tol = 1e-6;
  const int max_num_iterations = 1000;

  if (func(a) * func(b) >= 0) {
    return result;
  }

  for (int i = 0; i <= max_num_iterations; ++i) {
    double c = 0.5 * (b + a);
    double f_at_c = func(c);

    if ((b - a) <= tol) {
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

namespace yanl::derivative {
  
    double fp_fd(std::function<double(double)> func, double x, double h) {
	  return (func(x + h) - func(x)) / h;
	}

    double fp_cd(std::function<double(double)> func, double x, double h) {
	  return (func(x + h) - func(x - h)) / (2.0 * h);
	}
  
	double fp_bd(std::function<double(double)> func, double x, double h) {
	  return (func(x) - func(x - h)) / h;
	}

	double fpp_121(std::function<double(double)> func, double x, double h) {
	  return (func(x + h) - 2.0 * func(x) + func(x - h)) / std::pow(h, 2.0);
	}

};

}; // namespace yanl::optimization

TEST(BisectionMethodTest, ParabolicFunction) {
  const auto func = [](double x) { return x * x - 1.0; };
  auto r = yanl::optimization::bisect(func, 0.0, 5.0);
  EXPECT_NE(r.root, 1.0);
  EXPECT_EQ(r.converged, true);
  EXPECT_EQ(r.num_iterations, 23);
}

TEST(BisectionMethodTest, TrigFunction) {
  const auto func = [](double x) { return std::sin(x); };
  auto r = yanl::optimization::bisect(func, 3.1, 3.2);
  EXPECT_NE(r.root, 1.0);
  EXPECT_EQ(r.converged, true);
  EXPECT_EQ(r.num_iterations, 17);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
