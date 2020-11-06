#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	Mat dstMat;
	Mat srcMat = imread("lena.jpg", 1);
	if (srcMat.empty()) return -1;

	//变换前的四点坐标
	const Point2f pts1[] = {
		Point2f(150,150),
		Point2f(150,300),
		Point2f(350,300),
		Point2f(350,150) };
	//变换后的四点坐标
	const Point2f pts2[] = {
		Point2f(200,150),
		Point2f(200,300),
		Point2f(340,270),
		Point2f(340,180) };

	Mat perspective_matrix = getPerspectiveTransform(pts1, pts2);
	warpPerspective(srcMat, dstMat, perspective_matrix, srcMat.size());

	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
}