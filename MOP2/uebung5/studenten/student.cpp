#include "student.h"
#include "examination.h"

Student::~Student()
{   
	for (unsigned int i=0;i<exams.size();i++)
	{
		delete exams[i];
	}

}

void Student::AddExam(Exam *exam) const
{
	exams.push_back(exam);
}

long Student::currentRegNumber = 0;

double Student::GetStudentsAverage(void) const
{
	double average=0.0;
	for (unsigned int i=0;i<exams.size();i++)
		average+=exams[i]->GetMark();
	return average/exams.size();
}

void Student::Print(void) const
{
	cout << endl << "Schueler: ";
	cout.width(20);
	cout.setf(ios::left);
	cout << surname+" "+name << " Nummer: " << regNumber;
};

void Student::PrintExams(void) const
{
	Print();
	for (unsigned int i=0;i<exams.size();i++)
		exams[i]->Print();
	cout << endl << "Durchschnitt: " << GetStudentsAverage();
	cout << endl;
}
