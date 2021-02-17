#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cstdlib>
using namespace std;

// print map
void print(vector<vector<char>> w, int dimX) {
    // display column number
    cout << "     ";
    for (int m=0; m<dimX; m++) cout << setw(4) << left << m+1;

    // map formatting *for the upper edge of the map
    cout << endl << "    -";
    for(int m=0; m<dimX; m++) cout << "----";
    cout << endl;
    
    // print map
    for (int i=0; i<w.size(); i++) {
        // display row number and map formatting *for the left edge of the map
        cout << setw(4) << left << i+1 << "/ ";

        for (int j=0; j<w[i].size(); j++) {
            if(j!=w[i].size()-1) cout << w[i][j] << " | ";
            else {
                cout << w[i][j] << " /"; // map formatting *for the right edge of the map

                // map formatting *for separating each row
                cout << endl << "    -";
                for(int m=0; m<dimX; m++) cout << "----";
            }
        }

        cout << endl;
    }
}

// initialise map with objects
void initVector(vector <vector<char>> &w, char objects[]) {
    for (int i=0; i<w.size(); i++) {
        for (int j=0; j<w[i].size(); j++) {
            int objNo = rand() % 10;
            w[i][j] = objects[objNo];
        }
    }
}

int main() {
    srand(time(NULL));

    vector<vector<char>> map;
    int dimX, dimY;
    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ',
                      'X', '#', '@', '$'};

    cout << "enter desired x-dimension: \n==>  ";
    cin >> dimX;
    cout << "enter desired y-dimension: \n==>  ";
    cin >> dimY;

    cout << endl;

    map.resize(dimY); // create dimY rows
    for (int i=0; i<dimY; i++)
        map[i].resize(dimX);  // create dimX columns

    initVector(map, objects);
    print(map, dimX);

    cout << endl;
    
    return 0;
}