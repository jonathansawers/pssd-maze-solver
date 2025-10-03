#include "Maze.h"

Maze::Maze(int w, int h) : width(w), height(h) {
    // sets the grid with all cells having walls around the cell
    grid.assign(height, std::vector<Cell>(width));
    
    // set the start and end positions as whatever for now
    start = {1, 1};
    end = {width - 2, height - 2};
}

//helper functions below

int Maze::getWidth() const {
    return width;
}

int Maze::getHeight() const {
    return height;
}

void Maze::setStart(int x, int y) {
    start = {x, y};
}

void Maze::setEnd(int x, int y) {
    end = {x, y};
}

std::pair<int,int> Maze::getStart() const {
    return start;
}

std::pair<int,int> Maze::getEnd() const {
    return end;
}

// access the grid
std::vector<std::vector<Cell>>& Maze::getGrid() {
    return grid;
}

const std::vector<std::vector<Cell>>& Maze::getGrid() const {
    return grid;
}