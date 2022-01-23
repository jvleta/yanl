add_executable(test_yanl main.cpp)
target_link_libraries(test_yanl gtest pthread)
target_include_directories(test_yanl PUBLIC ${PROJECT_SOURCE_DIR}/src)

if(MSVC)
  target_compile_options(test_yanl PRIVATE /W4 /WX)
else()
  target_compile_options(test_yanl PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()