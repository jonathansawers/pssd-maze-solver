#include "MazeDisplay.h"
#include <iostream>
#include <algorithm>

// Constructor
MazeDisplay::MazeDisplay(const Maze* m) : maze(m) {}

// Display the basic maze
void MazeDisplay::displayMaze() const {
    if (!maze) return;
    
    int width = maze->getWidth();
    int height = maze->getHeight();
    const auto& grid = maze->getGrid();
    
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
void MazeDisplay::displayMazeWithPath(const std::vector<std::pair<int, int>>& path) const {
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
void MazeDisplay::displayMazeWithVisited(const std::vector<std::pair<int, int>>& visited) const {
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
    
    std::cout << "+";
    for (int x = 0; x < width; x++) {
        if (row < maze->getHeight() - 1 && grid[row][x].walls[2]) {  // bottom wall
            std::cout << "---+";
        } else {
            std::cout << "   +";
        }
    }
    std::cout << std::endl;
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
    if (grid[row][width-1].walls[1]) {  // right wall
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
void MazeDisplay::displayMazeWithSymbols(const std::vector<std::pair<int, int>>& path, 
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
            } else if (std::find(path.begin(), path.end(), std::make_pair(x, y)) != path.end()) {
                cellChar = '*';  // Path
            } else if (std::find(visited.begin(), visited.end(), std::make_pair(x, y)) != visited.end()) {
                cellChar = '.';  // Visited
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
        if (grid[y][width-1].walls[1]) {  // right wall
            std::cout << "|";
        }
        std::cout << std::endl;
        
        // Print horizontal walls
        printHorizontalWall(y);
    }
}