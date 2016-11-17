#include "examination.h"
#include "student.h"
#include "class.h"

void Examination::AddClass(Class *clss)
{
    vector<const Student*> students = clss->GetClassStudents();
	participants.insert(participants.end(),students.begin(),students.end());

}
void Examination::PrintParticipants() const
{
	cout << endl << "Pruefung: " << name << endl;
    for (auto participant : participants)
	{
        participant->Print();
	}
	cout << endl;

}

void Examination::PrintResults() const
{
	cout << endl << "Ergebnisse Pruefung: " << name << endl;
    for (auto participant:participants)
	{
        participant->Print();
        //vector<Exam*> exams = participant->GetExams();
        for (auto exam : participant->GetExams() )
            if (exam->GetExamination()==this)
                cout << " Note: " << exam->GetMark();
	}
	cout << endl;
}

void Examination::Grading()
{
	/* give random marks */
    const double marks[11] { 1.0, 1.3, 1.7, 2.0, 2.3, 2.7, 3.0, 3.3, 3.7, 4.0, 5.0 };
	static unsigned int rnd=4712;
	int min = 0,
		max = 11;
	switch(examType)
	{
		case EASY:   max = 8; break;
		case NORMAL: min = 2; break;
		case HEAVY:  min = 5; break;
	}
    for (auto participant : participants)
	{
        Exam *exam = new Exam(this,marks[(rnd=rnd*17+1)%(max-min)+min]);
        participant->AddExam(exam);
	}
}

