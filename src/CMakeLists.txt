# Create module libraries
add_library(image)
add_library(math_utils)
add_library(object)
add_library(scene)

# Main render application
add_executable(render "")

# Add module subdirectories
add_subdirectory(image)
add_subdirectory(main)
add_subdirectory(math)
add_subdirectory(object)
add_subdirectory(scene)