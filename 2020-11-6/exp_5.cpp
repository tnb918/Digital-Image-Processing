#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	Mat srcMat = imread("1.jpg", 0);
	Mat src = imread("1.jpg");
	Mat dstMat;

	int height = srcMat.rows;//行数
	int width = srcMat.cols;//列数
	int x1 = 0, x2 = 0, y1 = 0;

	for (int i = 0; i < width; i++)
	{
		if (srcMat.at<uchar>(0, i) < 250)
		{
			x1 = i;
		}
		if (srcMat.at<uchar>(height-1, i) < 250)
		{
			x2 = i;
		}
	}

	for (int j = 0; j < height; j++)
	{
		if (srcMat.at<uchar>(j, 0) < 240)
		{
			y1 = j;
		}
	}
	
	//在图中将点画出，判断是否准确，进行微调
	circle(src, Point(x1-2, 2), 0, CV_RGB(255, 0, 0), 5, 8, 0);
	circle(src, Point(x2, height-1), 0, CV_RGB(255, 0, 0), 5, 8, 0);
	circle(src, Point(0, y1), 0, CV_RGB(255, 0, 0), 5, 8, 0);

	//变换前的三点坐标
	const Point2f src_pt[] = { Point2f(x1 - 2,2),
		Point2f(x2,height - 1),
		Point2f(0,y1) };
	//变换后的三点坐标
	const Point2f dst_pt[] = { Point2f(0,0),
		Point2f(width - 1,height - 1),
		Point2f(0,height - 1) };
	//计算仿射矩阵
	const Mat affine_matrix = getAffineTransform(src_pt, dst_pt);
	warpAffine(src, dstMat, affine_matrix, srcMat.size());

	imshow("srcMat", src);
	imshow("dstMat", dstMat);
	waitKey(0);
	return 0;
}