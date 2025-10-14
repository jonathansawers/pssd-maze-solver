#include "MazeSolver.h"

//dfs algorithm works by going as far as possible down one path, then backtracking if a dead end is reached
bool MazeSolver::DFS_SOLVE(point curPoint, vector<vector<bool>> &seen, Solution &curSol)
{
    int x = curPoint.first, y = curPoint.second;
    curSol.tracedPath.push_back(curPoint);
    if (curMaze->atEnd(curPoint))
        return true;

    auto &grid = curMaze->getGrid();
    seen[y][x] = true;

    //loop that checks all four directions
    for (int i = 0; i < 4; ++i)
    {
        if (grid[y][x].walls[i])
            continue;
        int nx = x + DIRS[i][0], ny = y + DIRS[i][1];
        if (nx < 0 || ny < 0 || ny >= (int)grid.size() ||
            nx >= (int)grid[0].size())
            continue;
        if (seen[ny][nx])
            continue;

        //recursive call that visits next cell
        if (DFS_SOLVE({nx, ny}, seen, curSol))
            return true;
        //if user chooses to include all navigation, we add the current point again, else backtrack
        if (INCLUDE_ALL_NAV)
            curSol.tracedPath.push_back(curPoint);
        else
            curSol.tracedPath.pop_back();
    }
    return false;
}

//bfs implementation that explores all neighbours at current depth before moving on to next depth level
void MazeSolver::BFS_SOLVE(point startPoint, Solution &curSol)
{
    vector<vector<point>> parent;
    if (!INCLUDE_ALL_NAV)
    {
        parent.resize(curMaze->getHeight(),
                      vector<point>(curMaze->getWidth(), {-1, -1}));
    }
    auto &grid = curMaze->getGrid();
    // start at the start point, then move out
    vector<vector<bool>> seen(curMaze->getHeight(),
                              vector<bool>(curMaze->getWidth(), false));

    int startX = startPoint.first;
    int startY = startPoint.second;

    seen[startY][startX] = true;

    queue<point> q;
    q.push(startPoint);

    while (!q.empty())
    {
        // get the top point
        auto [x, y] = q.front();
        q.pop();

        curSol.tracedPath.push_back({x, y});

        if (curMaze->atEnd({x, y}))
            break;

        //loop that explores all valid neighbours
        for (int i = 0; i < 4; i++)
        {
            if (grid[y][x].walls[i])
                continue;
            int nx = x + DIRS[i][0], ny = y + DIRS[i][1];
            if (nx < 0 || ny < 0 || ny >= (int)grid.size() ||
                nx >= (int)grid[0].size())
                continue;
            if (seen[ny][nx])
                continue;

            seen[ny][nx] = true;
            q.push({nx, ny});
            if (!INCLUDE_ALL_NAV)
                parent[ny][nx] = {x, y};
        }
    }

    //if user does not want to include all navigation, reconstruct the shortest path from the end to start
    if (!INCLUDE_ALL_NAV)
    {
        // trace through path to get parent
        vector<point> pathBack;
        auto [x, y] = curMaze->getEnd();
        pathBack.push_back(curMaze->getEnd());
        while ((x != startX || y != startY))
        {
            point nextPoint = parent[y][x];
            x = nextPoint.first;
            y = nextPoint.second;
            pathBack.push_back({x, y});
        }
        reverse(pathBack.begin(), pathBack.end());
        curSol.tracedPath = pathBack;
    }
}

//A* algorithm that uses heuristics to find shortest path towards the goal
void MazeSolver::A_STAR_SOLVE(point startPoint, Solution &curSol)
{
    auto &grid = curMaze->getGrid();
    int H = curMaze->getHeight(), W = curMaze->getWidth();
    //check if coordinates are in bounds
    auto inb = [&](int x, int y)
    { return x >= 0 && y >= 0 && x < W && y < H; };

    vector<vector<int>> g(H, vector<int>(W, INT_MAX));
    vector<vector<uint8_t>> closed(H, vector<uint8_t>(W, 0));
    vector<vector<point>> parent(H, vector<point>(W, {-1, -1}));

    point goal = curMaze->getEnd();

    //manhattan distance heuristic
    auto h = [&](int x, int y)
    {
        return abs(x - goal.first) + abs(y - goal.second);
    };

    priority_queue<Node, vector<Node>, NodeCmp> pq;

    int sx = startPoint.first, sy = startPoint.second;
    g[sy][sx] = 0;
    pq.push({sx, sy, 0, h(sx, sy)});

    bool reached = false;

    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();

        if (closed[cur.y][cur.x])
            continue;
        if (cur.g != g[cur.y][cur.x])
            continue;

        closed[cur.y][cur.x] = 1;
        if (INCLUDE_ALL_NAV)
            curSol.tracedPath.push_back({cur.x, cur.y});

        if (cur.x == goal.first && cur.y == goal.second)
        {
            reached = true;
            break;
        }

        //loop that explores all valid neighbours
        for (int i = 0; i < 4; ++i)
        {
            if (grid[cur.y][cur.x].walls[i])
                continue;
            int nx = cur.x + DIRS[i][0], ny = cur.y + DIRS[i][1];
            if (!inb(nx, ny) || closed[ny][nx])
                continue;

            int ng = cur.g + 1;
            if (ng < g[ny][nx])
            {
                g[ny][nx] = ng;
                parent[ny][nx] = {cur.x, cur.y};
                pq.push({nx, ny, ng, ng + h(nx, ny)});
            }
        }
    }

    //similar to bfs, if user does not want to include all navigation, reconstruct the shortest path from the end to start
    if (!INCLUDE_ALL_NAV && reached)
    {
        vector<point> path;
        int x = goal.first, y = goal.second;
        while (!(x == sx && y == sy))
        {
            path.push_back({x, y});
            auto p = parent[y][x];
            if (p.first == -1)
            {
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

MazeSolver::MazeSolver() {}

MazeSolver::MazeSolver(Maze &initMaze) { curMaze = &initMaze; }

void MazeSolver::SetMaze(Maze &initMaze) { curMaze = &initMaze; }

//solution function that calls the appropriate algorithm based on user input and measures time taken
Solution MazeSolver::solveMazeBlind(solveType type)
{
    Solution res;
    if (!curMaze)
        return res;

    auto t0 = chrono::steady_clock::now();
    vector<vector<bool>> seen(curMaze->getHeight(),
                              vector<bool>(curMaze->getWidth(), false));
    switch (type)
    {
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

bool MazeSolver::NodeCmp::operator()(const Node &a, const Node &b) const
{
    if (a.f != b.f)
        return a.f > b.f;
    return a.g < b.g;
}
