# Main render application
add_executable(render "")

# Add module subdirectories
add_subdirectory(math)
add_subdirectory(image)
add_subdirectory(object)
add_subdirectory(scene)
add_subdirectory(main)

# Link with module libraries
target_link_libraries(render image)
target_link_libraries(render math_utils)
target_link_libraries(render object)
target_link_libraries(render scene)