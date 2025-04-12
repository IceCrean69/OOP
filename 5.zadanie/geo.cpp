#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

class Geo
{
    protected:
        float height;
    public:
        Geo(float h)
        {
            this->height = h;
        }
        float obsah()
        {
            return height * height;
        };
        float obvod()
        {
            return 4 * height;
        }
};
class Rectangle : public Geo
{
    private:
        float width;
    public:
        Rectangle(float h, float w) : Geo(h)
        {
            this->width = w;
        };
    
        float obsah()
        {
            return width * height;
        }
        float obvod()
        {
            return 2 * width + 2* height;
        }
};

class Circle : Geo
{
    private: 
        float radius;
    public:
        Circle(float h, float r) : Geo(h)
        {
            this->radius = r;
        }
        
        float obsah()
        {
            return  M_PI * radius * radius;
        }
        float obvod()
        {
            return 2 * M_PI * radius;
        }
};

int main()
{
    Geo *cube = new Geo(5);
    Rectangle *rect = new Rectangle(15,10);
    Circle *cir = new Circle(5,10);
    cout << rect->obsah() << endl;
    cout<< cube->obsah() << endl;
    cout<< cir->obsah() << endl;
    return 0;
}