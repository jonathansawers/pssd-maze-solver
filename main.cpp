//for running the program

#include "MazeDisplay.h"
#include "MazeGenerator.h"
#include "MazeSolver.h"
#include <iostream>

// ASCII drawing function (delete when implemented visual display)
void drawMaze(const Maze& maze) {
    int w = maze.getWidth();
    int h = maze.getHeight();
    const auto& grid = maze.getGrid();

    // top boundary
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

    //general check whether it generates correctly, delete when visual display is implemented
    std::cout << "DFS Maze\n";
    Maze dfsMaze = generator.generateDFS(20, 20); 
    drawMaze(dfsMaze);                          

    std::cout << "\nPrim's Maze \n";
    Maze primMaze = generator.generatePrim(20, 20);//looks a bit weird
    drawMaze(primMaze);

    
    return 0;
}