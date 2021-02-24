#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cctype>
#include <string>
using namespace std;

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
        void display();
        int getDimX();
        int getDimY();
        char getObject(int, int);
        void setObject(int, int, char);
        bool isEmpty(int, int);
        bool isInsideMap(int, int);
};

//
// initialise map (with objects)
void Mars::init() {
    dimX = 10;
    dimY = 15;

    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ',
                      'X', '#', '@', '$'};

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
    //cout << "the object '" << obj << "' should be at row " << x << ", column " << y << endl;
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
    if (y >= 0 && y <= dimY && x >= 0 && x <= dimX)
        return true;
    else
        return false;
}

//
// Rover class
class Rover {
    private:
        int x, y;
        char heading;
    public:
        Rover() {
        }
        void land(Mars &mars);
        char getHeading();
        void getRoverLocation();
        void moveRover(Mars &mars, Rover &rover);
        void turnRoverRight(Mars &mars, Rover &rover);
        void turnRoverLeft(Mars &mars, Rover &rover);
};

//
// place rover in the middle of the map
void Rover::land(Mars &mars) {
    char possibleHeading[] = {'^', '>', '<', 'v'};

    x = mars.getDimX() / 2;
    y = mars.getDimY() / 2;
    heading = possibleHeading[ rand() % 4 ];
    //heading = '^';
    mars.setObject(x,y,heading);
}

//
// return the rover heading
char Rover::getHeading() {
    return heading;
}

//
// return the coordinates of the rover
void Rover::getRoverLocation() {
   cout << "the rover should be at row " << x << ", column " << y << endl; 
}

//
// move the rover (if no obstructions)
void Rover::moveRover(Mars &mars, Rover &rover) {
    bool temp = false;
    switch(heading) {
            case '^':
                if (mars.isEmpty(x,y+1) && mars.isInsideMap(x, y+1)) {
                    mars.setObject(x, y, ' ');
                    y++;
                    mars.setObject(x, y, heading);
                    temp = true;
                }
            break;
            case 'v':
                if (mars.isEmpty(x,y-1) && mars.isInsideMap(x, y-1)) {
                    mars.setObject(x, y, ' ');
                    y--;
                    mars.setObject(x, y, heading);
                    temp = true;
                }
            break;
            case '>':
                if (mars.isEmpty(x+1,y) && mars.isInsideMap(x+1, y)) {
                    mars.setObject(x, y, ' ');
                    x++;
                    mars.setObject(x, y, heading);
                    temp = true;
                }
            break;
            case '<':
                if (mars.isEmpty(x-1,y) && mars.isInsideMap(x-1, y)) {
                    mars.setObject(x, y, ' ');
                    x--;
                    mars.setObject(x, y, heading);
                    temp = true;
                }
            break;
        }
        if (temp) {
            mars.display();
            rover.getRoverLocation();
            cout << "current heading is [" << rover.getHeading() << "]" << "\n\n";
        }
        else
            cout << "object at row " << x << ", column " << y+1 << " is [" << mars.getObject(x,y+1) << "]\n" 
                 << "invalid movement !\n";
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
    mars.display();
    rover.getRoverLocation();
    cout << "current heading is [" << rover.getHeading() << "]" << "\n\n";
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
    mars.display();
    rover.getRoverLocation();
    cout << "current heading is [" << rover.getHeading() << "]" << "\n\n";
}

//
// get user input
void getInput(Mars &mars, Rover &rover) {
    int x = mars.getDimX(), y = mars.getDimY();
    char input;

    while (tolower(input) != 'q') {
        cout << "enter input [m/r/l/q]:\n==> ";
        cin >> input;
        input = tolower(input);

        switch(input)   {
            case 'm':
                rover.moveRover(mars,rover);
            break;
            case 'r':
                rover.turnRoverRight(mars,rover);
            break;
            case 'l':
                rover.turnRoverLeft(mars,rover);
            break;
            case 'q':

            break;
        }
    }
}

int main() {
    srand(time(NULL));
    Mars mars;
    Rover rover;

    rover.land(mars);
    mars.display();

    rover.getRoverLocation();
    cout << "current heading is [" << rover.getHeading() << "]" << "\n\n";

    getInput(mars, rover);

    return 0;
}