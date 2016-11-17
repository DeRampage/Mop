#include "class.h"
#include "student.h"

/* Implementierung der Klasse Class() ************************************/

// ToDo AddStudent()
void Class::AddStudent(Student* student) const
{
    vector<const Student*> studenten = this->GetClassStudents();
    studenten.insert(students.begin(), student);
}

// ToDo: ListStudents(void)
// ToDo: PrintClassAverage(void)

