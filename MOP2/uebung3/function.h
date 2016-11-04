#pragma once

#include <string>
#include <cfloat>
using namespace std;


/* Base Class Declaration ***************************************************/
class BaseFunction
{
public:
    typedef enum { Points, Lines } type;
    BaseFunction(string name, type displayType = Lines) : name(name)
    {
        this->displayType = displayType;
        SetXRange(-DBL_MAX,DBL_MAX);
    };

    //meine Änderungen:
    type GetDisplayType() const;
    string GetName() const;
    virtual double f(double x);
    bool IsInRange(double x);

protected:
	type displayType;
	string name;
    //meine Änderungen:
    double xMin = 0, xMax = 0;

    void SetXRange(double xMin, double xMax);
};

/* Derived Classes Declaration **********************************************/

/* ToDo */

class SimpleSquareFunction:public BaseFunction{
public:
    SimpleSquareFunction():BaseFunction("f(x)=x^2"){};

    double f(double x);


};

class SquareFunction:public BaseFunction{
public:
    SquareFunction(double a, double b, double c):BaseFunction("f(x)=ax^2+bx+c"){
        this->a = a;
        this->b = b;
        this->c = c;
    };
    double f(double x);
private:
    double a, b, c;
};

class Derivation;
