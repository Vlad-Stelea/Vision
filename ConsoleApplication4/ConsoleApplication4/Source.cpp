#include <iostream>
#include "opencv2\core.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\features2d.hpp"
#include <vector>
#include "opencv2\objdetect.hpp"
cv::Mat pic;
using namespace std;
//trackbar values
int lowThreshH;
int lowThreshS;
int lowThreshV;
int highThreshH = 255;
int highThreshS = 255;
int highThreshV = 255;
//
void createThreshold();
cv::Size kern(3,3);
using namespace cv;
void on_Slider(int, void* v) {
	createThreshold();
	std::cout << "LOW V = " << lowThreshV << std::endl;
	std::cout << "High V = " << highThreshV << std::endl;
}
void createSliders() {
	namedWindow("Sliders", WINDOW_NORMAL);
	createTrackbar("LowH", "Sliders", &lowThreshH, 255, on_Slider);
	createTrackbar("LowS", "Sliders", &lowThreshS, 255, on_Slider);
	createTrackbar("LowV", "Sliders", &lowThreshV, 255, on_Slider);
	createTrackbar("HighH", "Sliders", &highThreshH, 255, on_Slider);
	createTrackbar("HighS", "Sliders", &highThreshS, 255, on_Slider);
	createTrackbar("HighV", "Sliders", &highThreshV, 255, on_Slider);
}
double findSlope(Point p1,Point p2) {
	return ((double)p1.y - (double)p2.y) / ((double)p1.x - (double)p2.x);
}
void morph(Mat m) {
	
	erode(m, m, Mat());
	blur(m,m,Size(3,3));
		}
void drawRect(RotatedRect r) {

	Point2f vertices[4];
	r.points(vertices);
	for (int i = 0; i < 4; i++)
		line(pic, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0));
	cout << "Slope "<<findSlope(vertices[0],vertices[1]) << endl;
}
void createThreshold() {
	std::vector<std::vector<Point> > contours;
	std::vector<std::vector<Point>> contours2;
	std::vector<Vec4i> hierarchy;
	Mat thresh;
	blur(pic , thresh, Size(3, 3));
	cvtColor(thresh, thresh, CV_BGR2HSV);
	inRange(thresh,Scalar(47,169,136),Scalar(94,255,169),thresh);
	dilate(thresh,thresh,Mat());
	boundingRect(thresh);
	findContours(thresh,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE,Point(0,0));
	contours2.push_back(contours.at(5));
	drawContours(pic,contours2,-1,Scalar(0,100,100),3,8);
	RotatedRect r =  minAreaRect(contours2[0]);
	drawRect(r);
	cout << "Match shapes " << matchShapes(contours[5],contours[17],CV_CONTOURS_MATCH_I2,0) << endl;
	//std::vector<Rect> boundRect(contours.size());
	imshow("win", thresh);
	imshow("normal",pic);
	//waitKey(0);
}
int main(int argc, char* argv[])
{
	using namespace cv;
	createSliders();
	namedWindow("win", WINDOW_NORMAL);
	namedWindow("normal",WINDOW_NORMAL);
	pic = imread("display.png", CV_LOAD_IMAGE_COLOR);
	createThreshold();
	waitKey(0);
	return 0;
}
