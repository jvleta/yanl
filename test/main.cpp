#include <gtest/gtest.h>

#include "yanl.h"

TEST(Vector_TestZeros, WithDoubles) {
  int size = 10;
  auto x = yanl::zeros<double>(size);
  auto y = std::vector<double>(size, 0.0);
  EXPECT_TRUE(x->get() == y);
}

TEST(Vector_TestZeros, WithInts) {
  int size = 10;
  auto x = yanl::zeros<int>(size);
  auto y = std::vector<int>(size, 0.0);
  EXPECT_TRUE(x->get() == y);
}

TEST(Vector_TestOnes, WithDoubles) {
  int size = 10;
    auto x = yanl::ones<double>(size);
    auto y = std::vector<double>(size, 1.0);
  EXPECT_TRUE(x->get() == y);
}

TEST(Vector_TestOnes, WithInts) {
  int size = 10;
  auto x = yanl::ones<int>(size);
  auto y = std::vector<int>(size, 1);
  EXPECT_TRUE(x->get() == y);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}