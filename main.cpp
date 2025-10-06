#include "MazeDisplay.h"
#include "MazeGenerator.h"
#include "MazeSolver.h"
#include <iostream>

int main() {
    MazeGenerator generator;

    //general check whether it generates correctly, delete when visual display is implemented
    std::cout << "DFS Maze\n";
    Maze dfsMaze = generator.generateDFS(20, 20); 
    
    MazeDisplay display(&dfsMaze);
    display.displayMaze();

    std::cout << "\nPrim's Maze \n";
    Maze primMaze = generator.generatePrim(20, 20);//looks a bit weird
    MazeDisplay display2(&primMaze);
    display2.displayMaze();

    
    return 0;
}