#pragma once

#include <vector>
#include <iostream>
#include <string>

using namespace std;

/* Forward Declaration ****************************************************/
class Exam; 
class Examination;

/* Declaration of class Student *********************************************/
class Student
{
public:
	Student(char* name, char* surname)
	{
		this->name=name;
		this->surname=surname;
		this->regNumber=++currentRegNumber;
	};
	Student(string& name, string& surname)
	{
		this->name=name;
		this->surname=surname;
		this->regNumber=++currentRegNumber;
	};
	Student::~Student();

	void Print(void)
	{
		cout << endl << "Schueler: ";
		cout.width(20);
		cout.setf(ios::left);
		cout << surname+" "+name << " Nummer: " << regNumber;
	};
	void PrintExams(void);
	vector<Exam*> GetExams(void)
	{
		return exams;
	};
	double GetStudentsAverage(void);
	void AddExam(Exam* exam);

private:
	long regNumber;
	vector<Exam*>exams;
	static long currentRegNumber;
	string name;
	string surname;
};

/* Declaration of class Class *********************************************/
class Class
{
public:
	Class(char* name){ this->name = name; }; 
	Class(string& name) { this->name = name; };
	~Class();
	void AddStudent(Student* student);
	void ListStudents(void);
	void PrintClassAverage(void);
	vector<Student*> GetClassStudents(void)
	{
		return students;
	}

private:
	vector<Student*> students;
	string name;
};

/* Declaration of class Examination ******************************************/
/* The examination of a class of students */
class Examination
{
public: 
	Examination(char* name) { this->name = name; };
	Examination(string& name) { this->name = name; };
	void AddClass(Class* clss);
	void PrintParticipants(void);
	void Print(void) { cout << endl; cout << "Pruefung " << name; };
	void PrintResults(void);
	void Grading(void); /* ToDo: we'd need a teacher for sophisticated grading */
private:
	string name;
	vector <Student*> participants;
};

/* Declaration of class Exam *************************************************/
/* The result of one student passing/failing an examination */
class Exam
{
public:
	Exam(Examination*examination, Student* student, double mark=5.0) { this->examination = examination; this->student=student;this->mark = mark; };
	double GetMark(void) { return mark; };
	Examination* GetExamination(void) { return examination; };
	Student* GetStudent(void) { return student; };
	void Print(void) { examination->Print(); cout << " Note: " << mark; };
private:
	Examination* examination;
	Student* student;
	double mark;
};
