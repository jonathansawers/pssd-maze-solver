// header file of Mazesolver class
// containing functions and variables to solve the maze
#ifndef MAZE_SOLVE
#define MAZE_SOLVE

#include <chrono>

#include "Maze.h"
using namespace std;

using point = pair<int, int>;

// directions to go from each point
constexpr int DIRS[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

struct Solution {
  vector<point> tracedPath;
  point foundEndpoint;
  long long timeTaken = 0;
  Solution() : tracedPath({}), foundEndpoint({0, 0}) {};
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

  void BFS_SOLVE(point startPoint, Solution& curSol) {
    vector<vector<point>> parent;
    if (!INCLUDE_ALL_NAV) {
      parent.resize(curMaze->getHeight(),
                    vector<point>(curMaze->getWidth(), {-1, -1}));
    }
    auto& grid = curMaze->getGrid();
    // start at the start point, then move out
    vector<vector<bool>> seen(curMaze->getHeight(),
                              vector<bool>(curMaze->getWidth(), false));

    int startX = startPoint.first;
    int startY = startPoint.second;

    seen[startY][startX] = true;

    queue<point> q;
    q.push(startPoint);

    while (!q.empty()) {
      // get the top point
      auto [x, y] = q.front();
      q.pop();

      curSol.tracedPath.push_back({x, y});

      if (curMaze->atEnd({x, y})) break;

      for (int i = 0; i < 4; i++) {
        if (grid[y][x].walls[i]) continue;
        int nx = x + DIRS[i][0], ny = y + DIRS[i][1];
        if (nx < 0 || ny < 0 || ny >= (int)grid.size() ||
            nx >= (int)grid[0].size())
          continue;
        if (seen[ny][nx]) continue;

        seen[ny][nx] = true;
        q.push({nx, ny});
        if (!INCLUDE_ALL_NAV) parent[ny][nx] = {x, y};
      }
    }

    if (!INCLUDE_ALL_NAV) {
      // trace through path to get parent
      vector<point> pathBack;
      auto [x, y] = curMaze->getEnd();
      pathBack.push_back(curMaze->getEnd());
      while ((x != startX || y != startY)) {
        point nextPoint = parent[y][x];
        x = nextPoint.first;
        y = nextPoint.second;
        pathBack.push_back({x, y});
      }
      reverse(pathBack.begin(), pathBack.end());
      curSol.tracedPath = pathBack;
    }
  }

  struct Node {
    int x, y, g, f;
  };
  struct NodeCmp {
    bool operator()(const Node& a, const Node& b) const {
      if (a.f != b.f) return a.f > b.f;
      return a.g < b.g;
    }
  };

  void A_STAR_SOLVE(point startPoint, Solution& curSol) {
    auto& grid = curMaze->getGrid();
    int H = curMaze->getHeight(), W = curMaze->getWidth();
    auto inb = [&](int x, int y) { return x >= 0 && y >= 0 && x < W && y < H; };

    vector<vector<int>> g(H, vector<int>(W, INT_MAX));
    vector<vector<uint8_t>> closed(H, vector<uint8_t>(W, 0));
    vector<vector<point>> parent(H, vector<point>(W, {-1, -1}));

    point goal = curMaze->getEnd();
    auto h = [&](int x, int y) {
      return abs(x - goal.first) + abs(y - goal.second);
    };

    priority_queue<Node, vector<Node>, NodeCmp> pq;

    int sx = startPoint.first, sy = startPoint.second;
    g[sy][sx] = 0;
    pq.push({sx, sy, 0, h(sx, sy)});

    bool reached = false;

    while (!pq.empty()) {
      Node cur = pq.top();
      pq.pop();

      if (closed[cur.y][cur.x]) continue;
      if (cur.g != g[cur.y][cur.x]) continue;

      closed[cur.y][cur.x] = 1;
      if (INCLUDE_ALL_NAV) curSol.tracedPath.push_back({cur.x, cur.y});

      if (cur.x == goal.first && cur.y == goal.second) {
        reached = true;
        break;
      }

      for (int i = 0; i < 4; ++i) {
        if (grid[cur.y][cur.x].walls[i]) continue;
        int nx = cur.x + DIRS[i][0], ny = cur.y + DIRS[i][1];
        if (!inb(nx, ny) || closed[ny][nx]) continue;

        int ng = cur.g + 1;
        if (ng < g[ny][nx]) {
          g[ny][nx] = ng;
          parent[ny][nx] = {cur.x, cur.y};
          pq.push({nx, ny, ng, ng + h(nx, ny)});
        }
      }
    }

    if (!INCLUDE_ALL_NAV && reached) {
      vector<point> path;
      int x = goal.first, y = goal.second;
      while (!(x == sx && y == sy)) {
        path.push_back({x, y});
        auto p = parent[y][x];
        if (p.first == -1) {
          path.clear();
          break;
        }
        x = p.first;
        y = p.second;
      }
      if (!path.empty() || (sx == goal.first && sy == goal.second))
        path.push_back({sx, sy}), reverse(path.begin(), path.end());
      curSol.tracedPath = path;
    }
  }

 public:
  MazeSolver();
  MazeSolver(Maze& initMaze);

  void SetMaze(Maze& initMaze);

  void showFullNav(bool showAllNav) { INCLUDE_ALL_NAV = showAllNav; }

  Solution solveMazeBlind(solveType type) {
    Solution res;
    if (!curMaze) return res;

    auto t0 = chrono::steady_clock::now();
    vector<vector<bool>> seen(curMaze->getHeight(),
                              vector<bool>(curMaze->getWidth(), false));
    switch (type) {
      case DFS:

        DFS_SOLVE(curMaze->getStart(), seen, res);
        // return res;
        break;
      case BFS:

        BFS_SOLVE(curMaze->getStart(), res);
        // return res;
        break;
      case A_STAR:
        // TODO: Implement A* algorithm
        A_STAR_SOLVE(curMaze->getStart(), res);
        // return res;
        break;
      default:
        break;
    }
    auto t1 = chrono::steady_clock::now();
    res.timeTaken = chrono::duration<double, milli>(t1 - t0).count();
    return res;
  }
};

#endif