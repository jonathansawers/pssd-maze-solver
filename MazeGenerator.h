//header file of mazegenerator class
//containing functions and variables to generate the maze

#include "Maze.h"

class MazeGenerator {
    private:    
        void removeWall(Maze& maze, int x1, int y1, int x2, int y2); //helper function to remove wall between two cells
        void dfsGenerate(Maze &maze, int x, int y); //helper function for dfs generation

    public:
        MazeGenerator();
        Maze generate(int width, int height); //generic maze generation
 
        Maze generateDFS(int width, int height); //if using dfs for maze generation
        Maze generatePrim(int width, int height); //if using prim's algorithm for maze generation

    };
