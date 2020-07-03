#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <fstream>


using namespace std;

class measurements
{
    int feet;
    int inches;
    void adjust();//private function bs users would not see this
public:
    measurements(int inches) : inches(inches), feet(0) { adjust(); } // initializer list-- only for constructors
    //initialize variables and set them to their default value
    //inches goes into variable inches (whatever in paranthesis is parameter
    measurements(); //declaration
    // is default constructor
    int getFeet() const { return feet; }
    int getInches() const { return inches; }
    void set_inches(int inches); // declarations
    void set_feet(int feet);
};
measurements::measurements()
        :feet(0), inches(0) // same as line 26
{
    //feet = 0; //definition
    //inches = 0;
}
void measurements::set_inches(int inches) // need classname:: before definition of function
{
    this->inches = inches; // replace og inches variable (og is one with this infront of it)
    adjust();
}
void measurements::set_feet(int feet)
{
    this->feet = feet; // this refers to variable used to instantiate variable (when tying it into main class)
    adjust();
}
void measurements::adjust() //checks if valid
{
    feet += inches / 12;
    inches %= 12;

    if (inches < 0)
    {
        feet--;
        inches += 12;
    }
}

int main()
{
    measurements i; //class name first and then variable
    measurements x(-23);
    cout << i.getInches() << endl;
    cout << i.getFeet() << endl;
    cout << x.getInches() << endl;
    cout << x.getFeet() << endl;

    x.set_inches(7);
    cout << x.getInches() << endl;
    cout << x.getFeet() << endl;

    i.set_feet(10);
    i.set_inches(30);
    cout << i.getInches() << endl;
    cout << i.getFeet() << endl;

    return 0;
}
