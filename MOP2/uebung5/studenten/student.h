#pragma once

#include <vector>
#include <iostream>
#include <string>

using namespace std;

/* Forward Declaration ****************************************************/
class Exam; 
class Examination;
class Class;

/* Declaration of class Student *********************************************/
class Student
{
public:
    Student(const char* name, const char* surname) : name(name),surname(surname)
	{
		this->regNumber=++currentRegNumber;
		exams.clear();
        current = NULL;
	};
	Student(string& name, string& surname) : name(name), surname(surname)
	{
		this->regNumber=++currentRegNumber;
		exams.clear();
        current = NULL;
	};
    ~Student();

    void Print() const;
    void PrintExams() const;
    Class* GetClass() const
	{
        return current;
	}
	void SetClass(Class *c)
	{
        current = c;
	}

	vector<Exam*> GetExams(void) const
	{
		return exams;
	};
	double GetStudentsAverage(void) const;
    void AddExam(Exam* exam) const;

private:
	long regNumber;
    mutable vector<Exam*>exams;
	static long currentRegNumber;
	string name;
	string surname;
    Class *current;
};

