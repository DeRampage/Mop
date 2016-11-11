#include "MyString.h"
#include <cstring>
#include <iostream>
using namespace std;

int MyString::counter = 0; 

int MyString::Set(const MyString &newStr)
{
	return Set(newStr.Get());
}
int MyString::Set(const char *newStr)
{
	if (str)
	{
        delete[] str;
        str = nullptr;
	}
	if (newStr)
	{
		length = strlen(newStr);
        str = new char[length+1];
		if (str)
            strcpy(str, newStr);
	}
	return length;
}


MyString::MyString(const char *newStr)
{
	counter++;
	id = counter;
    str = nullptr;
	Set(newStr);
    cout << "Construct MyString " << id << ": <" << str << ">" << endl;
}


MyString::MyString(const MyString &newStr)
{
	counter++;
	id = counter;
    str = nullptr;
	Set(newStr.Get());
    cout << "Construct MyString " << id << ": <" << str << ">" << endl;
}


MyString::~MyString()
{
	if(str)
        cout << "Deconstruct MyString " << id << ": <" << str << ">" << endl;
        delete[] str;
}

