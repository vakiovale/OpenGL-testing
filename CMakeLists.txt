cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(OpenGL-app)

include(FetchContent)
include(ExternalProject)

set(BOOST_INSTALL_DIR ${PROJECT_SOURCE_DIR}/lib/boost)
if(NOT EXISTS ${BOOST_INSTALL_DIR})
  ExternalProject_Add(
    ext_boost
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/boost
    URL https://dl.bintray.com/boostorg/release/1.73.0/source/boost_1_73_0.tar.gz
    URL_HASH SHA256=9995e192e68528793755692917f9eb6422f3052a53c5e13ba278a228af6c7acf
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ./bootstrap.sh --without-libraries=python --prefix=${BOOST_INSTALL_DIR} && ./b2 install
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND ""
  )
endif()
set(Boost_INCLUDE_DIRS ${BOOST_INSTALL_DIR}/include)
set(Boost_LIBRARIES ${BOOST_INSTALL_DIR}/lib/libboost_regex.a)
include_directories(${Boost_INCLUDE_DIRS})

# Set up spdlog
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.6.1
)
FetchContent_MakeAvailable(spdlog)

# Set up GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.2
)
FetchContent_MakeAvailable(glfw)

# Set up glad
add_library(glad lib/glad/include/glad/glad.h lib/glad/src/glad.c)
target_include_directories(glad PUBLIC lib/glad/include/)

# Set up GLM
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)

# Set up tinyobjloader
FetchContent_Declare(
  ext_tinyobjloader
  GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
  GIT_TAG v1.0.6
)
FetchContent_GetProperties(ext_tinyobjloader)
if(NOT ext_tinyobjloader_POPULATED)
  FetchContent_POPULATE(ext_tinyobjloader)
  add_library(tinyobjloader ${ext_tinyobjloader_SOURCE_DIR}/tiny_obj_loader.h)
  set_target_properties(tinyobjloader PROPERTIES LINKER_LANGUAGE CXX)
  target_include_directories(tinyobjloader PUBLIC ${ext_tinyobjloader_SOURCE_DIR}/)
endif()

# App
set(LIBRARIES spdlog glad glfw glm tinyobjloader ${Boost_LIBRARIES})
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

# Executable and linking
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} OpenGL-app-lib)

# Set up tests
include(CTest)
add_subdirectory(tests)
