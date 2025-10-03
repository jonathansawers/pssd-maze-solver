//header file of mazegenerator class
//containing functions and variables to generate the maze

#include "Maze.h"

class MazeGenerator {
    private:

    public:
        MazeGenerator();
        Maze generate(int width, int height); //generic maze generation
 
        Maze generateDFS(int width, int height); //if using dfs for maze generation
        Maze generatePrim(int width, int height); //if using prim's algorithm for maze generation
};
