#include "MenuSystem.h"
#include <iostream>
#include <limits>
#include <cstdlib>

MenuSystem::MenuSystem() : currentMaze(nullptr), display(nullptr), solver(nullptr) {}

MenuSystem::~MenuSystem() {
    delete currentMaze;
    delete display;
    delete solver;
}

void MenuSystem::run() {
    int choice;
    bool running = true;
    
    std::cout << Colors::BRIGHT_CYAN << "=== MAZE SOLVER PROGRAM ===" << Colors::RESET << std::endl;
    std::cout << "Welcome to the Interactive Maze Solver!" << std::endl;
    std::cout << "Generate mazes using different algorithms and solve them with various methods." << std::endl << std::endl;
    
    while (running) {
        displayMainMenu();
        choice = getValidInt("Enter your choice", 1, 6);
        
        switch (choice) {
            case 1:
                generateMaze();
                break;
            case 2:
                if (currentMaze) {
                    solveMaze();
                } else {
                    std::cout << Colors::YELLOW << "Please generate a maze first!" << Colors::RESET << std::endl;
                    pauseForUser();
                }
                break;
            case 3:
                if (currentMaze) {
                    displayMaze();
                } else {
                    std::cout << Colors::YELLOW << "Please generate a maze first!" << Colors::RESET << std::endl;
                    pauseForUser();
                }
                break;
            case 4:
                if (currentMaze) {
                    setStartEndPositions();
                } else {
                    std::cout << Colors::YELLOW << "Please generate a maze first!" << Colors::RESET << std::endl;
                    pauseForUser();
                }
                break;
            case 5:
                showMazeInfo();
                break;
            case 6:
                running = false;
                std::cout << Colors::GREEN << "Thank you for using the Maze Solver! Goodbye!" << Colors::RESET << std::endl;
                break;
        }
    }
}

void MenuSystem::displayMainMenu() const {
    clearScreen();
    std::cout << Colors::BRIGHT_CYAN << "=== MAIN MENU ===" << Colors::RESET << std::endl;
    std::cout << "1. " << Colors::GREEN << "Generate Maze" << Colors::RESET << std::endl;
    std::cout << "2. " << Colors::BLUE << "Solve Maze" << Colors::RESET << std::endl;
    std::cout << "3. " << Colors::YELLOW << "Display Maze" << Colors::RESET << std::endl;
    std::cout << "4. " << Colors::MAGENTA << "Set Start/End Positions" << Colors::RESET << std::endl;
    std::cout << "5. " << Colors::CYAN << "Show Maze Info" << Colors::RESET << std::endl;
    std::cout << "6. " << Colors::RED << "Exit" << Colors::RESET << std::endl;
    std::cout << std::endl;
}

void MenuSystem::displayGenerationMenu() const {
    std::cout << Colors::BRIGHT_CYAN << "=== MAZE GENERATION ===" << Colors::RESET << std::endl;
    std::cout << "1. " << Colors::GREEN << "DFS (Depth-First Search)" << Colors::RESET << " - Recursive backtracking" << std::endl;
    std::cout << "2. " << Colors::BLUE << "Prim's Algorithm" << Colors::RESET << " - Randomized minimum spanning tree" << std::endl;
    std::cout << "3. " << Colors::YELLOW << "Back to Main Menu" << Colors::RESET << std::endl;
    std::cout << std::endl;
}

void MenuSystem::displaySolverMenu() const {
    std::cout << Colors::BRIGHT_CYAN << "=== MAZE SOLVING ===" << Colors::RESET << std::endl;
    std::cout << "1. " << Colors::GREEN << "DFS (Depth-First Search)" << Colors::RESET << " - Recursive exploration" << std::endl;
    std::cout << "2. " << Colors::BLUE << "BFS (Breadth-First Search)" << Colors::RESET << " - Level-by-level exploration" << std::endl;
    std::cout << "3. " << Colors::MAGENTA << "A* (A-Star)" << Colors::RESET << " - Heuristic-based search" << std::endl;
    std::cout << "4. " << Colors::YELLOW << "Back to Main Menu" << Colors::RESET << std::endl;
    std::cout << std::endl;
}

