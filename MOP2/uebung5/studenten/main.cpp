/* Uebung 5.2 */
#include "student.h"
#include "examination.h"
#include "class.h"

int main(void)
{
	// Klassen anlegen 
	Class class1("1. Klasse");
	class1.AddStudent(new Student("Duck","Donald"));
	class1.AddStudent(new Student("Duck","Daisy"));
	class1.AddStudent(new Student("Gans","Gustav"));
	class1.ListStudents();

	Class class2("2. Klasse");
	class2.AddStudent(new Student("Duesentrieb","Daniel"));
	class2.AddStudent(new Student("Duck","Dagobert"));
	class2.AddStudent(new Student("Klever","Klaas"));
	class2.ListStudents();

    // Pruefungen anlegen und durchfuehren

	Examination exam1("Mathe", Examination::EASY);
	exam1.AddClass(&class1);
	exam1.AddClass(&class2);
	exam1.PrintParticipants();
	exam1.Grading();
	exam1.PrintResults();
	
	Examination exam2("Physik", Examination::NORMAL);
	exam2.AddClass(&class2);
	exam2.Grading();
	exam2.PrintResults();
	
	Examination exam3("Deutsch", Examination::HEAVY);
	exam3.AddClass(&class2);
	exam3.AddClass(&class1);
	exam3.Grading();
	exam3.PrintResults();

    /* Uebung 5.2 c)
	
	// Klassendurchschnitt berechnen und ausgeben 
    class1.PrintClassAverage();
    class2.PrintClassAverage();

    /* Uebung 5.2 d)  */

    // ToDo: 1. Schueler auslesen

    /* Uebung  5.2 f) - Zusatzaufgabe

	Student* panzerknacker = new Student("Panzerknacker","176-77");
	Class class3 = Class("Sonderklasse");
	class1.AddStudent(panzerknacker);
	class2.AddStudent(panzerknacker);
	class3.AddStudent(panzerknacker);
	class1.ListStudents();
	class2.ListStudents();
	class3.ListStudents();

    /* Uebung  5.2 Zusatzaufgabe Lambda

    class1.ListBestStudents(true);
    class2.ListBestStudents(false);


	/* Ende */

    return 0;

}








		



