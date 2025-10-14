// header file of Mazesolver class
// containing functions and variables to solve the maze
#ifndef MAZE_SOLVE
#define MAZE_SOLVE

#include <chrono>

#include "Maze.h"
using namespace std;

using point = pair<int, int>; //coordinate point in the maze

// directions to go from each point
constexpr int DIRS[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}}; //left, down, right, up

//stores the result of a maze solving attempt
struct Solution
{
  vector<point> tracedPath;
  point foundEndpoint;
  double timeTaken = 0.0;
  Solution() : tracedPath({}), foundEndpoint({0, 0}) {};
};

//select the maze solving algorithm
enum solveType
{
  DFS,
  BFS,
  A_STAR
};

class MazeSolver
{
private:
  Maze *curMaze;
  bool INCLUDE_ALL_NAV = false;

  //dfs algorithm (recursive)
  bool DFS_SOLVE(point curPoint, vector<vector<bool>> &seen, Solution &curSol);
 
  //bfs algorithm
  void BFS_SOLVE(point startPoint, Solution &curSol);

  //for A* algorithm (x, y are coordinates, g is cost from start to current node, f is total cost)
  struct Node
  {
    int x, y, g, f;
  };

  //used in priority queue for A* algorithm
  struct NodeCmp
  {
    bool operator()(const Node &a, const Node &b) const;
  };

  //A* algorithm
  void A_STAR_SOLVE(point startPoint, Solution &curSol);

public:
  MazeSolver();
  MazeSolver(Maze &initMaze);

  void SetMaze(Maze &initMaze);

  void showFullNav(bool showAllNav) { INCLUDE_ALL_NAV = showAllNav; }

  Solution solveMazeBlind(solveType type);
};

#endif