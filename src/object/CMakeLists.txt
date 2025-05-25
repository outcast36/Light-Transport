target_sources(object
    PRIVATE
        CSG.cpp
        Sphere.cpp
)

target_include_directories(object PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(render object)