void MenuSystem::displayDisplayMenu() const {
    std::cout << Colors::BRIGHT_CYAN << "=== DISPLAY OPTIONS ===" << Colors::RESET << std::endl;
    std::cout << "1. " << Colors::WHITE << "Basic Maze" << Colors::RESET << " - Just the maze structure" << std::endl;
    std::cout << "2. " << Colors::CYAN << "Colored Maze" << Colors::RESET << " - Maze with colors" << std::endl;
    std::cout << "3. " << Colors::GREEN << "Symbols Only" << Colors::RESET << " - Path with arrows and dots" << std::endl;
    std::cout << "4. " << Colors::YELLOW << "Back to Main Menu" << Colors::RESET << std::endl;
    std::cout << std::endl;
}

void MenuSystem::generateMaze() {
    clearScreen();
    displayGenerationMenu();
    
    int choice = getValidInt("Select generation algorithm", 1, 3);
    
    if (choice == 3) return;
    
    // Get maze dimensions
    int width = getValidInt("Enter maze width (5-50)", 5, 50);
    int height = getValidInt("Enter maze height (5-50)", 5, 50);
    
    std::cout << Colors::YELLOW << "Generating maze..." << Colors::RESET << std::endl;
    
    // Clean up previous maze
    delete currentMaze;
    delete display;
    delete solver;
    
    // Generate new maze
    switch (choice) {
        case 1:
            currentMaze = new Maze(generator.generateDFS(width, height));
            std::cout << Colors::GREEN << "DFS maze generated successfully!" << Colors::RESET << std::endl;
            break;
        case 2:
            currentMaze = new Maze(generator.generatePrim(width, height));
            std::cout << Colors::GREEN << "Prim's maze generated successfully!" << Colors::RESET << std::endl;
            break;
    }
    
    // Initialize display and solver
    display = new MazeDisplay(currentMaze);
    solver = new MazeSolver(*currentMaze);
    
    std::cout << Colors::CYAN << "Maze Info:" << Colors::RESET << std::endl;
    std::cout << "  Size: " << width << "x" << height << std::endl;
    std::cout << "  Start: (" << currentMaze->getStart().first << ", " << currentMaze->getStart().second << ")" << std::endl;
    std::cout << "  End: (" << currentMaze->getEnd().first << ", " << currentMaze->getEnd().second << ")" << std::endl;
    
    pauseForUser();
}

void MenuSystem::solveMaze() {
    clearScreen();
    displaySolverMenu();
    
    int choice = getValidInt("Select solving algorithm", 1, 4);
    
    if (choice == 4) return;
    
    // Configure solver
    bool showFullNav = getValidBool("Show full navigation (visited cells)? (y/n)");
    solver->showFullNav(showFullNav);
    
    std::cout << Colors::YELLOW << "Solving maze..." << Colors::RESET << std::endl;
    
    // Solve maze
    Solution solution;
    std::string algorithmName;
    
    switch (choice) {
        case 1:
            solution = solver->solveMazeBlind(DFS);
            algorithmName = "DFS";
            break;
        case 2:
            // BFS and A* not implemented yet, fall back to DFS
            std::cout << Colors::YELLOW << "BFS not implemented yet, using DFS instead." << Colors::RESET << std::endl;
            solution = solver->solveMazeBlind(DFS);
            algorithmName = "DFS (BFS fallback)";
            break;
        case 3:
            // A* not implemented yet, fall back to DFS
            std::cout << Colors::YELLOW << "A* not implemented yet, using DFS instead." << Colors::RESET << std::endl;
            solution = solver->solveMazeBlind(DFS);
            algorithmName = "DFS (A* fallback)";
            break;
    }
    
    // Display results
    std::cout << Colors::GREEN << "Solution found using " << algorithmName << "!" << Colors::RESET << std::endl;
    std::cout << "Path length: " << solution.tracedPath.size() << " steps" << std::endl;
    std::cout << "End point found: (" << solution.foundEndpoint.first << ", " << solution.foundEndpoint.second << ")" << std::endl;
    
    // Ask for display preference
    std::cout << std::endl;
    displayDisplayMenu();
    int displayChoice = getValidInt("How would you like to display the solution?", 1, 4);
    
    if (displayChoice != 4) {
        std::cout << std::endl;
        switch (displayChoice) {
            case 1:
                display->displayMaze();
                break;
            case 2:
                display->displayMazeWithColors(solution.tracedPath, {});
                break;
            case 3:
                display->displayMazeWithSymbols(solution.tracedPath, {});
                break;
        }
    }
    
    pauseForUser();
}

