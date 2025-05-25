target_sources(scene
    PRIVATE
        Cameras.cpp
        Scene.cpp
)

target_include_directories(scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(render scene)