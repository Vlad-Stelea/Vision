#include "zones.h"
#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\shape.hpp"
#include "opencv2\imgproc.hpp"
#include <iostream>

#define	colLim =10;
using namespace cv;

int width;
int height;

Zones::Zones(Mat pic) {
	Size s = pic.size();
	width = s.width;
	height = s.height;
	pict = pic;
	
}
Rect r1;
Rect r2;
Rect r3;
Rect r4;
Rect c;
void Zones::quad1() {
	Scalar s(0, 255, 255);
	r1 = Rect(width / 2, 0, width - 1, height / 2);
	rectangle(pict, r1, s, 1, LINE_8, 0);
}
void Zones::quad2() {
	Scalar s(255,255,255);
	r2 = Rect(0, 0, width / 2, height / 2);
	rectangle (pict,r2,s,1,LINE_8,0);
}
void Zones::quad3() {
	Scalar s(255, 0, 255);
	r3 = Rect(0, height / 2, width / 2, height);
	rectangle(pict, r3, s, 1, LINE_8, 0);
}
void Zones::quad4() {
	Scalar s(255, 255, 0);
	r4 = Rect(width / 2, height / 2, width, height);
	rectangle(pict, r4, s, 1, LINE_8, 0);
}
void Zones::center() {
	Scalar s(0, 0, 255);
	c = Rect((width / 2) - 100, (height / 2) - 50, 200, 100);
	rectangle(pict, c, s, 1, LINE_8, 0);
}

void Zones::setUpZones() {
	quad2();
	quad1();
	quad3();
	quad4();
	center();
}

int Zones::getZone(Scalar s,Scalar s1)
{

	cvtColor(pict,pict,CV_BGR2HSV);
	inRange(pict,s,s1,pict);
	return 0;
}
