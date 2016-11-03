#include <sstream>
#include "plotter.h"
#include "function.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>


/* Plotter Implementation **************************************************/
Plotter::Plotter(BaseFunction *f,int x1,int y1,int width,int height)
{
    QGraphicsScene* scene = new QGraphicsScene();
    view = new QGraphicsView(scene); /* note, there is no destructor, as view will be a parent window and the resource is managed by Qt */
    view->setGeometry(x1,y1,width,height);

	if (f)
		AddFunction(f);
    this->x1 = 12;
    this->x2 = width-16;
    this->y1 = 12;
    this->y2 = height-20;
}
void Plotter::AddFunction(BaseFunction *f)
{
	fVec.push_back(f);
}


void Plotter::DrawBackground(void)
{
    view->scene()->clear();
}
void Plotter::DrawXAxis(void)
{
    QFont font("Tahoma",7.0);
    QGraphicsScene *scene = view->scene();
    scene->addLine(x1+50,y2-20,x2-10,y2-20, QPen(QColor(Qt::blue)));
    scene->addLine(x2-10,y2-20,x2-16,y2-24, QPen(QColor(Qt::blue)));
    scene->addLine(x2-10,y2-20,x2-16,y2-16, QPen(QColor(Qt::blue)));
    auto text = scene->addText(xAxis.title.c_str(), font);
    text->moveBy(x2-10, y2);
    double diffX = xAxis.end-xAxis.start;
    double deltaX = (x2-10-x1-60)/(diffX);
    for (double d = 0; d < diffX; d += xAxis.tick)
	{
        scene->addLine(x1+50+(int)(deltaX*d),y2-18,x1+50+(int)(deltaX*d),y2-22, QPen(QColor(Qt::blue)));
	}
    for (double d = 0; d <= diffX; d += xAxis.label)
	{
        scene->addLine(x1+50+(int)(deltaX*d),y2-16,x1+50+(int)(deltaX*d),y2-24, QPen(QColor(Qt::blue)));
        stringstream s;
        s << d + xAxis.start;
        auto text2 = scene->addText(s.str().c_str(), font);
        text2->moveBy(x1+50-text2->boundingRect().width()/2.0+(deltaX*d),y2-5);
    }
}
void Plotter::DrawYAxis(void)
{
    QFont font("Tahoma",7.0);
    QGraphicsScene *scene = view->scene();
    scene->addLine(x1+50,y1+20,x1+50,y2-20, QPen(QColor(Qt::blue)));
    scene->addLine(x1+46,y1+26,x1+50,y1+20, QPen(QColor(Qt::blue)));
    scene->addLine(x1+54,y1+26,x1+50,y1+20, QPen(QColor(Qt::blue)));
    auto text = scene->addText(yAxis.title.c_str(), font);
    text->moveBy(x1+10,y1+12);
    double diffY = yAxis.end-yAxis.start;
    double deltaY = (y2-10-y1-40)/(diffY);

    for (double d = 0; d < diffY; d += yAxis.tick)
	{
        scene->addLine(x1+48,y2-20-(int)(deltaY*d),x1+52,y2-20-(int)(deltaY*d),QPen(QColor(Qt::blue)));
	}
    for (double d = 0; d <= diffY; d += yAxis.label)
	{
        scene->addLine(x1+44,y2-20-(int)(deltaY*d),x1+56,y2-20-(int)(deltaY*d),QPen(QColor(Qt::blue)));
        stringstream s;
        s<<d+yAxis.start;
        auto text2 = scene->addText(s.str().c_str(), font);
        text2->moveBy(x1+45-text2->boundingRect().width(),y2-30-(int)(deltaY*d));
		
	}

}

void Plotter::Draw()
{
	double deltaX,deltaY;
    static QColor colors[4] = { { 128,0,0,255} , { 0,128,128,255} , { 0,0,128,255}, {0,128,128, 255 }};
    QGraphicsScene *scene = view->scene();
    DrawBackground();
	DrawXAxis();
    DrawYAxis();
    double diffX = xAxis.end-xAxis.start;
    double diffY = yAxis.end-yAxis.start;
    double textY = 0;
    deltaX = (x2-10-x1-60)/(diffX);
    deltaY = (y2-10-y1-40)/(diffY);
	for (unsigned int i=0;i<fVec.size();i++)
	{
		for (int x=0;x<x2-x1-60;x++)
		{
            double xd = xAxis.start+x/deltaX;
			if (fVec[i]->IsInRange(xd))
			{
				
                double yd =(fVec[i]->f(xd)-yAxis.start)*deltaY+0.5;
                if (yd > 0 && yd < y2-40)
				switch(fVec[i]->GetDisplayType())
				{
				case BaseFunction::Lines:
					{
                        double yd2=(fVec[i]->f(xd+1/deltaX)-yAxis.start)*deltaY+0.5;
						if (yd2>0 && yd2<y2-40)
						{
                            scene->addLine(x1+50+x,y2-20-yd, x1+51+x,y2-20-yd2,QPen(colors[i%4]));
							break;
						}
					} 
					break;
				case BaseFunction::Points:
                    scene->addEllipse(x1+50+x, yd+y1+30, 2, 2, QPen(colors[i%4]));
                    break;
				}
			}
		}
        QFont font("Times New Roman",10.0);
        auto elem = scene->addSimpleText(fVec[i]->GetName().c_str(), font);
        elem->setBrush(QBrush(colors[i%4]));
        elem->moveBy(x2-elem->boundingRect().width()-10,y1+textY);
        textY += elem->boundingRect().height();
	}
    view->show();
}


