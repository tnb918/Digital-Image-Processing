#include <opencv2/opencv.hpp> 
#include<iostream>
using namespace cv;

int main() 
{
	VideoCapture cap;
	cap.open(0);
	Mat frame;
	Mat bgMat;
	Mat subMat;
	Mat bny_subMat;
	int cnt = 0;

	while (1)
	{
		cap >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		if (cnt == 0)
		{
			//第一帧，获得背景图像
			frame.copyTo(bgMat);
			cnt++;
		}
		else
		{
			//从第二帧开始背景差分
			//背景图形和当前 图像相减
			absdiff(frame, bgMat, subMat);
			//差分结果二值化
			threshold(subMat, bny_subMat, 50, 255, CV_THRESH_BINARY);

			imshow("b_subMat", bny_subMat);
			imshow("subMat", subMat);
			waitKey(30);
		}
	}
	return 0;
}