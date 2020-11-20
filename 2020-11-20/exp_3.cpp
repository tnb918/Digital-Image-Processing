#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("3.jpg");
	Mat hsvMat;
	Mat detectMat;
	Mat detectMat_close;

	//缩放比例
	double scale = 0.2;
	//HSV提取红色对应参数
	double i_minH = 0;
	double i_maxH = 5;
	double i_minS = 73;
	double i_maxS = 255;
	double i_minV = 46;
	double i_maxV = 255;

	//按scale缩放图片，HSV初步提取图片红色区域
	Size ResImgSiz = Size(srcMat.cols * scale, srcMat.rows * scale);
	Mat disMat = Mat(ResImgSiz, srcMat.type());
	resize(srcMat, disMat, ResImgSiz, INTER_LINEAR);

	cvtColor(disMat, hsvMat, COLOR_BGR2HSV);

	inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);
	imshow("detectMat", detectMat);

	//构建结构元素，进行闭运算,填充缝隙，得到整体轮廓
	Mat stru = getStructuringElement(MORPH_RECT, Size(23, 23), Point(-1, -1));
	morphologyEx(detectMat, detectMat_close, MORPH_CLOSE, stru, Point(-1, -1), 1);
	imshow("detectMat_close", detectMat_close);

	//通过findContours寻找连通域
	vector<vector<Point>> contours;
	findContours(detectMat_close, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	//绘制轮廓及最小外接四边形
	for (int i = 0; i < contours.size(); i++)
	{
		RotatedRect rbox = minAreaRect(contours[i]);
		float width = (float)rbox.size.width;
		float height = (float)rbox.size.height;
		float area = width * height;
		if (area > 500)
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