#include "MazeGenerator.h"
#include <stack>
#include <random>
#include <algorithm>
#include <set>

MazeGenerator::MazeGenerator() {}

Maze MazeGenerator::generate(int width, int height) {
    //defaults to DFS generation
    return generateDFS(width, height);
}

Maze MazeGenerator::generateDFS(int width, int height) {

    Maze maze(width, height);
    for (auto& row : maze.getGrid()) {
        for (auto& cell : row) {
            cell.visited = false;
        }
    }

    dfsGenerate(maze, maze.getStart().first, maze.getStart().second);
    return maze;
}

//helper function to remove wall between two cells
void MazeGenerator::removeWall(Maze& maze, int x1, int y1, int x2, int y2) {
    std::vector<std::vector<Cell>>& grid = maze.getGrid();

    if (x2 == x1 + 1 && y2 == y1) {       // right
        grid[y1][x1].walls[1] = false;
        grid[y2][x2].walls[3] = false;
    } else if (x2 == x1 - 1 && y2 == y1) { // left
        grid[y1][x1].walls[3] = false;
        grid[y2][x2].walls[1] = false;
    } else if (x2 == x1 && y2 == y1 + 1) { // bottom
        grid[y1][x1].walls[2] = false;
        grid[y2][x2].walls[0] = false;
    } else if (x2 == x1 && y2 == y1 - 1) { // top
        grid[y1][x1].walls[0] = false;
        grid[y2][x2].walls[2] = false;
    }
}

void MazeGenerator::dfsGenerate(Maze &maze, int x, int y) {
    std::vector<std::vector<Cell>>& grid = maze.getGrid();
    grid[y][x].visited = true;

    int w = maze.getWidth();
    int h = maze.getHeight();

    //the possible directions (right, left, down, up)
    std::vector<std::pair<int,int>> neighbors = {{x+1,y},{x-1,y},{x,y+1},{x,y-1}};

    //randomly shuffle the neighbors to ensure randomness
    std::random_device rd;                                                        // random seed
    std::mt19937 g(rd());                                                         // random number generator from seed (Mersenne Twister PRNG)                                                
    std::shuffle(neighbors.begin(), neighbors.end(), g);                          // shuffle the neighbors

    for (std::size_t i = 0; i < neighbors.size(); i++) {
        int nx = neighbors[i].first;
        int ny = neighbors[i].second;

        //check if the neighbor is within bounds and not visited
        if (nx >= 0 && nx < w && ny >= 0 && ny < h && !grid[ny][nx].visited) {
            //remove the wall between the current cell and the neighbor
            removeWall(maze, x, y, nx, ny);
            dfsGenerate(maze, nx, ny); //recursively visit the neighbor
        }
    }



}