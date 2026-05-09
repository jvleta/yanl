include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message("Using GCC compiler")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wunused -Wmisleading-indentation -Wdouble-promotion")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message("Using Clang compiler")    
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Werror -Weverything -Wno-padded -Wno-c++98-compat-pedantic -Wno-c++17-attribute-extensions -Wno-global-constructors -Wno-exit-time-destructors -Wno-sign-conversion")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    message("Using MSVC compiler")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /permissive /W4 /w14640")
else()
    message("Unknown C++ compiler")
endif()

set(CMAKE_CXX_CLANG_TIDY
     clang-tidy;
     -header-filter=.*;
     -checks=readability-*;
   -warnings-as-errors=*;)

add_executable(matrix_test main.cpp)

target_link_libraries(matrix_test
 PRIVATE
  GTest::GTest
  yanl)
  
add_test(yanl_gtests matrix_test)
