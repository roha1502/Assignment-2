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
    if (y-1 > 0 && y-1 < dimY && x-1 > 0 && x-1 < dimX)
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
    if ( ( mars.isEmpty(x,y) || mars.isGold(x,y) ) && mars.isInsideMap(x,y) )
        return true;
    else
        return false;
}

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
        bool ableToMove(Mars &mars);
        void moveRover(Mars &mars, Rover &rover);
        void moveRoverGod(Mars &mars, Rover &rover, char);
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
// is the cell in front of the rover empty, a gold, or a trap ?
bool Rover::ableToMove(Mars &mars) {
    switch(heading) {
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

void displayInfo (Mars &, Rover &);

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

    displayInfo(mars,rover);
}

//
// invisible rover for gold generation
void Rover::moveRoverGod(Mars &mars, Rover &rover, char t) {    // - moves with disregard to objects (traps or mountains)
    switch(heading) {                                           // - turns around if it reaches the edge
            case '^':                                           // - place the character of variable t in its path (see the generateGold function)
                if (mars.isInsideMap(x,y+1)) {
                mars.setObject(x, y, t);
                y++;
                }
                else {
                    rover.turnRoverRight(mars,rover);
                    rover.turnRoverRight(mars,rover);
                }
            break;
            case 'v':
                if (mars.isInsideMap(x,y-1)) {
                mars.setObject(x, y, t);
                y--;
                }
                else {
                    rover.turnRoverRight(mars,rover);
                    rover.turnRoverRight(mars,rover);
                }
            break;
            case '>':
                if (mars.isInsideMap(x+1,y)) {
                mars.setObject(x, y, t);
                x++;
                }
                else {
                    rover.turnRoverRight(mars,rover);
                    rover.turnRoverRight(mars,rover);
                }
            break;
            case '<':
                if (mars.isInsideMap(x-1,y)) {
                mars.setObject(x, y, t);
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
// generate gold (with rover) *using rover to generate gold ensures that the gold is reachable
void Rover::generateGold(Mars &mars, Rover &rover) {
    int t = 0, t2, gold;
    cout << "enter amounts of gold:\n==> ";
    cin >> gold;

    char possibleHeading[] = {'^', '>', '<', 'v'};
    while (mars.sufficientGold() < gold) {
        for (int i=0; i<5; i++) {
            t2 = (rand() % 10) + 1;
            if (t2 < 3) {
                rover.moveRoverGod(mars, rover, '$');
                t++;
            }
            else if (t2 >= 3 && t2 < 8)
                rover.moveRoverGod(mars, rover, ' ');
            else
                rover.moveRoverGod(mars, rover, '#');

            if (t2 > 6)
                heading = possibleHeading[ rand() % 4 ];
        }
    }
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
    //mars.display();

    //displayInfo(mars,rover);
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

    //displayInfo(mars,rover);
}

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
                //displayInfo(mars,rover);
            break;
            case 'r':
                rover.turnRoverRight(mars,rover);
                displayInfo(mars,rover);
            break;
            case 'l':
                rover.turnRoverLeft(mars,rover);
                displayInfo(mars,rover);
            break;
            case 'q':
            break;
        }
    }
}

// display map + current heading
void displayInfo(Mars &mars, Rover &rover) {
    mars.display();
    cout << "the current heading is [" << rover.getHeading() << "]\n";
    cout << "gold left to be collected = " << mars.sufficientGold() << "\n";
}

int Mars::sufficientGold() {
    int t = 0;
    for (int i=0; i<map.size(); i++) {
        for (int j=0; j<map[i].size(); j++) {
            if (map[i][j] == '$')
                t++;
        }
    }

    //cout << "t = " << t << '\n';
    return t;
}

int main() {
    srand(time(NULL));

    Mars mars;
    Rover rover;

    //mars.display();
    rover.land(mars);

    //mars.setObject(5,8,'#');
    displayInfo(mars,rover);

    //string t = (mars.isTrap(5,8)) ? "isTrap = true\n":"isTrap = false\n";
    //cout << t;
    //string t = (mars.isGold(5,8)) ? "isGold = true\n":"isGold = false\n";
    //cout << t;
    //t = (mars.checkPath(5,8,mars)) ? "checkPath = true\n":"checkPath = false\n";
    //cout << t;

    rover.generateGold(mars,rover);
    mars.sufficientGold();

    rover.land(mars);
    displayInfo(mars,rover);

    getInput(mars,rover);

    return 0;
}