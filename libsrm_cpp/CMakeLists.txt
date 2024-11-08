cmake_minimum_required(VERSION 3.5)
project(libsrm_cpp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffloat-store")

set(MAIN_SOURCE_FILE src/main.cpp)
file(GLOB_RECURSE LIBRARY_SOURCE_FILES src/srm.cpp src/utils.cpp)

include_directories(include/libsrm_cpp)

find_package(OpenCV REQUIRED)
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS})

add_library(srm SHARED ${LIBRARY_SOURCE_FILES})

add_executable(main_exec ${MAIN_SOURCE_FILE})
target_link_libraries(main_exec PRIVATE srm ${OpenCV_LIBS})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/Executables)

add_custom_target(distclean
    COMMAND rm -rf CMakeFiles CMakeCache.txt *.cmake Makefile
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Removing all generated files"
)