void MenuSystem::displayMaze() {
    clearScreen();
    displayDisplayMenu();
    
    int choice = getValidInt("Select display type", 1, 4);
    
    if (choice == 4) return;
    
    std::cout << std::endl;
    switch (choice) {
        case 1:
            display->displayMaze();
            break;
        case 2:
            display->displayMazeWithColors({}, {});
            break;
        case 3:
            display->displayMazeWithSymbols({}, {});
            break;
    }
    
    pauseForUser();
}

void MenuSystem::setStartEndPositions() {
    clearScreen();
    std::cout << Colors::BRIGHT_CYAN << "=== SET START/END POSITIONS ===" << Colors::RESET << std::endl;
    
    int width = currentMaze->getWidth();
    int height = currentMaze->getHeight();
    
    std::cout << "Current maze size: " << width << "x" << height << std::endl;
    std::cout << "Current start: (" << currentMaze->getStart().first << ", " << currentMaze->getStart().second << ")" << std::endl;
    std::cout << "Current end: (" << currentMaze->getEnd().first << ", " << currentMaze->getEnd().second << ")" << std::endl;
    std::cout << std::endl;
    
    int startX = getValidInt("Enter start X coordinate (0-" + std::to_string(width-1) + ")", 0, width-1);
    int startY = getValidInt("Enter start Y coordinate (0-" + std::to_string(height-1) + ")", 0, height-1);
    int endX = getValidInt("Enter end X coordinate (0-" + std::to_string(width-1) + ")", 0, width-1);
    int endY = getValidInt("Enter end Y coordinate (0-" + std::to_string(height-1) + ")", 0, height-1);
    
    currentMaze->setStart(startX, startY);
    currentMaze->setEnd(endX, endY);
    
    std::cout << Colors::GREEN << "Start and end positions updated!" << Colors::RESET << std::endl;
    std::cout << "New start: (" << startX << ", " << startY << ")" << std::endl;
    std::cout << "New end: (" << endX << ", " << endY << ")" << std::endl;
    
    pauseForUser();
}

void MenuSystem::showMazeInfo() {
    clearScreen();
    std::cout << Colors::BRIGHT_CYAN << "=== MAZE INFORMATION ===" << Colors::RESET << std::endl;
    
    if (!currentMaze) {
        std::cout << Colors::YELLOW << "No maze loaded. Please generate a maze first." << Colors::RESET << std::endl;
    } else {
        std::cout << "Maze Size: " << currentMaze->getWidth() << "x" << currentMaze->getHeight() << std::endl;
        std::cout << "Start Position: (" << currentMaze->getStart().first << ", " << currentMaze->getStart().second << ")" << std::endl;
        std::cout << "End Position: (" << currentMaze->getEnd().first << ", " << currentMaze->getEnd().second << ")" << std::endl;
        std::cout << "Total Cells: " << currentMaze->getWidth() * currentMaze->getHeight() << std::endl;
    }
    
    pauseForUser();
}

int MenuSystem::getValidInt(const std::string& prompt, int min, int max) const {
    int value;
    while (true) {
        std::cout << prompt << " (" << min << "-" << max << "): ";
        if (std::cin >> value && value >= min && value <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        } else {
            std::cout << Colors::RED << "Invalid input! Please enter a number between " << min << " and " << max << "." << Colors::RESET << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

bool MenuSystem::getValidBool(const std::string& prompt) const {
    char response;
    while (true) {
        std::cout << prompt << " (y/n): ";
        std::cin >> response;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (response == 'y' || response == 'Y') {
            return true;
        } else if (response == 'n' || response == 'N') {
            return false;
        } else {
            std::cout << Colors::RED << "Invalid input! Please enter 'y' or 'n'." << Colors::RESET << std::endl;
        }
    }
}

void MenuSystem::clearScreen() const {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void MenuSystem::pauseForUser() const {
    std::cout << std::endl << Colors::CYAN << "Press Enter to continue..." << Colors::RESET;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
