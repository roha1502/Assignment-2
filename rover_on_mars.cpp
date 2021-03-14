#include <iostream>
#include "class_Mars.cpp"
#include "class_Rover.cpp"
#include "class_PlayerMap.cpp"
#include "class_Game.cpp"

using namespace std;

int main() {
    srand(time(NULL));
    
    Game game;
    game.startGame();

    return 0;
}