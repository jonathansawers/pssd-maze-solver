# **pssd-maze-solver**
**A high-performance maze generation and solving utility designed for COMPSCI 2203.**
**Group Name:** The Maze Runners
---

## **Overview**

`pssd-maze-solver` is a robust program capable of both generating unique, guaranteed-solvable mazes and finding optimal paths through them. It provides a platform for experimenting with classic graph search and maze generation algorithms.

## Motivation
The maze solver project provides both an educational and technical platform for exploring computer science concepts, offering a hands-on approach to understanding algorithmic design, graph traversal, recursion, and computational efficiency. By implementing and comparing algorithms such as Recursive Backtracking, Randomised Prims, Breadth-First Search, and Depth-First Search, it allowed us to experiment the trade-offs between performance, complexity, and path optimality.

### Key Features
* **Dynamic Generation:** Create unique mazes of any size using multiple established algorithms.
* **Advanced Solving:** Find the shortest, most efficient path from start to finish.
* **Custom Maze Support:** Easily upload and solve your own maze designs.
* **Visual Output:** Clear, simple output for visualising both the maze and the solved path.

---

## **Algorithms & Techniques**

### Maze Generation
* **Recursive Backtracking:** A depth-first search (DFS) based approach for generating mazes with long, winding corridors.
* **Randomized Prim's Algorithm:** A greedy, wall-erasing approach that often results in mazes with shorter dead-ends and a more "tree-like" structure.

### Maze Solving
* **Breadth-First Search (BFS):** Ensures the **shortest path** (fewest steps) is found.
* **Depth-First Search (DFS):** Used to explore alternative or non-optimal paths (if required).
* **A* Search (Planned Feature):** Quickly finds the shortest path in larger mazes by prioritizing directions closer to the goal.

---

## **Installation & Setup**

This project uses a standard `Makefile` for simple compilation.

1.  **Compile the Program:**
    The `make` command compiles the source files (`.c` or `.cpp`) and creates the executable.
    ```bash
    make
    ```

---

## **Usage**

Once compiled, run the executable `./maze` and follow the on-screen prompts for generation or solving.

### Basic Execution
```bash
./maze
```

## Reflections
You can find each group members' reflection in the 'reflections'[https://github.com/jonathansawers/pssd-maze-solver/tree/main/reflections] folder.
