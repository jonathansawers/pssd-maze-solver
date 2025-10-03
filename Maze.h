//header file of Maze class
//containing general functions and variables of the maze
//also contains the cell struct for the grid
#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <utility>  

struct Cell {
    bool visited = false;       // checks if the cell has been visited (use for algorithms)
    bool walls[4] = {true,true,true,true}; // top, right, bottom, left (true = wall exists, false = no wall)
};

class Maze {
    private:
        int width;                                      //width of the maze
        int height;                                     //height of the maze
        std::vector<std::vector<Cell>> grid;                //2D grid representing the maze
        std::pair<int, int> start;                      // starting point (x, y)
        std::pair<int, int> end;                        // ending point (x, y)

    public:
        Maze(int w, int h);
        //helper functions
        int getWidth() const;
        int getHeight() const;
        void setStart(int x, int y);
        void setEnd(int x, int y);
        std::pair<int, int> getStart() const;
        std::pair<int, int> getEnd() const;
        std::vector<std::vector<Cell>>& getGrid();                     // non-const
        const std::vector<std::vector<Cell>>& getGrid() const;         // const

};

#endif