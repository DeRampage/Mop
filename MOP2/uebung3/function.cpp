#include "function.h"
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

/* function classes implementation ******************************************/

/* ToDo: Methoden der Basisklasse implementieren */
BaseFunction::type BaseFunction::GetDisplayType() const{
    return this->displayType;
}

string BaseFunction::GetName() const{
    return this->name;
}

double BaseFunction::f(double x){
    return x;
}
bool BaseFunction::IsInRange(double x){
    if(this->xMin < x && this->xMax > x){
        return true;
    }
    else return false;
}
void BaseFunction::SetXRange(double xMin, double xMax){
    this->xMin = xMin;
    this->xMax = xMax;
}

double SimpleSquareFunction::f(double x){
    return x*x;
}
double SquareFunction::f(double x){
    return (a*x*x+b*x+c);
}
