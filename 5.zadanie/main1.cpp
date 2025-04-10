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
};

class PrivateCar : public Car
{
    public: 
        PrivateCar(int speed, int milage, bool crashed) : Car(speed, milage, crashed){}

    void CarGoBRR()
    {
        cout << "this car goes brrr" << endl;
        return;
    }
    
    
};

class Truck: Car
{
    public:
        Truck (int speed, int milage, bool crashed) : Car(speed, milage, crashed){}

        void trucks()
        {
            cout << "i am an amerikan driver" << endl;
        }

};

int main()
{
    PrivateCar *pc = new PrivateCar(50,12300, false);
    Truck *truck = new Truck(40, 29301, true);
    pc->CarGoBRR();
    truck->trucks();
    return 0;
}