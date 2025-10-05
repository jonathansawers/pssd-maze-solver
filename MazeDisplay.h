#ifndef MAZEDISPLAY_H
#define MAZEDISPLAY_H

#include "Maze.h"
#include <iostream>

class MazeDisplay {
    private:
        const Maze* maze;
        
    public:
        // Constructor
        MazeDisplay(const Maze* m);
        
        // Display methods
        void displayMaze() const;
        void displayMazeWithPath(const std::vector<std::pair<int, int>>& path) const;
        void displayMazeWithVisited(const std::vector<std::pair<int, int>>& visited) const;
        
        // Helper methods
        void printHorizontalWall(int row) const;
        void printCellRow(int row) const;
        char getCellChar(int x, int y) const;
        
        // Display with different symbols
        void displayMazeWithSymbols(const std::vector<std::pair<int, int>>& path, const std::vector<std::pair<int, int>>& visited) const;
};

#endif