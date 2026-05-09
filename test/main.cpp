#include <gtest/gtest.h>

#include <yanl/yanl.h>

constexpr int kSize = 10;

TEST(matrix_tests, call_zeros_with_doubles) {
  int nrows = kSize;
  int ncols = kSize;
  int size = nrows * ncols;
  auto my_matrix = yanl::zeros<double>(nrows, ncols);
  auto stl_vector = std::vector<double>(size, 0.0);
  EXPECT_TRUE(my_matrix.data_ == stl_vector);
}

TEST(matrix_tests, call_zeros_with_integers) {
  int nrows = kSize;
  int ncols = kSize;
  int size = nrows * ncols;
  auto my_matrix = yanl::zeros<int>(nrows, ncols);
  auto stl_vector = std::vector<int>(size, 0);
  EXPECT_TRUE(my_matrix.data_ == stl_vector);
}

TEST(matrix_tests, call_ones_with_doubles) {
  int nrows = kSize;
  int ncols = kSize;
  int size = nrows * ncols;
  auto my_matrix = yanl::ones<double>(nrows, ncols);
  auto stl_vector = std::vector<double>(size, 1.0);
  EXPECT_TRUE(my_matrix.data_ == stl_vector);
}

TEST(matrix_tests, call_ones_with_integers) {
  int nrows = kSize;
  int ncols = kSize;
  int size = nrows * ncols;
  auto my_matrix = yanl::ones<int>(nrows, ncols);
  auto stl_vector = std::vector<int>(size, 1);
  EXPECT_TRUE(my_matrix.data_ == stl_vector);
}

TEST(matrix_tests, call_eye_with_doubles) {
  int nrows = 3;
  auto my_matrix = yanl::eye<double>(nrows);
  std::vector<double> stl_vector{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
  EXPECT_TRUE(my_matrix.data_ == stl_vector);
}

TEST(matrix_tests, call_eye_with_integers) {
  int nrows = 3;
  auto my_matrix = yanl::eye<int>(nrows);
  std::vector<int> stl_vector{1, 0, 0, 0, 1, 0, 0, 0, 1};
  EXPECT_TRUE(my_matrix.data_ == stl_vector);
}

TEST(matrix_tests, call_determinant) {
  int nrows = 3;
  int ncols = 3;
  auto my_matrix = yanl::zeros<int>(nrows, ncols);

  my_matrix(0, 0) = 1.0;
  my_matrix(1, 1) = 2.0;
  my_matrix(2, 2) = 3.0;

  auto computed_value = yanl::linear_algebra::det(my_matrix);
  auto expected_value = 6.0;

  EXPECT_NEAR(computed_value, expected_value, 1e-10);
}

TEST(linear_algebra_tests, call_solve) {
  yanl::matrix<double> my_matrix(3, 3);
  my_matrix.data_ = {1.0,  4.0, 5.0, 6.0, 8.0, 22.0,
                     32.0, 5.0, 5.0, 1.0, 2.0, 3.0};

  // auto my = yanl::zeros<double>(3, 3);
  // auto b = yanl::zeros<double>(3, 1);

  // A(0, 0) = 1.0;
  // A(0, 1) = 4.0;
  // A(0, 2) = 5.0;
  // A(1, 0) = 6.0;
  // A(1, 1) = 8.0;
  // A(1, 2) = 22.0;
  // A(2, 0) = 32.0;
  // A(2, 1) = 5.0;
  // A(2, 2) = 5.0;
  // b(0, 0) = 1.0;
  // b(1, 0) = 2.0;
  // b(2, 0) = 3.0;

  // auto solution = yanl::linear_algebra::solve(A, b);

  // std::cout << "A =\n" << A << "\n";
  // std::cout << "b =\n" << b << "\n";
  // std::cout << "x =\n" << x << "\n";

  // const std::vector<double> expected_values = {0.05614973, 0.25935829,
  //                                              -0.01871658};
  // EXPECT_NEAR(x(0, 0), expected_values[0], 1e-8);
  // EXPECT_NEAR(x(1, 0), expected_values[1], 1e-8);
  // EXPECT_NEAR(x(2, 0), expected_values[2], 1e-8);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
