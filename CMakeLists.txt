cmake_minimum_required(VERSION 3.25)

project(yanl LANGUAGES CXX VERSION 0.001)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add your source directories
add_subdirectory(src)
add_subdirectory(test)
