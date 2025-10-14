//for menusystem class that controls the user interface and interactions

#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

#include "Maze.h"
#include "MazeGenerator.h"
#include "MazeSolver.h"
#include "MazeDisplay.h"
#include <iostream>
#include <string>

class MenuSystem
{
private:
    MazeGenerator generator;
    Maze *currentMaze;
    MazeDisplay *display;
    MazeSolver *solver;

    // Menu display methods
    void displayMainMenu() const;
    void displayGenerationMenu() const;
    void displaySolverMenu() const;
    void displayDisplayMenu(bool solvingMode = false) const;

    // Input validation methods
    int getValidInt(const std::string &prompt, int min = 1, int max = 100) const;
    bool getValidBool(const std::string &prompt) const;

    // Menu action methods
    void generateMaze();
    void solveMaze();
    void displayMaze();
    void setMazeDimensions();
    void setStartEndPositions();

    // Utility methods
    void clearScreen() const;
    void pauseForUser() const;
    void showMazeInfo();

public:
    MenuSystem();
    ~MenuSystem();

    void run();
};

#endif
