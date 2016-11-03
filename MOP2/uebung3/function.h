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
protected:
	type displayType;
	string name;
};

/* Derived Classes Declaration **********************************************/

/* ToDo */

class SimpleSquareFunction;

class SquareFunction;

class Derivation;
