cmake_minimum_required(VERSION 3.25)
project(YANL)

set(CMAKE_CXX_STANDARD 20)

if (EMSCRIPTEN)
	add_subdirectory(src)
endif()

if (NOT EMSCRIPTEN)
  include(FetchContent)

  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.18.0
    SYSTEM         # <--- Crucial: suppresses compiler warnings
  )

  FetchContent_MakeAvailable(googletest)

  find_program(CLANG_TIDY_EXE NAMES "clang-tidy")

  if(CLANG_TIDY_EXE)
	  message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
	  set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

    if(APPLE)
      # Query the system for the active macOS SDK location
      execute_process(COMMAND xcrun --show-sdk-path 
				              OUTPUT_VARIABLE MACOS_SDK_PATH
                      OUTPUT_STRIP_TRAILING_WHITESPACE
      )
        
      # Inject the SDK path as an extra compiler argument for clang-tidy
      set(CMAKE_CXX_CLANG_TIDY 
          "${CLANG_TIDY_EXE}"
          "--extra-arg=-isysroot"
          "--extra-arg=${MACOS_SDK_PATH}"
      )
    else()
      # Default behavior for Linux / Windows environment
	    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
    endif()
  else()
    message(WARNING "clang-tidy not found. Static analysis will be skipped.") 
  endif()

  add_subdirectory(src)
  add_subdirectory(tests)

endif()

