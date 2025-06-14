cmake_minimum_required(VERSION 4.0.2)
project(LightTransport VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable warnings
add_compile_options(-Wall -Wextra -g)

# Add source libraries, files, and exectuables
add_subdirectory(src)

# Conditionally build and include tests
option(BUILD_TESTING "Build test code and enable testing" OFF)
if (BUILD_TESTING) 
    enable_testing()
    add_subdirectory(tests)
endif()