cmake_minimum_required(VERSION 2.8)

project(OpenGL-app)
set(CMAKE_CXX_STANDARD 17)

# Set up GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)

# Set up glad
add_library(glad lib/glad/include/glad/glad.h lib/glad/src/glad.c)
target_include_directories(glad PUBLIC lib/glad/include/)

# Set up GLM
add_subdirectory(lib/glm)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} glad glfw glm)
