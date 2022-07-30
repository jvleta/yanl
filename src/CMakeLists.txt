add_library(yanl INTERFACE)
target_include_directories(yanl INTERFACE .)

# add_executable(demo main.cpp)
# if(MSVC)
#   target_compile_options(demo PRIVATE /W4 /WX)
# else()
#   target_compile_options(demo PRIVATE -Wall -Wextra -Wpedantic -Werror)
# endif()