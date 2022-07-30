cmake_minimum_required(VERSION 3.16)

project(yanl LANGUAGES CXX VERSION 0.001)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(ENABLE_CODE_ANALYSIS "Run code analysis" OFF)
message(STATUS "ENABLE_CODE_ANALYSIS       ${ENABLE_CODE_ANALYSIS}")

if(ENABLE_CODE_ANALYSIS)
find_program(cppcheck cppcheck)
    message(STATUS "cppcheck                   ${cppcheck}")
    if(NOT (cppcheck MATCHES "NOTFOUND"))

        # Notes:
        # - unmatchedSuppression needed since not all source files are
        #   analyzed simultaneously
        # - unusedFunction needed since not all source files are
        #   analyzed simultaneously
        # - template needed to force "warning" into output string, and
        #   to make the 'id' available for suppression
        set(CMAKE_CXX_CPPCHECK "${cppcheck}"
            "--enable=all"
            "--inconclusive"
            "--inline-suppr"
            "--quiet"
            "--suppress=unmatchedSuppression"
            "--suppress=unusedFunction"
            "--check-config"
            "--template='{file}:{line}: warning: {id} ({severity}): {message}'")
    endif()

    set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    -header-filter=.;
    -checks=*;)
endif()

add_subdirectory(src)
add_subdirectory(test)