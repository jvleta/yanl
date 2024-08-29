#include <gtest/gtest.h>

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
  int nrows = 10;
  int ncols = 10;
  int size = nrows * ncols;
  auto actual = yanl::zeros<int>(nrows, ncols);
  auto expected = std::vector<int>(size, 0);
  EXPECT_TRUE(actual.data_ == expected);
}

TEST(matrix_tests, call_ones_with_doubles) {
  int nrows = 10;
  int ncols = 10;
  int size = nrows * ncols;
  auto actual = yanl::ones<double>(nrows, ncols);
  auto expected = std::vector<double>(size, 1.0);
  EXPECT_TRUE(actual.data_ == expected);
}

TEST(matrix_tests, call_ones_with_integers) {
  int nrows = 10;
  int ncols = 10;
  int size = nrows * ncols;
  auto actual = yanl::ones<int>(nrows, ncols);
  auto expected = std::vector<int>(size, 1);
  EXPECT_TRUE(actual.data_ == expected);
}

TEST(matrix_tests, call_eye_with_doubles) {
  int nrows = 3;
  auto actual = yanl::eye<double>(nrows);
  std::vector<double> expected{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
  EXPECT_TRUE(actual.data_ == expected);
}

TEST(matrix_tests, call_eye_with_integers) {
  int nrows = 3;
  auto actual = yanl::eye<int>(nrows);
  std::vector<int> expected{1, 0, 0, 0, 1, 0, 0, 0, 1};
  EXPECT_TRUE(actual.data_ == expected);
}

TEST(matrix_tests, call_determinant) {
  int nrows = 3;
  int ncols = 3;
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

  std::cout << "A =\n" << lhs << "\n";
  std::cout << "b =\n" << rhs << "\n";
  std::cout << "x =\n" << actual << "\n";

  const std::vector<double> expected_values = {0.05614973, 0.25935829,
                                               -0.01871658};
  EXPECT_NEAR(actual(0, 0), expected_values[0], 1e-8);
  EXPECT_NEAR(actual(1, 0), expected_values[1], 1e-8);
  EXPECT_NEAR(actual(2, 0), expected_values[2], 1e-8);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}