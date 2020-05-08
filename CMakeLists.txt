cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(OpenGL-app)

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

# Add src files
include_directories(${PROJECT_SOURCE_DIR}/src)
file(GLOB SRC_FILES
  "${PROJECT_SOURCE_DIR}/src/*.h"
  "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} glad glfw glm)
