// This is a standalone program
//
// To build:
//    g++ TestClassRobot.cpp -o TestClassRobot

#include <iostream>
#include <string>

using namespace std;

class Robot
{
    public:  
        //behaviours. member functions, methods
        Robot();  //default constructor
        Robot(int x, int y, int velx=0, int vely=0);  //alternative constructor
        void set(int x, int y, int velx, int vely);  //setter function
        void move();   //setter function
         int getX();   //getter function
         int getY();   //getter function 
        void display(); 

    private:
        //aatributes, data members    
        int x_, y_;
        int velx_, vely_;

};

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

int main()
{
/*    int x1 = 10, y1 = 5;
    int velx1 = 2, vely1 = 3;
    int x2 = 10, y2 = 5;
    int velx2 = 2, vely2 = 3;
    displayPosition(x1, y1);
    displayPosition(x2, y2);

    move(x1, y1, velx1, vely1);
    move(x2, y2, velx2, vely2);

    displayPosition(x1, y1);
    displayPosition(x2, y2);
*/

    //Robot r1, r2;
    Robot r1(100, 200, 10, 20);
    Robot r2(200, 300);
    Robot r3;

    r1.display();
    r2.display();
    r3.display();

    //set(r1, 10,  5, 2, 3);
    //set(r2,  4, 25, 3, 1);
    r1.set(10,  5, 2, 3);
    r2.set( 4, 25, 3, 1);

    //move(r1);
    //move(r2);
    r1.move();
    r2.move();

    //display(r1);
    //display(r2);
    r1.display();
    r2.display();

    cout << r1.getX() << " " << r1.getY() << endl;
    cout << r2.getX() << " " << r2.getY() << endl;
    cout << r3.getX() << " " << r3.getY() << endl;
}