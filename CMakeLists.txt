cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(OpenGL-app)

# Set up spdlog
add_subdirectory(lib/spdlog)

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

# Set up tinyobjloader
add_library(tinyobjloader lib/tinyobjloader/tiny_obj_loader.h)
set_target_properties(tinyobjloader PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(tinyobjloader PUBLIC lib/tinyobjloader/)

# App
set(LIBRARIES spdlog glad glfw glm tinyobjloader)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

# Executable and linking
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} OpenGL-app-lib)

# Set up tests
include(CTest)
add_subdirectory(tests)
