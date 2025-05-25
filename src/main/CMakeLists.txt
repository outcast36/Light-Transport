target_sources(render
    PRIVATE
        driver.cpp
        TestScenes.cpp
)

target_include_directories(render PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})