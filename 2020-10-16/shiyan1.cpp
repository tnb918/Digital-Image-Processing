#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

int main()
{
	Mat srcMat = imread("coin.jpg",0);
	Mat binary;
	Mat erode;
	Mat dilate;
	Mat open;
	Mat close;
	Mat stru;

	stru = getStructuringElement(MORPH_RECT,Size(3,3), Point(-1, -1));
	threshold(srcMat, binary, 100, 255, THRESH_BINARY);
	morphologyEx(binary, erode, 0, stru, Point(-1, -1), 1);
	morphologyEx(binary, dilate, 1, stru, Point(-1, -1), 1);
	morphologyEx(binary, open, 2, stru, Point(-1, -1), 1);
	morphologyEx(binary, close, 3, stru, Point(-1, -1), 1);

	imshow("src",srcMat);
	imshow("binary",binary);
	imshow("erode", erode);
	imshow("dilate", dilate);
	imshow("open", open);
	imshow("close", close);
	waitKey(0);
	return 0;
}