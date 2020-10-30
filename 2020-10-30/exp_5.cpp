#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{

	VideoCapture cap(0);

	double scale = 0.5;
	//肤色
	double i_minH = 0;
	double i_maxH = 20;
	//0-255
	double i_minS = 43;
	double i_maxS = 255;
	//0-255
	double i_minV = 55;
	double i_maxV = 255;

	while (1)
	{
		Mat frame;
		Mat hsvMat;
		Mat outFrame;
		Mat mask;
		Mat detectMat;

		cap >> frame;
		Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);
		rFrame.copyTo(detectMat);

		//根据肤色提取掩膜
		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);
		inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), mask);

		//通过高斯滤波实现磨皮
		GaussianBlur(rFrame, outFrame, Size(39, 39), 1, 0, BORDER_DEFAULT);

		//当mask值不为0时，原图像拷贝到目标图像，当mask值为0时，目标图像保持不变
		outFrame.copyTo(detectMat,mask);

		imshow("原图", rFrame);
		imshow("掩膜", mask);
		imshow("整体磨皮", outFrame);
		imshow("人脸磨皮", detectMat);
		waitKey(30);
	}
}
