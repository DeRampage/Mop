#pragma once

#include <vector>
#include <string>


using namespace std;
/* Forward Declaration *****************************************************/
class BaseFunction;
class QGraphicsView;

typedef struct axis
{
    double start;
    double end;
    double label;
    double tick;
    string title;
} tAxis;

/* Class Declaration *******************************************************/

class Plotter
{
public:
    Plotter(BaseFunction *f=NULL, int x1=20, int y1=20, int height=320, int width=320);
	virtual void Draw(void);
	void AddFunction(BaseFunction *f);
    virtual void SetXAxis(double xStart, double xEnd, double xLabel=100.0, double xTick=10.0, const char*name="X")
    {
        xAxis.start = xStart;
        xAxis.end = xEnd;
        xAxis.label = xLabel;
        xAxis.tick = xTick;
        xAxis.title = name;
    };
    virtual void SetYAxis(double yStart, double yEnd, double yLabel=100.0, double yTick=10.0, const char*name="Y")
    {
        yAxis.start = yStart;
        yAxis.end = yEnd;
        yAxis.label = yLabel;
        yAxis.tick = yTick;
        yAxis.title = name;
    };

protected:
	virtual void DrawBackground(void);
	virtual void DrawXAxis(void);
	virtual void DrawYAxis(void);
private:

	vector<BaseFunction*> fVec;
    tAxis xAxis { 0.0, 10.0, 1.0, 5.0, ""};
    tAxis yAxis { 0.0, 10.0, 1.0, 5.0, ""};
    int x1, y1, x2, y2;

    QGraphicsView* view { nullptr };
};


