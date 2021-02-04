class Rover
{
 private:
 int x,y;
 Direction heading;
 char objectUnderRover;
 Map* p_mars; //a pointer to the map for Mars
 Map mapper; //a map that keeps track of observed cells so far

 public:
 Rover();
 void land(Map& mars); //links a map of Mars to a Rover
 bool turnLeft();
 bool turnRight();
 bool move();
 void displayMapper();
 bool executeCommand(char command);
}; //Rover