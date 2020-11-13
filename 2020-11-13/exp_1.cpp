#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

int main()
{
	Mat srcMat = imread("Lena.jpg");
	Mat dstMat;
	if (srcMat.empty()) return -1;

	//旋转角度，缩放比例
	float angle = -10.0, scale = 1;
	//旋转中心为图像中心
	Point2f center(srcMat.cols * 0.5, srcMat.rows * 0.5);		
	//获得变换矩阵
	Mat affine_matrix = getRotationMatrix2D(center, angle, scale);
	//获取外界四边形
	Rect bbox = RotatedRect(center, srcMat.size(), angle).boundingRect();
	//调整仿射矩阵参数
	affine_matrix.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	affine_matrix.at<double>(1, 2) += bbox.height / 2.0 - center.y;
	//仿射变换
	warpAffine(srcMat, dstMat, affine_matrix, bbox.size());

	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
}