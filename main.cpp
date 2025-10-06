#include <iostream>

#include "MazeDisplay.h"
#include "MazeGenerator.h"
#include "MazeSolver.h"

int main() {
  MazeGenerator generator;

  // general check whether it generates correctly, delete when visual display is
  // implemented
  std::cout << "DFS Maze\n";
  Maze dfsMaze = generator.generateDFS(20, 20);

  MazeDisplay display(&dfsMaze);
  display.displayMaze();

  MazeSolver solver(dfsMaze);
  solver.showFullNav(false);

  auto solved = solver.solveMazeBlind(DFS);
  display.displayMazeWithSymbols(solved.tracedPath, {});

  solver.showFullNav(true);

  solved = solver.solveMazeBlind(DFS);
  display.displayMazeWithSymbols(solved.tracedPath, {});

  //   std::cout << "\nPrim's Maze \n";
  //   Maze primMaze = generator.generatePrim(20, 20);  // looks a bit weird
  //   MazeDisplay display2(&primMaze);
  //   display2.displayMaze();

  return 0;
}