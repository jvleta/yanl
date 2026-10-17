#include "optimization.h"

#include <cmath>
#include <gtest/gtest.h>

constexpr double kOne = 1.0;
constexpr double kFive = 5.0;
constexpr double kZero = 0.0;

TEST(BisectionMethodTest, ParabolicFunction) {
  const auto func = [](double x) { return x * x - kOne; };
  auto r = yanl::optimization::bisect(func, kZero, kFive);
  EXPECT_NE(r.root, kOne);
  EXPECT_EQ(r.converged, true);
}

TEST(BisectionMethodTest, TrigFunction) {
  const auto func = [](double x) { return std::sin(x); };
	constexpr double kLeftEndPoint = 3.1;
	constexpr double kRightEndPoint = 3.2;
  auto r = yanl::optimization::bisect(func, kLeftEndPoint, kRightEndPoint);
  EXPECT_NE(r.root, kOne);
  EXPECT_EQ(r.converged, true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
