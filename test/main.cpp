#include <gtest/gtest.h>

#include "yanl.h"

// TEST(Vector_TestZeros, WithDoubles) {
//   int nrows = 10;
//   int ncols = 10;
//   auto x = yanl::zeros<double>(nrows, ncols);
//   auto y = std::vector<double>(size, 0.0);
//   EXPECT_TRUE(x.get() == y);
// }

// TEST(Vector_TestZeros, WithInts) {
//   int size = 10;
//   auto x = yanl::zeros<int>(size);
//   auto y = std::vector<int>(size, 0.0);
//   EXPECT_TRUE(x.get() == y);
// }

// TEST(Vector_TestOnes, WithDoubles) {
//   int size = 10;
//   auto x = yanl::ones<double>(size);
//   auto y = std::vector<double>(size, 1.0);
//   EXPECT_TRUE(x.get() == y);
// }

// TEST(Vector_TestOnes, WithInts) {
//   int size = 10;
//   auto x = yanl::ones<int>(size);
//   auto y = std::vector<int>(size, 1);
//   EXPECT_TRUE(x.get() == y);
// }

// TEST(Vector_TestPlusOperator, WithInts) {
//   int size = 3;
//   auto x = yanl::ones<int>(size);
//   x(1) = 2;
//   x(2) = 3;
//   auto y = yanl::ones<int>(size);
//   auto z = x + y;

//   for (int i = 0; i < 3; ++i) {
//     EXPECT_TRUE(z(i) == i + 2);
//   }
// }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}