#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	Mat dstMat;
	Mat srcMat = imread("lena.jpg");
	if (srcMat.empty()) return -1;

	//旋转角度，缩放比例
	float angle = -10.0, scale = 1;
	//旋转中心为图像中心
	Point2f center(srcMat.cols * 0.5, srcMat.rows * 0.5);
	//获得变换矩阵
	const Mat affine_matrix = getRotationMatrix2D(center, angle, scale);

	warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
}