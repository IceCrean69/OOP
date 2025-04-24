#include <string>
#include <iostream>
#include <list>
#include <map>
#include <cmath>
#include <vector>
using namespace std;



class Vehicle {
protected:
    static int next_id;
    static int days_rented;

    int id;
    int price;
    string name;
    double daily_rate;
    bool rented;
    
    Vehicle(int p, string n, double rate)
      :id(next_id++), price(p), name(std :: move(n)), daily_rate(rate), rented(false)
    {}

public:
    virtual ~Vehicle() {}  
    int get_vehicle_id(){return this->id;}
    int get_price(){return this->price;}
    string get_name(){return this->name;}
    double get_rate(){return this->daily_rate;}
    int get_days_rented_for(){return this-> days_rented;}   
    string get_availibility(){return this->rented ? "available" : "rented";} 
    void change_availibility(){this->rented = !rented;}   
    void change_rent_days(int days){this->days_rented = days;}

    virtual void get_vehicle_stats() const
    {
        cout <<"Vehicle status: " << this->rented << endl;
        cout <<"Vehicle id: " << this->id << endl;
        cout <<"Vehicle name: " << this->name << endl;
        cout <<"Vehicle price for a day: " << this->price << endl;
        cout <<"Vehicle daily rate: " << this->daily_rate << endl;
    }
    virtual double calculate_rent_price(int day) = 0; 
    virtual void vehicle_list() = 0;
};

class Car : public Vehicle 
{
    private:
         class Engine
         {
                int horsepower;
                string type;
                Engine(int h, string t) : horsepower(h), type(t){};
                int engine_horsepower() const 
                { 
                    return horsepower; 
                }
                const string& engine_type() const 
                {
                    return type; 
                }
                friend class Car;
         };
        int seats_num;
        Engine* engine;

        int engine_horsepower_internal (Engine* engine) const {return engine->horsepower;}
        string engine_type_internal(Engine* engine) const {return engine->type;}
    public:
        Car(int price, string name, double rate, int horsepower, string engine_type, int sn)
        : Vehicle(price, std :: move(name), rate)
        , engine(new Engine(horsepower, engine_type))
        , seats_num(sn)
        {}

        double calculate_rent_price(int day) override {
            return price * pow((daily_rate / 100) + 1, day);
        }

        void vehicle_list() override{
            cout << daily_rate  << "%" << " daily interest" << endl;
            cout << engine->engine_horsepower() << " Horses" << endl;
        }
        
        int get_engine_horsepower()const {return this->engine_horsepower_internal(engine);}
        string get_engine_type()const{return this->engine_type_internal(engine);}

        void get_vehicle_stats() const override
        {
            Vehicle::get_vehicle_stats();
            cout <<"Vehicle horsepower: " << this->get_engine_horsepower() << endl;
            cout <<"Vehicle motor type " << this->get_engine_type() << endl;
            cout <<"this vehicle has " << this->seats_num << " seats" << endl;
            cout << " " << endl;
        }
};

class Truck : public Vehicle {
    private:
        double payload_capacity;
    public:
        Truck(int price, string name, double rate, double payload)
        : Vehicle(price, std :: move(name), rate)
        , payload_capacity(payload)
        {}

        double calculate_rent_price(int day) override {
            return price * pow((daily_rate / 100) + 1, day);
        }
        void vehicle_list() override{
            cout << "Truck id: " << this->id << " | Truck name: " << this->name << endl;        
            cout << "Renting price: " << this->price <<" With daily rate of: " << this->daily_rate<<"%" <<endl;        
            cout << "This truck can handle up to : " << this->payload_capacity<< "KG" << endl;             
        }
        void get_vehicle_stats() const override
        {
            Vehicle::get_vehicle_stats();
            cout <<"Vehicle payload capacity: " << this->payload_capacity << endl; 
            cout << " " << endl;
        }

};
class Manager {
    private:
        vector<Vehicle*> fleet;
        static int vehicle_num;
    public:
        vector<Vehicle*> get_all_cars(){return this->fleet;}        
        void add_Vehicle(Vehicle* vehicle)
        {
            fleet.push_back(vehicle);
            vehicle_num ++;
        }
        
