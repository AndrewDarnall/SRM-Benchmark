cmake_minimum_required(VERSION 3.5)
project(libsrm_cpp)

set(CMAKE_CXX_STANDARD 11)


file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
include_directories(include/libsrm_cpp)

set(MAIN_SOURCE_FILE src/main.cpp)

find_package(OpenCV REQUIRED)
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS})

add_library(srm SHARED ${SOURCE_FILES})

add_executable(main_exec ${MAIN_SOURCE_FILE})
target_link_libraries(main_exec srm ${OpenCV_LIBS})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/Executables)