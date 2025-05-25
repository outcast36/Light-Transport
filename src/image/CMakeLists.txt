target_sources(image
    PRIVATE
        FileHandle.cpp
        PFMImageIO.cpp
)

target_include_directories(image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(render image)