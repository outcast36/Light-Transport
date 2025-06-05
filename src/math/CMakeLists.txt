add_library(math_utils)

target_sources(math_utils
    PRIVATE
        GFXBase.cpp
        Interval.cpp
        Span.cpp
        vec3.cpp
)

target_include_directories(math_utils PUBLIC ${CMAKE_CURRENT_LIST_DIR})