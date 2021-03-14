#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <stdlib.h>
#include <cctype>
#include <string>
#include "class_Mars.cpp"
#include "class_Rover.cpp"
#include "class_PlayerMap.cpp"
using namespace std;
#pragma once

//
// Game class
//
class Game {
    public:
        void gameOverWin(Mars &mars, Rover &rover);
        void gameOverLose(Mars &mars, Rover &rover);
        void displayInfo(Mars &mars, Rover &rover, PlayerMap &pm);
        void moveRover(Mars &mars, Rover &rover, PlayerMap &pm);
        void turnRoverRight(Mars &mars, Rover &rover, PlayerMap &pm);
        void turnRoverLeft(Mars &mars, Rover &rover, PlayerMap &pm);
        void getInput(Mars &mars, Rover &rover, PlayerMap &pm);
        void startGame();

};

void Game::gameOverWin(Mars &mars, Rover &rover) {
    char input;

    if (mars.sufficientGold() == 0) {
        cout << "\n\nall gold has been collected, you've won !\n";
        cout << "\nnew game ? [y/n]\n==> ";

        while(1) {
            cin >> input;
            input = tolower(input);

            switch(input) {
                case 'y':
                    startGame();
                break;
                case 'n':
                    exit(EXIT_SUCCESS);
                break;
                default:
                    cout << "invalid input !\nnew game ? [y/n]\n==> ";
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
}

void Game::gameOverLose(Mars &mars, Rover &rover) {
    char input;

    if (rover.ableToMove() || mars.) {
        if (rover.isTrap(mars)) {
            cout << "\n\ngame over !\nyou've driven the rover into a trap.\n";
            cout << "\nnew game ? [y/n]\n==> ";
            
            while(1) {
                cin >> input;
                input = tolower(input);
                switch(input) {
                    case 'y':
                        startGame();
                    break;
                    case 'n':
                        exit(EXIT_SUCCESS);
                    break;
                    default:
                        cout << "invalid input !\nnew game ? [y/n]\n==> ";
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        }
    }
}

// display map + current heading
void Game::displayInfo(Mars &mars, Rover &rover, PlayerMap &pm) {
    pm.display();
    cout << "the current heading is [" << rover.getHeading() << "]\n";
    cout << "gold left to be collected = " << mars.sufficientGold() << "\n";
}

// grouping of all functions that run when the rover moves
void Game::moveRover(Mars &mars, Rover &rover, PlayerMap &pm) {
    gameOverLose(mars,rover);       // has the player lost ?

    pm.moveRover(mars,rover,pm);
    rover.moveRover(mars,rover);
    pm.RevealCells(mars,rover,pm);

    displayInfo(mars,rover,pm);

    gameOverWin(mars,rover);        // has the player won ?
}

// grouping of all functions that run when the rover turns right
void Game::turnRoverRight(Mars &mars, Rover &rover, PlayerMap &pm) {
    rover.turnRoverRight(mars,rover);

    pm.RevealCells(mars,rover,pm);
    displayInfo(mars,rover,pm);
}

// grouping of all functions that run when the rover turns left
void Game::turnRoverLeft(Mars &mars, Rover &rover, PlayerMap &pm) {
    rover.turnRoverLeft(mars,rover);

    pm.RevealCells(mars,rover,pm);
    displayInfo(mars,rover,pm);
}

// user menu input
void Game::getInput(Mars &mars, Rover &rover, PlayerMap &pm) {
    int x = mars.getDimX(), y = mars.getDimY();
    char input;

    while (1) {
        cout << "enter input [m/r/l/q]:\n==> ";
        cin >> input;
        input = tolower(input);

        switch(input)   {
            case 'm':
                moveRover(mars,rover,pm);
            break;
            case 'r':
                turnRoverRight(mars,rover,pm);
            break;
            case 'l':
                turnRoverLeft(mars,rover,pm);
            break;
            case 'q':
                exit(EXIT_SUCCESS);
            break;
            default:
                cout << "invalid input !\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
}

// grouping of all functions that run when the game starts (or restarts)
void Game::startGame() {
    Mars mars;
    
    PlayerMap pm;
    pm.initPlayerMap(mars);

    Rover rover;

    rover.land(mars);
    rover.generateGold(mars,rover);
    mars.sufficientGold();

    rover.land(mars);
    pm.RevealCells(mars,rover,pm);
    pm.display();

    getInput(mars,rover,pm);
}
