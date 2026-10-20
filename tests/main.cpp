#include <gtest/gtest.h>

#include <cmath>

#include "yanl.h"

TEST(BisectionMethodTest, ParabolicFunction) {
  auto func = [](double x) -> double { return std::pow(x, 2.0) - 1.0; };
  auto result = yanl::optimization::bisect(func, 0.0, 5.0);
  EXPECT_NE(result.root, 1.0);
  EXPECT_EQ(result.converged, true);
}

TEST(BisectionMethodTest, TrigFunction) {
  auto func = [](double x) -> double { return std::sin(x); };
  const double a = 3.1;
  const double b = 3.2;
  auto result = yanl::optimization::bisect(func, a, b);
  EXPECT_NE(result.root, 1.0);
  EXPECT_EQ(result.converged, true);
}

auto main(int argc, char** argv) -> int {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
