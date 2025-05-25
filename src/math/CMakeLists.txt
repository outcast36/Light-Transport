target_sources(math_utils
    PRIVATE
        Interval.cpp
        IntervalSet.cpp
        Span.cpp
        vec3.cpp
)

target_include_directories(math_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(render math_utils)