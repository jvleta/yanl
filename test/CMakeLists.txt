find_package(GTest REQUIRED)

# Create your executable
add_executable(matrix_test main.cpp)

# Link your executable to GTest
target_link_libraries(matrix_test
 PRIVATE
  GTest::gtest_main
  yanl)

set_target_properties(matrix_test PROPERTIES CXX_CLANG_TIDY "clang-tidy;-header-filter=.;-checks=readability-*, -readability-magic-numbers, -readability-identifier-length, modernize-*, -modernize-use-trailing-return-type, -modernize-avoid-c-arrays")

add_test(yanl_gtests matrix_test)