#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cctype>
#include <string>
#include "class_Mars.cpp"
#include "class_Rover.cpp"
#include "class_PlayerMap.cpp"
using namespace std;

// display map + current heading
void displayInfo(Mars &mars, Rover &rover) {
    mars.display();
    cout << "the current heading is [" << rover.getHeading() << "]\n";
    cout << "gold left to be collected = " << mars.sufficientGold() << "\n";
}

// grouping of all functions that run when the rover moves
void moveRover(Mars &mars, Rover &rover, PlayerMap &pm) {
    pm.moveRover(mars,rover,pm);
    rover.moveRover(mars,rover);
    pm.RevealCells(mars,rover,pm);

    //displayInfo(mars,rover);
    pm.display();    
}

// grouping of all functions that run when the rover turns right
void turnRoverRight(Mars &mars, Rover &rover, PlayerMap &pm) {
    rover.turnRoverRight(mars,rover);

    //displayInfo(mars,rover);
    pm.RevealCells(mars,rover,pm);
    pm.display();
}

// grouping of all functions that run when the rover turns left
void turnRoverLeft(Mars &mars, Rover &rover, PlayerMap &pm) {
    rover.turnRoverLeft(mars,rover);

    //displayInfo(mars,rover);
    pm.RevealCells(mars,rover,pm);
    pm.display();
}

// user menu input
void getInput(Mars &mars, Rover &rover, PlayerMap &pm) {
    int x = mars.getDimX(), y = mars.getDimY();
    char input;

    while (tolower(input) != 'q') {
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
            
            break;
        }
    }
}

// grouping of all functions that run when the game starts (or restarts)
void startGame() {
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

int main() {
    srand(time(NULL));

    startGame();

    return 0;
}