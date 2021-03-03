#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cctype>
#include <string>
#include "class_Mars.cpp"
using namespace std;
#pragma once

//
// Rover class
//
class Rover {
    private:
        int x, y;
        char heading;
    public:
        Rover() {
        }
        void land(Mars &mars);
        char getHeading();
        int getDimX();
        int getDimY();
        bool ableToMove(Mars &mars);
        void moveRover(Mars &mars, Rover &rover);
        void roverGoldMode(Mars &mars, Rover &rover, char);
        void turnRoverRight(Mars &mars, Rover &rover);
        void turnRoverLeft(Mars &mars, Rover &rover);
        void generateGold(Mars &mars, Rover &rover);
};

//
// place rover in the middle of the map
void Rover::land(Mars &mars) {
    char possibleHeading[] = {'^', '>', '<', 'v'};

    x = mars.getDimX() / 2;
    y = mars.getDimY() / 2;
    heading = possibleHeading[ rand() % 4 ];
    heading = '^';
    mars.setObject(x,y,heading);
}

//
// return heading of rover
char Rover::getHeading() {
    return heading;
}

//
// return rover's x-coordinate
int Rover::getDimX() {
    return x;
}

//
// return rover's y-coordinate
int Rover::getDimY() {
    return y;
}

//
// can the rover move into the cell in front of it ?
bool Rover::ableToMove(Mars &mars) {                    // - calls mars.checkPath() with coordinates being the cell directly
    switch(heading) {                                   //   in front of the rover (depending on its heading)
            case '^':
                if (mars.checkPath(x, y+1, mars))
                    return true;
                else
                    return false;
            break;
            case 'v':
                if (mars.checkPath(x, y-1, mars)) 
                    return true;
                else
                    return false;
            break;
            case '>':
                if (mars.checkPath(x+1, y, mars))
                    return true;
                else
                    return false;
            break;
            case '<':
                if (mars.checkPath(x-1, y, mars))
                    return true;
                else
                    return false;
            break;
            default:
                return false;
            break;
    }
}

//
// move the rover (if no obstructions)
void Rover::moveRover(Mars &mars, Rover &rover) {
    if (rover.ableToMove(mars)) {
        switch(heading) {
                case '^':
                    mars.setObject(x, y, ' ');
                    y++;
                    mars.setObject(x, y, heading);
                break;
                case 'v':
                    mars.setObject(x, y, ' ');
                    y--;
                    mars.setObject(x, y, heading);
                break;
                case '>':
                    mars.setObject(x, y, ' ');
                    x++;
                    mars.setObject(x, y, heading);
                break;
                case '<':
                    mars.setObject(x, y, ' ');
                    x--;
                    mars.setObject(x, y, heading);
                break;
        }
    }
    else
        cout << "rover cannot move there !";
}

//
// turn rover right
void Rover::turnRoverRight(Mars &mars, Rover &rover) {
    switch(heading) {
            case '^':
                heading = '>';
            break;
            case 'v':
                heading = '<';
            break;
            case '>':
                heading = 'v';
            break;
            case '<':
                heading = '^';
            break;
        }
    mars.setObject(x,y,heading);
}

//
// turn rover left
void Rover::turnRoverLeft(Mars &mars, Rover &rover) {
    switch(heading) {
            case '^':
                heading = '<';
            break;
            case 'v':
                heading = '>';
            break;
            case '>':
                heading = '^';
            break;
            case '<':
                heading = 'v';
            break;
        }
    mars.setObject(x,y,heading);
}

//
// rover for gold generation
void Rover::roverGoldMode(Mars &mars, Rover &rover, char placeObject) {    // - moves with disregard to objects (traps or mountains)
    switch(heading) {                                                      // - turns around if it reaches the edge
            case '^':                                                      // - place the character of variable placeObject in its path
                if (mars.isInsideMap(x,y+1)) {                             //   (see the generateGold function)
                mars.setObject(x, y, placeObject);
                y++;
                }
                else {
                    rover.turnRoverRight(mars,rover);
                    rover.turnRoverRight(mars,rover);
                }
            break;
            case 'v':
                if (mars.isInsideMap(x,y-1)) {
                mars.setObject(x, y, placeObject);
                y--;
                }
                else {
                    rover.turnRoverRight(mars,rover);
                    rover.turnRoverRight(mars,rover);
                }
            break;
            case '>':
                if (mars.isInsideMap(x+1,y)) {
                mars.setObject(x, y, placeObject);
                x++;
                }
                else {
                    rover.turnRoverRight(mars,rover);
                    rover.turnRoverRight(mars,rover);
                }
            break;
            case '<':
                if (mars.isInsideMap(x-1,y)) {
                mars.setObject(x, y, placeObject);
                x--;
                }
                else {
                    rover.turnRoverRight(mars,rover);
                    rover.turnRoverRight(mars,rover);
                }
            break;
    }
}

//
// generate gold (with roverGoldMode)
void Rover::generateGold(Mars &mars, Rover &rover) {                    // - amount of gold the player needs to collect is determined by:
    int goldOrNot, gold = ( mars.getDimX() + mars.getDimX() ) / 3;      //   ( total x-dimension + total y-dimension ) / 3
                                                                        // - as the rover moves, it has a * 50% chance of changing direction
    char possibleHeading[] = {'^', '>', '<', 'v'};                      //                                * 20% chance of dropping a gold;
    while (mars.sufficientGold() < gold) {                              //                                  else leave the cell as empty
                                                                        // - mars.sufficientGold() checks the entire map array for the amount of gold
        for (int i=0; i<5; i++) {
            goldOrNot = (rand() % 10) + 1;

            if (goldOrNot > 5)
                heading = possibleHeading[ rand() % 4 ];

            if (goldOrNot < 3)
                rover.roverGoldMode(mars, rover, '$');
            else
                rover.roverGoldMode(mars, rover, ' ');
        }
    }
}