#include <iostream>
using namespace std;

#include "Robot.hpp"

Robot::Robot()
: x_(10), y_(20),      //initializers
  velx_(2), vely_(3)
{
    cout << "Default constructor called!" << endl;    
}

Robot::Robot(int x, int y, int velx, int vely)  //alternative constructor
: x_(x), y_(y),         //initializers
  velx_(velx), vely_(vely)
{
    cout << "Aternative constructor called!" << endl;
    // set(x, y, velx, vely);
}


void Robot::set(int x, int y, int velx, int vely)
{
    x_ = x;  y_ = y;
    velx_ = velx;  vely_ = vely;
}

void Robot::move()
{
    x_ = x_ + velx_;
    y_ = y_ + vely_;
}

int Robot::getX()
{
    return x_;
}

int Robot::getY()
{
    return y_;
}

void Robot::display()
{
    cout << "Position = (" <<    x_ << "," <<    y_ << ")" << endl;
    cout << "Velocity = <" << velx_ << "," << vely_ << ">" << endl;
}