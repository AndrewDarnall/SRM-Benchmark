cmake_minimum_required(VERSION 3.5)
project(libsrm_cpp)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Specify the path for the main source file separately from the library source files
set(MAIN_SOURCE_FILE src/main.cpp)
file(GLOB_RECURSE LIBRARY_SOURCE_FILES src/srm.cpp)

# Include directories for headers
include_directories(include/libsrm_cpp)

# Find OpenCV
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS})

# Create the shared library `srm` from the `srm.cpp` source file
add_library(srm SHARED ${LIBRARY_SOURCE_FILES})

# Create the main executable and link it to the `srm` library and OpenCV
add_executable(main_exec ${MAIN_SOURCE_FILE})
target_link_libraries(main_exec PRIVATE srm ${OpenCV_LIBS})

# Set the output path for executables
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/Executables)

# Add a custom target for a full clean-up
add_custom_target(distclean
    COMMAND rm -rf CMakeFiles CMakeCache.txt *.cmake Makefile
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Removing all generated files"
)
