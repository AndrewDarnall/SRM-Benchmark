# SRM Project's Makefile (For Linux and MacOS Only)

# Compiler
CC = g++

# Compiler Optimization
OPTIMIZATION = -O3

# Compiler flags
CFLAGS = $(OPTIMIZATION) -std=c++11 -Wall -g

# Source files directory (for implementations)
SRC_DIR = ./Implementations

# Define the variables based on the OS
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	OPENCV_LIBS_PATH = -L/usr/lib/x86_64-linux-gnu

	OPENCV_LIBS = -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio

	INCLUDES =  -I/usr/include/opencv4 \
				-I/usr/include/opencv4/opencv2 \
				-I./Headers \
				-I./Implementations
else ifeq ($(UNAME_S), Darwin)
	# OpenCV library path
	OPENCV_LIBS_PATH = -L/opt/homebrew/opt/opencv/lib

	# OpenCV libraries
	OPENCV_LIBS = -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio

	# Include directories
	INCLUDES = -I/opt/homebrew/opt/opencv/include/opencv4/opencv2/ \
				-I/opt/homebrew/opt/opencv/include/opencv4 \
				-I./Headers \
				-I./Implementations
else
	@echo "error -- Unsupported OS"
endif


# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) main.cpp

# Object files directory
OBJ_DIR = ./obj

# Output directory
OUT_DIR = ./Executables

# Executable name
EXEC = $(OUT_DIR)/SRM

# Object files
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))

all: $(OUT_DIR) $(OBJ_DIR) $(EXEC)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(INCLUDES) $(OPENCV_LIBS_PATH) $(OPENCV_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

post-build: $(EXEC)
	rm -rf $(OBJ_DIR)/*.o

clean:
	rm -rf $(OUT_DIR) $(OBJ_DIR)