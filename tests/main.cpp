#include <gtest/gtest.h>

#include <cmath>

#include "yanl.h"

TEST(BisectionMethodTests, ParabolicFunction) {
  auto func = [](double x) -> double { return std::pow(x, 2.0) - 1.0; };
  auto result = yanl::optimization::bisect(func, 0.0, 5.0);
  EXPECT_NE(result.root, 1.0);
  EXPECT_EQ(result.converged, true);
}

TEST(BisectionMethodTests, TrigFunction) {
  auto func = [](double x) -> double { return std::sin(x); };
  const double a = 3.1;
  const double b = 3.2;
  auto result = yanl::optimization::bisect(func, a, b);
  EXPECT_NE(result.root, 1.0);
  EXPECT_EQ(result.converged, true);
}

TEST(BisectionMethodTests, EquationOfState) {
  // [p + a * (N/V)^2] * (V - N * b) = k * N * T
  // where V is volume occupied by a gas at temperature T and pressure P.
  // Additionally a and b are constants specific to the gas being
  // considered and k is the boltzman constant.
  constexpr double a = 0.401;                   // [Pa m^6]
  constexpr double b = 42.7e-6;                 // [m^3]
  constexpr double num_molecules = 1000;        // [molecules]
  constexpr double temperature = 300.0;         // [K]
  constexpr double pressure = 3.5e7;            // [Pa]
  constexpr double k_boltzman = 1.3806503e-23;  // [J K^-1]
                                                //
  const auto func = [&](double volume) -> double {
    const double thing1 =
        pressure + (a * std::pow(num_molecules / volume, 2.0));
    const double thing2 = volume - (num_molecules * b);
    const double lhs = thing1 * thing2;
    const double rhs = k_boltzman * num_molecules * temperature;
    return lhs - rhs;
  };
  constexpr double max_vol = 1.0;
	const double xtol = 1e-11;
  auto result = yanl::optimization::bisect(func, 0, max_vol, xtol);
  std::cout << result.root << "\n";
	EXPECT_LT(result.residual, xtol);
}

auto main(int argc, char** argv) -> int {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
