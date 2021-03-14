#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cctype>
#include <string>
#include "class_Mars.cpp"
#include "class_Rover.cpp"
using namespace std;
#pragma once

//                                      // - this class contains mostly retrofitted functions from Mars and Rover class
// Player Map class                     //   to create a map whose cells are hidden by '?', only revealing the cells as
//                                      //   the player moves through the map
class PlayerMap {                       // - revealCells() is the only new function exclusive to this class, others are
    private:                            //   slightly modified versions carried over from Rover and Mars class
        vector<vector<char>> map;
        int dimX, dimY;
    public:
        PlayerMap() {
        }
        void initPlayerMap(Mars &mars);
        void display();
        void setObject(int, int, char);
        void moveRover(Mars &mars, Rover &rover, PlayerMap &pm);
        void RevealCells(Mars &mars, Rover &rover, PlayerMap &pm);
};

//
// create a map with all objects being '?'
void PlayerMap::initPlayerMap(Mars &mars) {
    dimX = mars.getDimX();
    dimY = mars.getDimY();

    char objects[] = {'?'};

    map.resize(dimY); // create dimY rows
    for (int i=0; i<dimY; i++)
        map[i].resize(dimX);  // create dimX columns

    for (int i=0; i<map.size(); i++) {
        for (int j=0; j<map[i].size(); j++) {
            map[i][j] = *objects;
        }
    }
}

//
// place an object at a specific coordinate
void PlayerMap::setObject(int x, int y, char obj) {
    map[y-1][x-1] = obj;
}

//
// display map
void PlayerMap::display() {
    // map formatting *for the upper edge of the map
    cout << endl << "    -";
    for(int m=0; m<dimX; m++) cout << "----";
    cout << endl;
    
    // print map
    for (int i=map.size()-1; i>=0; i--) {
        // display row number and map formatting *for the left edge of the map
        cout << setw(4) << left << i+1 << "/ ";

        for (int j=0; j<map[i].size(); j++) {
            if(j!=map[i].size()-1) cout << map[i][j] << " | ";
            else {
                cout << map[i][j] << " /"; // map formatting *for the right edge of the map

                // map formatting *for separating each row
                cout << endl << "    -";
                for(int m=0; m<dimX; m++) cout << "----";
            }
        }
        cout << endl;
    }
    // display column number
    cout << "\n   ";
        for (int m=0; m<dimX; m++)
            cout << setw(4) << right << m+1;
    cout << endl << endl;
}

//
// move the rover in the player map accordingly to the actual rover in the actual map
void PlayerMap::moveRover(Mars &mars, Rover &rover, PlayerMap &pm) {
    if (rover.ableToMove(mars)) {
        switch(rover.getHeading()) {
                case '^':
                    pm.setObject(rover.getDimX(), rover.getDimY(), ' ');
                    pm.setObject(rover.getDimX(), rover.getDimY()+1, rover.getHeading());
                break;
                case 'v':
                    pm.setObject(rover.getDimX(), rover.getDimY(), ' ');
                    pm.setObject(rover.getDimX(), rover.getDimY()-1, rover.getHeading());
                break;
                case '>':
                    pm.setObject(rover.getDimX(), rover.getDimY(), ' ');
                    pm.setObject(rover.getDimX()+1, rover.getDimY(), rover.getHeading());
                break;
                case '<':
                    pm.setObject(rover.getDimX(), rover.getDimY(), ' ');
                    pm.setObject(rover.getDimX()-1, rover.getDimY(), rover.getHeading());
                break;
        }
    }
}

//
// reveal the three cells in front of the rover
void PlayerMap::RevealCells(Mars &mars, Rover &rover, PlayerMap &pm) {          // - all the if statements are to prevent the revealing of 
    switch(rover.getHeading()) {                                                //   non-existent cells when the rover is at the edges of the map
            case '^':                                                           // - otherwise, segmentation fault occurs
                if (mars.isInsideMap(rover.getDimX(),rover.getDimY()+1)) {
                    pm.setObject(rover.getDimX(), rover.getDimY()+1, mars.getObject(rover.getDimX(), rover.getDimY()+1));
                    pm.setObject(rover.getDimX()+1, rover.getDimY()+1, mars.getObject(rover.getDimX()+1, rover.getDimY()+1));
                    pm.setObject(rover.getDimX()-1, rover.getDimY()+1, mars.getObject(rover.getDimX()-1, rover.getDimY()+1));
                }
            break;
            case 'v':
                if (mars.isInsideMap(rover.getDimX(),rover.getDimY()-1)) {
                    pm.setObject(rover.getDimX(), rover.getDimY()-1, mars.getObject(rover.getDimX(), rover.getDimY()-1));
                    pm.setObject(rover.getDimX()+1, rover.getDimY()-1, mars.getObject(rover.getDimX()+1, rover.getDimY()-1));
                    pm.setObject(rover.getDimX()-1, rover.getDimY()-1, mars.getObject(rover.getDimX()-1, rover.getDimY()-1));
            }
            break;
            case '>':
                if (mars.isInsideMap(rover.getDimX()+1,rover.getDimY())) {
                    pm.setObject(rover.getDimX()+1, rover.getDimY(), mars.getObject(rover.getDimX()+1, rover.getDimY()));
                    if (mars.isInsideMap(rover.getDimX(),rover.getDimY()+1))
                        pm.setObject(rover.getDimX()+1, rover.getDimY()+1, mars.getObject(rover.getDimX()+1, rover.getDimY()+1));
                    if (mars.isInsideMap(rover.getDimX(),rover.getDimY()-1))
                        pm.setObject(rover.getDimX()+1, rover.getDimY()-1, mars.getObject(rover.getDimX()+1, rover.getDimY()-1));
                }
            break;
            case '<':
                if (mars.isInsideMap(rover.getDimX()-1,rover.getDimY())) {
                    pm.setObject(rover.getDimX()-1, rover.getDimY(), mars.getObject(rover.getDimX()-1, rover.getDimY()));
                    if (mars.isInsideMap(rover.getDimX(),rover.getDimY()+1))
                        pm.setObject(rover.getDimX()-1, rover.getDimY()+1, mars.getObject(rover.getDimX()-1, rover.getDimY()+1));
                    if (mars.isInsideMap(rover.getDimX(),rover.getDimY()-1))
                        pm.setObject(rover.getDimX()-1, rover.getDimY()-1, mars.getObject(rover.getDimX()-1, rover.getDimY()-1));
                }
            break;
    }
    pm.setObject(rover.getDimX(), rover.getDimY(), rover.getHeading());
}