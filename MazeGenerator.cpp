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

// uses dfs with backtracking to generate the maze
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

//helper function to add unvisited neighbour cells to nextCells
void MazeGenerator::addNextCell(Maze &maze, int x, int y, std::vector<std::pair<int, int>> &nextCells)
{
    int w = maze.getWidth();
    int h = maze.getHeight();
    std::vector<std::vector<Cell>>& grid = maze.getGrid();

    //
    if (x >= 0 && x < w && y >= 0 && y < h && !grid[y][x].visited) {
        nextCells.push_back(std::pair<int,int>(x,y));
    }
}

// uses prim's algorithm to generate the maze
Maze MazeGenerator::generatePrim(int width, int height) {
    Maze maze(width, height);
    std::vector<std::vector<Cell>>& grid = maze.getGrid();

    //firstly initialises all cells as unvisited
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid[y][x].visited = false;
        }
    }

    std::vector<std::pair<int,int>> nextCells;                                  //list of next boundary cells to consider

    //start from a random cell, using similar randomisation to the dfs backtracking method
    std::random_device rd;                                                        // random seed
    std::mt19937 g(rd());                                                         // random number generator from seed (Mers
    std::uniform_int_distribution<> distX(0, width - 1);                          //generate random x coordinate
    std::uniform_int_distribution<> distY(0, height - 1);                         //generate random y coordinate

    int startX = distX(g);
    int startY = distY(g);

    grid[startY][startX].visited = true;

    // add the neighbours of start cell to nextCells
    addNextCell(maze, startX + 1, startY, nextCells);                              //right neighbour
    addNextCell(maze, startX - 1, startY, nextCells);                              //left
    addNextCell(maze, startX, startY + 1, nextCells);                              //bottom
    addNextCell(maze, startX, startY - 1, nextCells);                              //top

    //main loop of prim's algorithm
    while (!nextCells.empty()) {
        //select a random cell from nextCells
        std::uniform_int_distribution<> idxDist(0, nextCells.size() - 1);
        int idx = idxDist(g);

        int x = nextCells[idx].first;
        int y = nextCells[idx].second;

        //finds visited neighbours of the selected cell
        std::vector<std::pair<int,int>> visitedNeighbours;

        if (x + 1 < width && grid[y][x+1].visited) visitedNeighbours.push_back(std::pair<int,int>(x+1,y)); //right
        if (x - 1 >= 0 && grid[y][x-1].visited) visitedNeighbours.push_back(std::pair<int,int>(x-1,y)); //left
        if (y + 1 < height && grid[y+1][x].visited) visitedNeighbours.push_back(std::pair<int,int>(x,y+1)); //bottom
        if (y - 1 >= 0 && grid[y-1][x].visited) visitedNeighbours.push_back(std::pair<int,int>(x,y-1)); //top

        if (!visitedNeighbours.empty()) {
            //select a random visited neighbour
            std::uniform_int_distribution<> nDist(0, visitedNeighbours.size() - 1);
            int nIdx = nDist(g);
            int nx = visitedNeighbours[nIdx].first;
            int ny = visitedNeighbours[nIdx].second;

            //remove the wall between the selected cell and the chosen neighbour
            removeWall(maze, x, y, nx, ny);
            grid[y][x].visited = true;                                          //mark the selected cell as visited

            //add the unvisited neighbours of the selected cell to nextCells
            addNextCell(maze, x + 1, y, nextCells);                              //right neighbour
            addNextCell(maze, x - 1, y, nextCells);                              //left
            addNextCell(maze, x, y + 1, nextCells);                              //bottom
            addNextCell(maze, x, y - 1, nextCells);                              //top
        }

        //remove the selected cell from nextCells
        nextCells.erase(nextCells.begin() + idx);
    }
    return maze;
}