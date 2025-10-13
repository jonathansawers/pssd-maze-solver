#ifndef MAZEDISPLAY_H
#define MAZEDISPLAY_H

#include <iostream>

#include "Maze.h"

// ANSI color codes for terminal output
namespace Colors {
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";
const std::string BOLD = "\033[1m";
const std::string BRIGHT_GREEN = "\033[92m";
const std::string BRIGHT_RED = "\033[91m";
const std::string BRIGHT_YELLOW = "\033[93m";
const std::string BRIGHT_BLUE = "\033[94m";
const std::string BRIGHT_MAGENTA = "\033[95m";
const std::string BRIGHT_CYAN = "\033[96m";
}  // namespace Colors

class MazeDisplay {
 private:
  const Maze* maze;

 public:
  // Constructor
  MazeDisplay(const Maze* m);

  // Display methods
  void displayMaze() const;
  void displayMazeWithPath(const std::vector<std::pair<int, int>>& path) const;
  void displayMazeWithVisited(
      const std::vector<std::pair<int, int>>& visited) const;

  // Helper methods
  void printHorizontalWall(int row) const;
  void printCellRow(int row) const;
  char getCellChar(int x, int y) const;

  // Display with different symbols
  void displayMazeWithSymbols(
      const std::vector<std::pair<int, int>>& path,
      const std::vector<std::pair<int, int>>& visited) const;

  // Display with colors for better visualization
  void displayMazeWithColors(
      const std::vector<std::pair<int, int>>& path,
      const std::vector<std::pair<int, int>>& visited) const;

  // Helper methods for colored output
  void printColoredCellRow(
      int row, const std::vector<std::pair<int, int>>& path,
      const std::vector<std::pair<int, int>>& visited) const;

  void animate(std::vector<std::pair<int, int>>& trace, int howLong,
               bool withColour);
};

#endif