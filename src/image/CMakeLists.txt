add_library(image)

target_sources(image
    PRIVATE
        FileHandle.cpp
        PFMImageIO.cpp
)

target_include_directories(image PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(image math_utils)