add_executable(run_tests main.cpp)
target_include_directories(run_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(run_tests PRIVATE yanl gtest_main)
