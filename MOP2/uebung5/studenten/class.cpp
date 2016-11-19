#include "class.h"
#include "student.h"

/* Implementierung der Klasse Class() ************************************/

// ToDo AddStudent()
void Class::AddStudent(Student* student)
{
    students.insert(students.end(), student);
}

void Class::ListStudents() const
{
    cout << "\n" << name << "\n";
    /*
    for (std::vector<Student*>::iterator it = students.begin(); it != students.end(); ++it){
        Print(it);
    }
    */
    for(auto studentIt : students){
        studentIt->Print();
    }
}
void Class::PrintClassAverage() const
{
    int i = 0;
    double a = 0;
    for(auto studentIt : students){
        a=a+studentIt->GetStudentsAverage();
        i++;
    }
    a = a/i;
    cout << "\n" << name << " Durschnitt: " << a << "\n";
}
