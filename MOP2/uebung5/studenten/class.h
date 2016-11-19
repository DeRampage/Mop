#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "student.h"

using namespace std;

/* Declaration of class Class *********************************************/
class Class
{
public:
    Class(const char* name){ this->name = name; };
	Class(string& name) { this->name = name; };
    ~Class() {students.clear();};
    void AddStudent(Student* student);
    void RemoveStudent(const Student* student);
    void ListStudents() const;
    void ListBestStudents(bool order) const;
    void PrintClassAverage() const;
    vector<const Student*> GetClassStudents() const
	{
        return students;
	}

private:
    vector<const Student*> students;
	string name;
};

