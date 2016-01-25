#pragma once
#include "opencv2\core.hpp"
using namespace cv;
class Zones
{
public:
	Zones(Mat pic);
	void setUpZones();
	int getZone(Scalar s1,Scalar toTrack);
	//~Zones();

private:

	Mat pict;
	void quad1();
	void quad2();
	void quad3();
	void quad4();
	void center();
};

