#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
int main()
{
	cv::Mat dispMat;
	dispMat.create(Size(500, 500), CV_8UC3);

	cv::Point pt1;
	pt1.x = 100;
	pt1.y = 100;
	cv::Point pt2;
	pt2.x = 200;
	pt2.y = 200;
	cv::Rect rect;
	rect.x = 100;
	rect.y = 100;
	rect.width=100;
	rect.height=100;
	
	circle(dispMat, pt1, 50, CV_RGB(255, 0, 0), 1, 8, 0);
	line(dispMat, pt1, pt2, CV_RGB(255, 0, 0), 1, 8, 0);
	rectangle(dispMat, rect, CV_RGB(255, 0, 0), 1, 8, 0);

	cv::imshow("1", dispMat);
	waitKey(0);
	return 0;
}