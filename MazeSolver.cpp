#include "MazeSolver.h"

MazeSolver::MazeSolver() {}

MazeSolver::MazeSolver(Maze &initMaze) { curMaze = &initMaze; }

void MazeSolver::SetMaze(Maze &initMaze) { curMaze = &initMaze; }