        void vehicle_stats()
        {
            for(auto v : fleet)
            {
                v->get_vehicle_stats();
            }
        }
        void check_availability_vehicle(Vehicle* vehicle)
        {
            for(auto it = fleet.begin(); it != fleet.end(); ++it)
            {
                if((*it)->get_vehicle_id() == vehicle->get_vehicle_id() && vehicle->get_availibility() == "available")
                {
                    vehicle->change_availibility();
                    break;
                }
                else
                {
                    cout << "Vehicle not found :((" << endl;
                }
            }
        }
};

class Customer {
    private:
        static int next_id;

        int id;
        double balance;
        string name;
        string email;
        string contact;
        vector<Vehicle*> rented_vehicles;
    public:
        Customer(double b, string n, string e, string c): id(next_id++), balance(b), name(n), email(e), contact(c){};
        double get_balance(){return this->balance;}
        string get_name(){return this->name;}
        string get_email(){return this->email;}
        string get_contact(){return this->contact;}

        void get_rented_vehicles()
        {
            cout << "Rented vehicles for " << this->name << endl;
            for(auto r: rented_vehicles)
            {
                r->get_vehicle_stats();
            }
        }

        void car_rent(Car* car, int days, Manager* manager)
        {
            double price = car->calculate_rent_price(days);
            if(balance > price)
            {
                cout << "Do you want to rent this car for 1. yes/ 2. no" << price << endl;
                int choose;
                cin >> choose;
                if(choose == 1)
                {
                    balance -= car->calculate_rent_price(days);
                    car->change_rent_days(days);
                    car->change_availibility();
                    rented_vehicles.push_back(car);
                    cout << "car has been rented" << endl;
                    cout << "your current balance: "<< this->balance << endl;
                    cout << "" << endl;
                }
                else
                {
                    cout << "Vehicle has been rented";
                }
            }
            else
            {
                cout << "You can rent this car for max " << max_time_for_rent(car)<< " days"<< endl;
            }
        }

        int max_time_for_rent(Vehicle* vehicle)
        {
            double price = vehicle->get_price();
            int days = 0;
            while(balance > price )
            {
                price = price * (vehicle->get_rate() / 100 + 1);
                days++;
            }
            return days;
        }

        void car_return(Vehicle* vehicle, Manager manager)
        {
            for(auto re = rented_vehicles.begin(); re != rented_vehicles.end(); ++re)
            {
                if((*re)->get_vehicle_id() == vehicle->get_vehicle_id() && vehicle->get_availibility() == "rented")
                {
                    rented_vehicles.erase(re);
                    vehicle->change_availibility();
                    manager.add_Vehicle(vehicle);
                    break;
                }
                else
                {
                    cout << "Vehicle not found :((" << endl;
                }
            }
        }


};



int Manager :: vehicle_num = 0;
int Vehicle :: next_id = 0;
int Vehicle :: days_rented = 0;
int Customer :: next_id = 0;

int main() {
    Manager* manager = new Manager();
    Customer* jakub = new Customer(2000, "Jakub Galica", "jakubgalica@gmail.com", "0901 241 241");
    Car* car = new Car(200, "nieco", 2,210,"nieco", 5);
    Car* car1 = new Car(200, "filip", 2,210,"nieco", 5);
    Car* car2 = new Car(200, "nikto", 2,210,"nieco", 5);
    Truck* truck = new Truck(400, "Corvette", 5, 50);
    manager->add_Vehicle(truck);
    manager->add_Vehicle(car1);
    manager->add_Vehicle(car2);

    cout << car1->get_days_rented_for() << endl;
    car1->change_rent_days(5);
    cout << car1->get_days_rented_for() << endl;
    


    delete car;
    delete car1;
    delete car2;
    return 0;
}