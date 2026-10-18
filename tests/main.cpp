#include <gtest/gtest.h>

#include <cmath>

#include "yanl.h"

// NOLINTBEGIN(readability-identifier-length)
TEST(BisectionMethodTest, ParabolicFunction) {
  auto func = [](double x) -> double { return std::pow(x, kTwo) - kOne; };
  auto r = yanl::optimization::bisect(func, kZero, kFive);
  EXPECT_NE(r.root, kOne);
  EXPECT_EQ(r.converged, true);
}

TEST(BisectionMethodTest, TrigFunction) {
  auto func = [](double x) -> double { return std::sin(x); };
  const double a = 3.1;
  const double b = 3.2;
  auto r = yanl::optimization::bisect(func, a, b);
  EXPECT_NE(r.root, kOne);
  EXPECT_EQ(r.converged, true);
}
// NOLINTEND(readability-identifier-length)

auto main(int argc, char** argv) -> int {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
