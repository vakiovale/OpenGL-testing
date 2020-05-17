include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB SRC_FILES
  "${PROJECT_SOURCE_DIR}/src/*.h"
  "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library(OpenGL-app-lib STATIC ${SRC_FILES})
target_link_libraries(OpenGL-app-lib ${LIBRARIES})
