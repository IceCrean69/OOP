#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Car
{
    public:
        int speed;
        int milage;
        bool crashed;
        string type;
        Car(int s, int m, bool c)
        {
            this->speed = s;
            this->milage = m;
            this->crashed = c;
        };
        int carSpeed()
        {
            return speed;
        }
        void crashedCar()
        {
            if(crashed)
            {
                cout << "this car was crashed" << endl;
                return;
            }
            else
            {
                cout << "this car was not crashed" << endl;
                return;
            }
        }
        void carType()
        {
            cout << this->type << endl;
        }
};

class PrivateCar : public Car
{
    public: 
        string type = "Private";
        PrivateCar(int speed, int milage, bool crashed) : Car(speed, milage, crashed){}
};

class Truck: Car
{

};

int main()
{
    PrivateCar *pc = new PrivateCar(50,12300, false);
    pc->carType();
    return 0;
}