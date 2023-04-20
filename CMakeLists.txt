cmake_minimum_required(VERSION 3.24)
project(test)

set(CMAKE_CXX_STANDARD 17)



# Désactivation du build des exemples de glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Path to glfw directory
add_subdirectory(./includes/glfw)
add_subdirectory(./includes/glad)

add_executable(myApp main.cpp)

target_link_libraries(myApp glad glfw)

find_package(OpenGL REQUIRED)

target_link_libraries(myApp OpenGL::GL)




