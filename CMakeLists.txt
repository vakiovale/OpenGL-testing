cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(OpenGL-app)

# Set up Boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_DEBUG_LIBS OFF)
set(Boost_USE_RELEASE_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_ROOT lib/boost)
find_package(Boost 1.73.0 REQUIRED COMPONENTS regex)
include_directories(${Boost_INCLUDE_DIRS})

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
set(LIBRARIES spdlog glad glfw glm tinyobjloader ${Boost_LIBRARIES})
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

# Executable and linking
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} OpenGL-app-lib)

# Set up tests
include(CTest)
add_subdirectory(tests)
