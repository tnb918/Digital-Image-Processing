#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	Mat image1;
	Mat image2;
	Mat image3;
	cv::Mat srcMat = imread("C:/Users/TNB/Desktop/Lena.jpg", 0);

	threshold(srcMat, image1, 100, 255, THRESH_BINARY);
	threshold(srcMat, image2, 100, 255, THRESH_OTSU);
	adaptiveThreshold(srcMat, image3, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 15, 10);

	imshow("SRC", srcMat);
	imshow("THRESH_BINARY", image1);
	imshow("THRESH_OTSU", image2);
	imshow("ADAPTIVE", image3);
	waitKey(0);
	return 0;
}