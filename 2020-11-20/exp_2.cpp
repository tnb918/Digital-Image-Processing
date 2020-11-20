#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("2.jpg", 0);
	Mat disMat = imread("2.jpg");
	Mat binary;
	Mat binary_open;

	threshold(srcMat, binary, 100, 255, THRESH_OTSU);
	imshow("binary", binary);

	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	cv::morphologyEx(binary, binary_open, MORPH_OPEN, element, Point(-1, -1), 1);
	cv::imshow("binary_open", binary_open);

	vector<vector<Point>> contours;
	findContours(binary_open, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	for (int i = 0; i < contours.size(); i++)
	{
		RotatedRect rbox = minAreaRect(contours[i]);
		float width = (float)rbox.size.width;
		float height = (float)rbox.size.height;
		float area = width * height;
		float ration = width / height;
		if (area>500)
		{
			drawContours(disMat, contours, i, Scalar(0, 255, 255), 1, 8);
			Point2f vtx[4];
			rbox.points(vtx);
			for (int i = 0; i < 4; ++i)
			{
				line(disMat, vtx[i], vtx[i < 3 ? i + 1 : 0], Scalar(0, 0, 255), 2, CV_AA);
			}
		}
	}
	imshow("disMat", disMat);
	waitKey();
	return 0;
}