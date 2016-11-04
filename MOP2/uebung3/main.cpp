#include <QApplication>
#include "function.h"
#include "plotter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // First Test
    BaseFunction line("f(x)=x");

    Plotter myPlot=Plotter(&line,30,30);
    myPlot.SetXAxis(-10, 20, 2, 0.5);
    myPlot.SetYAxis(-10, 50, 10, 1);
    myPlot.Draw();

    // Second Test

    SimpleSquareFunction q;
    myPlot.AddFunction(&q);
    myPlot.Draw();

    // Third Test

    SquareFunction s(-0.75,10.0,10.0);
    myPlot.AddFunction(&s);
    myPlot.Draw();

    // Fourth Test

//    Derivation df(&s);

//    Plotter myPlot2(&df,350,150,320,640);
//    myPlot2.SetXAxis(-10,20,5,1);
//    myPlot2.SetYAxis(-10,60,5,1);
//    myPlot2.AddFunction(&s);
//    myPlot2.Draw();

    return a.exec();
}
