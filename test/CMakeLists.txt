include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(matrix_test main.cpp)

target_link_libraries(matrix_test
 PRIVATE
  GTest::GTest
  yanl)
  
add_test(yanl_gtests matrix_test)
