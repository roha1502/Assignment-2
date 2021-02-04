// This program required the below files:
//   Robot.hpp
//   Robot.cpp

// To build:
//    g++ TestClassRobot_Main.cpp Robot.cpp -o TestClassRobot_Main

#include <iostream>
#include <string>
#include "Robot.hpp"

using namespace std;

int main()
{
    //Robot r1, r2;
    Robot r1(100, 200, 10, 20);
    Robot r2(200, 300);
    Robot r3;

    r1.display();
    r2.display();
    r3.display();

    r1.set(10,  5, 2, 3);
    r2.set( 4, 25, 3, 1);

    r1.move();
    r2.move();

    r1.display();
    r2.display();

    cout << r1.getX() << " " << r1.getY() << endl;
    cout << r2.getX() << " " << r2.getY() << endl;
    cout << r3.getX() << " " << r3.getY() << endl;
}