#include <gtest/gtest.h>

#include <numbers>
#include <yanl/yanl.h>

TEST(matrix_tests, call_zeros_with_doubles) {
  constexpr int nrows = 10;
  constexpr int ncols = 10;
  constexpr int size = nrows * ncols;
  auto actual = yanl::zeros<double>(nrows, ncols);
  auto expected = std::vector<double>(size, 0.0);
  EXPECT_TRUE(actual.data_ == expected);
}

TEST(matrix_tests, call_zeros_with_integers) {
  constexpr int nrows = 10;
  constexpr int ncols = 10;
  constexpr int size = nrows * ncols;
  auto actual = yanl::zeros<int>(nrows, ncols);
  auto expected = std::vector<int>(size, 0);
  EXPECT_TRUE(actual.data_ == expected);
}

TEST(matrix_tests, call_ones_with_doubles) {
  constexpr int nrows = 10;
  constexpr int ncols = 10;
  constexpr int size = nrows * ncols;
  auto actual = yanl::ones<double>(nrows, ncols);
  auto expected = std::vector<double>(size, 1.0);
  EXPECT_TRUE(actual.data_ == expected);
}

TEST(matrix_tests, call_ones_with_integers) {
  constexpr int nrows = 10;
  constexpr int ncols = 10;
  constexpr int size = nrows * ncols;
  auto actual = yanl::ones<int>(nrows, ncols);
  auto expected = std::vector<int>(size, 1);
  EXPECT_TRUE(actual.data_ == expected);
}

TEST(matrix_tests, call_eye_with_doubles) {
  constexpr int nrows = 3;
  auto actual = yanl::eye<double>(nrows);
  std::vector<double> expected{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
  EXPECT_TRUE(actual.data_ == expected);
}

TEST(matrix_tests, call_eye_with_integers) {
  constexpr int nrows = 3;
  auto actual = yanl::eye<int>(nrows);
  std::vector<int> expected{1, 0, 0, 0, 1, 0, 0, 0, 1};
  EXPECT_TRUE(actual.data_ == expected);
}

TEST(matrix_tests, call_determinant) {
  constexpr int nrows = 3;
  constexpr int ncols = 3;
  auto diagonal_matrix = yanl::zeros<int>(nrows, ncols);

  diagonal_matrix(0, 0) = 1.0;
  diagonal_matrix(1, 1) = 2.0;
  diagonal_matrix(2, 2) = 3.0;

  auto computed_value = yanl::linear_algebra::det(diagonal_matrix);
  auto expected_value = 6.0;

  EXPECT_TRUE(computed_value == expected_value);
}

TEST(linear_algebra_tests, call_solve) {
  auto lhs = yanl::zeros<double>(3, 3);
  auto rhs = yanl::zeros<double>(3, 1);

  lhs(0, 0) = 1.0;
  lhs(0, 1) = 4.0;
  lhs(0, 2) = 5.0;
  lhs(1, 0) = 6.0;
  lhs(1, 1) = 8.0;
  lhs(1, 2) = 22.0;
  lhs(2, 0) = 32.0;
  lhs(2, 1) = 5.0;
  lhs(2, 2) = 5.0;
  rhs(0, 0) = 1.0;
  rhs(1, 0) = 2.0;
  rhs(2, 0) = 3.0;

  auto actual = yanl::linear_algebra::solve(lhs, rhs);
  const std::vector<double> expected_values = {0.05614973, 0.25935829,
                                               -0.01871658};
  EXPECT_NEAR(actual(0, 0), expected_values[0], 1e-8);
  EXPECT_NEAR(actual(1, 0), expected_values[1], 1e-8);
  EXPECT_NEAR(actual(2, 0), expected_values[2], 1e-8);
}

const auto constant_function = [](double x) { return 1.0; };
const auto linear_function = [](double x) { return x; };
const auto quadratic_func = [](double x) { return std::pow(x, 2.0) - 1.0; };

TEST(BisectionMethodTests, EndPointErrorMessageTest) {
  const auto result =
      yanl::optimize::bisect(constant_function, 1, 0, 1e-3, 1000);
  EXPECT_EQ(yanl::optimize::kLeftEndPointMustBeLessThanRightEndpoint,
            result.message);
}

TEST(BisectionMethodTests, InitialFunctionEvaluationErrorMessageTest) {
  const auto result =
      yanl::optimize::bisect(constant_function, 0, 1, 1e-3, 1000);
  EXPECT_EQ(yanl::optimize::kInitialFunctionEvaluationsMustDifferInSign,
            result.message);
}

TEST(BisectionMethodTests, ConvergenceErrorMessageTest) {
  const auto result = yanl::optimize::bisect(linear_function, -100, 1, 1e-3, 2);
  EXPECT_EQ(yanl::optimize::kConvergenceNotAchieved, result.message);
}

TEST(BisectionMethodTests, QuadraticFunctions) {
  EXPECT_EQ(1, yanl::optimize::bisect(quadratic_func, 0, 2, 1e-6, 1000).root);
  EXPECT_EQ(-1, yanl::optimize::bisect(quadratic_func, -2, 0, 1e-6, 1000).root);
}

TEST(BisectionMethodTests, CosineFunction) {
  const auto func = [](double x) { return std::cos(x); };
  const auto pi = std::numbers::pi_v<double>;
  const auto tol1 = 1e-3;
  const auto tol2 = 1e-4;
  const auto tol3 = 1e-5;
  EXPECT_NEAR(pi / 2.0, yanl::optimize::bisect(func, 0, pi, tol1, 1000).root,
              tol1);
  EXPECT_NEAR(pi / 2.0, yanl::optimize::bisect(func, 0, pi, tol2, 1000).root,
              tol2);
  EXPECT_NEAR(pi / 2.0, yanl::optimize::bisect(func, 0, pi, tol3, 1000).root,
              tol3);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}