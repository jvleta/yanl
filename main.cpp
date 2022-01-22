#include <gtest/gtest.h>

#include "yanl.h"

TEST(TestZeros, WithDoubles) {
    int size = 10;
    auto x = yanl::Vector<double>::zeros(size);
    auto y = std::vector<double>(size, 0.0);
    EXPECT_TRUE(x.get() == y);
}

TEST(TestZeros, WithInts) {
    int size = 10;
    auto x = yanl::Vector<int>::zeros(size);
    auto y = std::vector<int>(size, 0);
    EXPECT_TRUE(x.get() == y);
}

TEST(TestOnes, WithDoubles) {
    int size = 10;
    auto x = yanl::Vector<double>::zeros(size);
    auto y = std::vector<double>(size, 0.0);
    EXPECT_TRUE(x.get() == y);
}

TEST(TestOnes, WithInts) {
    int size = 10;
    auto x = yanl::Vector<int>::zeros(size);
    auto y = std::vector<int>(size, 0);
    EXPECT_TRUE(x.get() == y);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}