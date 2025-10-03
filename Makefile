# Makefile (run with 'make' command in terminal)

# compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# src files
SRCS = main.cpp Maze.cpp MazeGenerator.cpp MazeSolver.cpp MazeDisplay.cpp

# object files
OBJS = $(SRCS:.cpp=.o)

# execute name
TARGET = maze

# default target
all: $(TARGET)

# link object files into the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean build files if needed
clean:
	rm -f $(OBJS) $(TARGET)
