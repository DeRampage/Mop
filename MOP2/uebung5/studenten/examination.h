#pragma once

#include <vector>
#include <iostream>
#include <string>

using namespace std;

/* Forward declaration */
class Class;
class Student;
/* Declaration of class Examination ******************************************/
/* The examination of a class of students */
class Examination
{
public:
	typedef enum { EASY, NORMAL, HEAVY } tExamType;
public: 
    Examination(const char* name, tExamType examType= NORMAL) {
		this->name = name; 
	    this->examType = examType;
	};
	Examination(string& name, tExamType examType= NORMAL) { 
		this->name = name; 
		this->examType = examType;
	};
	void AddClass(Class* clss);
    void PrintParticipants() const;
    void Print() const { cout << endl; cout << "Pruefung " << name; };
    void PrintResults() const;
    void Grading(); /* ToDo: we'd need a teacher for sophisticated grading */
private:
	string name;
	tExamType examType;
    vector <const Student*> participants;
};

/* Declaration of class Exam *************************************************/
/* The result of one student passing/failing an examination */
class Exam
{
public:
    Exam(const Examination*examination, double mark=5.0) {
        this->examination = examination;
        this->mark = mark;
    };
    double GetMark() const { return mark; };
    const Examination* GetExamination() const { return examination; };
    void Print() { examination->Print(); cout << " Note: " << mark; };
private:
    const Examination* examination;
    double mark;
};
