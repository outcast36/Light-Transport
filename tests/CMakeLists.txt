# Test build
add_executable(unit_tests "")

# Link with project modules -- include directories are added to libraries
target_link_libraries(unit_tests math_utils image object scene)

# Find installed GoogleTest
find_package(GTest REQUIRED)
include(GoogleTest)

# Link with gtest_main
target_sources(unit_tests PRIVATE SpanTest.cpp IntervalTest.cpp)
target_link_libraries(unit_tests GTest::gtest_main)
gtest_discover_tests(unit_tests) 