#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("1.jpg", 0);
	Mat disMat = imread("1.jpg");
	Mat binary;
	Mat binary_not;

	//二值化并反色变换
	threshold(srcMat, binary, 100, 255, THRESH_OTSU);
	bitwise_not(binary, binary_not);
	imshow("binary", binary);
	imshow("binary_not", binary_not);

	//通过findContours寻找连通域
	vector<vector<Point>> contours;
	findContours(binary_not, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	//绘制轮廓及最小外接四边形
	for (int i = 0; i < contours.size(); i++)
	{
		RotatedRect rbox = minAreaRect(contours[i]);
		float width = (float)rbox.size.width;
		float height = (float)rbox.size.height;
		float area = width * height;
		float ration = width / height;
		if (ration > 0.9 && area > 500)
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
	waitKey(0);
	return 0;
}