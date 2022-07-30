#include <gtest/gtest.h>

#include <yanl/yanl.h>

TEST(matrix_tests, call_zeros_with_doubles) {
  int nrows = 10;
  int ncols = 10;
  int size = nrows * ncols;
  auto x = yanl::zeros<double>(nrows, ncols);
  auto y = std::vector<double>(size, 0.0);
  EXPECT_TRUE(x.data_ == y);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}