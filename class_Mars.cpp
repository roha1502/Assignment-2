#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cctype>
#include <string>
using namespace std;
#pragma once

//
// Mars class
//
class Mars {
    private:
        vector<vector<char>> map;
        int dimX, dimY;
    public:
        Mars() {
            init();
        }
        void init();
        void initPlayerMap();
        void display();
        void setObject(int, int, char);
        char getObject(int, int);
        int getDimX();
        int getDimY();
        bool isInsideMap(int, int);
        bool isEmpty(int, int);
        bool isTrap(int, int);
        bool isGold(int, int);
        bool checkPath(int, int, Mars &mars);
        int sufficientGold();
};

//
// initialise map (with objects)
void Mars::init() {
    cout << "enter x-dimension:\n==> ";
    cin >> dimX;
    cout << "enter y-dimension:\n==> ";
    cin >> dimY;

    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ',
                      '@', '@', '#', '#'};

    map.resize(dimY); // create dimY rows
    for (int i=0; i<dimY; i++)
        map[i].resize(dimX);  // create dimX columns

    for (int i=0; i<map.size(); i++) {
        for (int j=0; j<map[i].size(); j++) {
            int objNo = rand() % 10;
            map[i][j] = objects[objNo];
        }
    }
}

//
// display map
void Mars::display() {
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
// return x-dimension of the map
int Mars::getDimX() {
    return dimX;
}
 
//
// return y-dimension of the map
int Mars::getDimY() {
    return dimY;
}

//
// return the object at a specific coordinate
char Mars::getObject(int x, int y) {
    return map[y-1][x-1];
}

//
// place an object at a specific coordinate
void Mars::setObject(int x, int y, char obj) {
    map[y-1][x-1] = obj;
}

//
// is the cell at (x,y) empty ?
bool Mars::isEmpty(int x, int y) {
    if (map[y-1][x-1] == ' ')
        return true;
    else
        return false;
}

//
// is the cell at (x,y) within the map ?
bool Mars::isInsideMap(int x, int y) {
    if (y > 0 && y-1 < dimY && x > 0 && x-1 < dimX)
        return true;
    else
        return false;
}

//
// is the cell at (x,y) a trap ?
bool Mars::isTrap(int x, int y) {
    if (map[y-1][x-1] == '#')
        return true;
    else
        return false;
}

//
// is the cell at (x,y) a gold ?
bool Mars::isGold(int x, int y) {
    if (map[y-1][x-1] == '$')
        return true;
    else
        return false;
}

//
// can the rover move to cell at (x,y) ?
bool Mars::checkPath(int x, int y, Mars &mars) {
    if (mars.isInsideMap(x,y)) {
        if (mars.isEmpty(x,y) || mars.isGold(x,y))
            return true;
        else
            return false;
    }
    else
        return false;
}

//
// checks the entire map array for the amount of gold
int Mars::sufficientGold() {
    int noOfGold = 0;
    for (int i=0; i<map.size(); i++) {
        for (int j=0; j<map[i].size(); j++) {
            if (map[i][j] == '$')
                noOfGold++;
        }
    }
    return noOfGold;
}
