add_library(image)

target_sources(image
    PRIVATE
        FileHandle.cpp
        PFMImageIO.cpp
)

target_link_libraries(render image)
target_include_directories(render PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})