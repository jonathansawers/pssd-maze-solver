// header file of Mazesolver class
// containing functions and variables to solve the maze
#ifndef MAZE_SOLVE
#define MAZE_SOLVE

#include "Maze.h"
using namespace std;

using point = pair<int, int>;

// directions to go from each point
constexpr int DIRS[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

struct Solution {
  vector<point> tracedPath;
  point foundEndpoint;
  Solution() : foundEndpoint({0, 0}), tracedPath({}) {};
};

enum solveType { DFS, BFS, A_STAR };

class MazeSolver {
  Maze* curMaze;
  bool INCLUDE_ALL_NAV = false;

  bool DFS_SOLVE(point curPoint, vector<vector<bool>>& seen, Solution& curSol) {
    int x = curPoint.first, y = curPoint.second;
    curSol.tracedPath.push_back(curPoint);
    if (curMaze->atEnd(curPoint)) return true;

    auto& grid = curMaze->getGrid();
    seen[y][x] = true;

    for (int i = 0; i < 4; ++i) {
      if (grid[y][x].walls[i]) continue;
      int nx = x + DIRS[i][0], ny = y + DIRS[i][1];
      if (nx < 0 || ny < 0 || ny >= (int)grid.size() ||
          nx >= (int)grid[0].size())
        continue;
      if (seen[ny][nx]) continue;

      if (DFS_SOLVE({nx, ny}, seen, curSol)) return true;
      if (INCLUDE_ALL_NAV)
        curSol.tracedPath.push_back(curPoint);
      else
        curSol.tracedPath.pop_back();
    }
    return false;
  }

 public:
  MazeSolver();
  MazeSolver(Maze& initMaze);

  void SetMaze(Maze& initMaze);

  void showFullNav(bool showAllNav) { INCLUDE_ALL_NAV = showAllNav; }

  Solution solveMazeBlind(solveType type) {
    Solution res;
    if (!curMaze) return res;

    vector<vector<bool>> seen(curMaze->getHeight(),
                              vector<bool>(curMaze->getWidth(), false));

    switch (type) {
      case DFS:

        DFS_SOLVE(curMaze->getStart(), seen, res);
        return res;
        break;
    }
  }
};

#endif