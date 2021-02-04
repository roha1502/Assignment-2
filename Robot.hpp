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