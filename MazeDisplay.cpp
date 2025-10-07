#include "MazeDisplay.h"

#include <algorithm>
#include <iostream>

char whichArrow(int dx, int dy) {
  if (dx == 1 && dy == 0) return '>';
  if (dx == -1 && dy == 0) return '<';
  if (dx == 0 && dy == 1) return 'v';
  if (dx == 0 && dy == -1) return '^';
  return '*';
}

// Constructor
MazeDisplay::MazeDisplay(const Maze* m) : maze(m) {}

// Display the basic maze
void MazeDisplay::displayMaze() const {
  if (!maze) return;

  int width = maze->getWidth();
  int height = maze->getHeight();

  // Print top border
  std::cout << "+";
  for (int x = 0; x < width; x++) {
    std::cout << "---+";
  }
  std::cout << std::endl;

  // Print each row
  for (int y = 0; y < height; y++) {
    printCellRow(y);
    printHorizontalWall(y);
  }
}

// Display maze with solution path
void MazeDisplay::displayMazeWithPath(
    const std::vector<std::pair<int, int>>& path) const {
  if (!maze) return;

  int width = maze->getWidth();
  int height = maze->getHeight();

  // Print top border
  std::cout << "+";
  for (int x = 0; x < width; x++) {
    std::cout << "---+";
  }
  std::cout << std::endl;

  // Print each row
  for (int y = 0; y < height; y++) {
    printCellRow(y);
    printHorizontalWall(y);
  }
}

// Display maze with visited cells
void MazeDisplay::displayMazeWithVisited(
    const std::vector<std::pair<int, int>>& visited) const {
  if (!maze) return;

  int width = maze->getWidth();
  int height = maze->getHeight();

  // Print top border
  std::cout << "+";
  for (int x = 0; x < width; x++) {
    std::cout << "---+";
  }
  std::cout << std::endl;

  // Print each row
  for (int y = 0; y < height; y++) {
    printCellRow(y);
    printHorizontalWall(y);
  }
}

// Print horizontal walls for a row
void MazeDisplay::printHorizontalWall(int row) const {
  if (!maze) return;

  int width = maze->getWidth();
  const auto& grid = maze->getGrid();

  std::cout << Colors::WHITE << "+";
  for (int x = 0; x < width; x++) {
    if (row < maze->getHeight() - 1 && grid[row][x].walls[2]) {  // bottom wall
      std::cout << "---+";
    } else {
      std::cout << "   +";
    }
  }
  std::cout << Colors::RESET << std::endl;
}

// Print cells and vertical walls for a row
void MazeDisplay::printCellRow(int row) const {
  if (!maze) return;

  int width = maze->getWidth();
  const auto& grid = maze->getGrid();
  auto start = maze->getStart();
  auto end = maze->getEnd();

  // Left border
  if (grid[row][0].walls[3]) {  // left wall
    std::cout << "|";
  } else {
    std::cout << " ";
  }

  // Print each cell in the row
  for (int x = 0; x < width; x++) {
    // Print cell content
    if (row == start.second && x == start.first) {
      std::cout << " S ";  // Start
    } else if (row == end.second && x == end.first) {
      std::cout << " E ";  // End
    } else {
      std::cout << "   ";
    }

    // Print right wall
    if (x < width - 1) {
      if (grid[row][x].walls[1]) {  // right wall
        std::cout << "|";
      } else {
        std::cout << " ";
      }
    }
  }

  // Right border
  if (grid[row][width - 1].walls[1]) {  // right wall
    std::cout << "|";
  }
  std::cout << std::endl;
}

// Get character representation of a cell
char MazeDisplay::getCellChar(int x, int y) const {
  if (!maze) return ' ';

  auto start = maze->getStart();
  auto end = maze->getEnd();

  if (y == start.second && x == start.first) {
    return 'S';  // Start
  } else if (y == end.second && x == end.first) {
    return 'E';  // End
  } else {
    return ' ';  // Empty cell
  }
}

