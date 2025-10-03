//for running the program

#include "MazeDisplay.h"
#include "MazeGenerator.h"
#include "MazeSolver.h"
#include <iostream>

// Simple ASCII drawing function
void drawMaze(const Maze& maze) {
    int w = maze.getWidth();
    int h = maze.getHeight();
    const auto& grid = maze.getGrid();

    // Draw top boundary
    for (int x = 0; x < w; x++) std::cout << " _";
    std::cout << "\n";

    for (int y = 0; y < h; y++) {
        std::cout << "|"; // left boundary
        for (int x = 0; x < w; x++) {
            std::cout << (grid[y][x].walls[2] ? "_" : " ");
            std::cout << (grid[y][x].walls[1] ? "|" : " ");
        }
        std::cout << "\n";
    }
}


int main() {
    MazeGenerator generator;
    Maze maze = generator.generateDFS(10, 6); // generate 10x6 maze
    drawMaze(maze);                            // display maze
    return 0;
}