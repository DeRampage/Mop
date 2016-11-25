#include <QApplication>
#include "BookForm.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	BookForm myBookForm(NULL);
	myBookForm.show();
	return app.exec();
}