// Display with different symbols for path and visited cells
void MazeDisplay::displayMazeWithSymbols(
    const std::vector<std::pair<int, int>>& path,
    const std::vector<std::pair<int, int>>& visited) const {
  if (!maze) return;

  int width = maze->getWidth();
  int height = maze->getHeight();
  const auto& grid = maze->getGrid();
  auto start = maze->getStart();
  auto end = maze->getEnd();

  // Print top border
  std::cout << "+";
  for (int x = 0; x < width; x++) {
    std::cout << "---+";
  }
  std::cout << std::endl;

  // Print each row
  for (int y = 0; y < height; y++) {
    // Left border
    if (grid[y][0].walls[3]) {  // left wall
      std::cout << "|";
    } else {
      std::cout << " ";
    }

    // Print each cell in the row
    for (int x = 0; x < width; x++) {
      // Determine cell content
      char cellChar = ' ';
      if (y == start.second && x == start.first) {
        cellChar = 'S';  // Start
      } else if (y == end.second && x == end.first) {
        cellChar = 'E';  // End
      } else {
        for (size_t i = 0; i < path.size(); ++i) {
          if (path[i].first == x && path[i].second == y) {
            if (i + 1 < path.size()) {
              int dx = path[i + 1].first - x;
              int dy = path[i + 1].second - y;
              cellChar = whichArrow(dx, dy);
            } else {
              cellChar = '*';
            }
            break;
          }
        }
        if (cellChar == ' ' &&
            std::find(visited.begin(), visited.end(), std::make_pair(x, y)) !=
                visited.end()) {
          cellChar = '.';
        }
      }

      std::cout << " " << cellChar << " ";

      // Print right wall
      if (x < width - 1) {
        if (grid[y][x].walls[1]) {  // right wall
          std::cout << "|";
        } else {
          std::cout << " ";
        }
      }
    }

    // Right border
    if (grid[y][width - 1].walls[1]) {  // right wall
      std::cout << "|";
    }
    std::cout << std::endl;

    // Print horizontal walls
    printHorizontalWall(y);
  }
}

// Display maze with colors for better visualization
void MazeDisplay::displayMazeWithColors(
    const std::vector<std::pair<int, int>>& path,
    const std::vector<std::pair<int, int>>& visited) const {
  if (!maze) return;

  int width = maze->getWidth();
  int height = maze->getHeight();
  
  // Print top border with color
  std::cout << Colors::WHITE << "+";
  for (int x = 0; x < width; x++) {
    std::cout << "---+";
  }
  std::cout << Colors::RESET << std::endl;

  // Print each row
  for (int y = 0; y < height; y++) {
    printColoredCellRow(y, path, visited);
    printHorizontalWall(y);
  }
}

// Print colored cells and vertical walls for a row
void MazeDisplay::printColoredCellRow(int row, 
    const std::vector<std::pair<int, int>>& path,
    const std::vector<std::pair<int, int>>& visited) const {
  if (!maze) return;

  int width = maze->getWidth();
  const auto& grid = maze->getGrid();
  auto start = maze->getStart();
  auto end = maze->getEnd();

  // Left border
  if (grid[row][0].walls[3]) {  // left wall
    std::cout << Colors::WHITE << "|" << Colors::RESET;
  } else {
    std::cout << " ";
  }

  // Print each cell in the row
  for (int x = 0; x < width; x++) {
    // Determine cell content and color
    char cellChar = ' ';
    std::string color = Colors::RESET;
    
    if (row == start.second && x == start.first) {
      cellChar = 'S';  // Start
      color = Colors::BRIGHT_GREEN + Colors::BOLD;
    } else if (row == end.second && x == end.first) {
      cellChar = 'E';  // End
      color = Colors::BRIGHT_RED + Colors::BOLD;
    } else {
      // Check if this cell is part of the solution path
      bool isInPath = false;
      for (size_t i = 0; i < path.size(); ++i) {
        if (path[i].first == x && path[i].second == row) {
          isInPath = true;
          if (i + 1 < path.size()) {
            int dx = path[i + 1].first - x;
            int dy = path[i + 1].second - row;
            cellChar = whichArrow(dx, dy);
          } else {
            cellChar = '*';
          }
          color = Colors::BRIGHT_CYAN + Colors::BOLD;
          break;
        }
      }
      
      // If not in path, check if visited
      if (!isInPath && 
          std::find(visited.begin(), visited.end(), std::make_pair(x, row)) != visited.end()) {
        cellChar = '.';
        color = Colors::YELLOW;
      }
    }

    std::cout << " " << color << cellChar << Colors::RESET << " ";

    // Print right wall
    if (x < width - 1) {
      if (grid[row][x].walls[1]) {  // right wall
        std::cout << Colors::WHITE << "|" << Colors::RESET;
      } else {
        std::cout << " ";
      }
    }
  }

  // Right border
  if (grid[row][width - 1].walls[1]) {  // right wall
    std::cout << Colors::WHITE << "|" << Colors::RESET;
  }
  std::cout << std::endl;
}