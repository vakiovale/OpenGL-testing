include_directories("${PROJECT_SOURCE_DIR}/lib/catch/")
include_directories("${PROJECT_SOURCE_DIR}/src/")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB TEST_SRC_FILES
  "${PROJECT_SOURCE_DIR}/tests/*.h"
  "${PROJECT_SOURCE_DIR}/tests/*.cpp")

add_executable(RunTests ${TEST_SRC_FILES})
target_link_libraries(RunTests ${LIBRARIES} OpenGL-app-lib)

add_test(NAME all_tests COMMAND RunTests)
