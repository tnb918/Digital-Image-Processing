#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("1.jpg");
	Mat srcgray = imread("1.jpg", 0);
	Mat canny;
	Mat dstMat;
	vector<Vec4i> lines;

	Canny(srcgray, canny, 100, 200, 3, false);
	HoughLinesP(canny, lines, 1, CV_PI / 180, 50, 10, 10);

	vector<Vec4i>::iterator it = lines.begin();
	for (; it != lines.end(); ++it)
	{
		Point pt1, pt2;
		pt1.x = (*it)[0];
		pt1.y = (*it)[1];
		pt2.x = (*it)[2];
		pt2.y = (*it)[3];
		line(srcMat, pt1, pt2, Scalar(0, 255, 255), 2, CV_AA);
	}

	imshow("canny", canny);
	imshow("srcMat_line", srcMat);
	waitKey(0);
}