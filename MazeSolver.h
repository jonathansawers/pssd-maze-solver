// header file of Mazesolver class
// containing functions and variables to solve the maze

#include "Maze.h"
using namespace std;

vector<vector<int>> dir = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

struct Solution {
  vector<point> tracedPath;
  point foundEndpoint;
  Solution() : foundEndpoint({0, 0}), tracedPath({}) {};
};

enum solveType { DFS, BFS, A_STAR };

class MazeSolver {
  Maze* curMaze;

  bool DFS_SOLVE(point curPoint, Solution& curSol) {
    curSol.tracedPath.push_back(curPoint);
    if (curMaze->atEnd(curPoint)) return true;
    Cell curCell = curMaze->getGrid()[curPoint.x][curPoint.y];

    for (int i = 0; i < 4; i++) {
      if (curCell.walls[i]) continue;
      int nextX = curPoint.x + dir[i][0];
      int nextY = curPoint.y + dir[i][1];

      if (!curMaze->getGrid()[nextX][nextY].visited) {
        bool foundEnd = DFS_SOLVE({nextX, nextY}, curSol);
        // just to show its going backwards
        if (!foundEnd)
          curSol.tracedPath.push_back(curPoint);
        else
          return foundEnd;
      }
    }
  }

 public:
  MazeSolver();
  MazeSolver(Maze& initMaze);

  void SetMaze(Maze& initMaze);

  Solution solveMazeBlind(solveType type) {
    switch (type) {
      case DFS:
        Solution res;
        DFS_SOLVE({curMaze->getStart().first, curMaze->getStart().second}, res);
        return res;
        break;
    }
  }
};