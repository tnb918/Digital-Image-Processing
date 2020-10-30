#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{

	VideoCapture cap(0);

	double scale = 0.5;
	//��ɫ
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

		//���ݷ�ɫ��ȡ��Ĥ
		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);
		inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), mask);

		//ͨ����˹�˲�ʵ��ĥƤ
		GaussianBlur(rFrame, outFrame, Size(39, 39), 1, 0, BORDER_DEFAULT);

		//��maskֵ��Ϊ0ʱ��ԭͼ�񿽱���Ŀ��ͼ�񣬵�maskֵΪ0ʱ��Ŀ��ͼ�񱣳ֲ���
		outFrame.copyTo(detectMat,mask);

		imshow("ԭͼ", rFrame);
		imshow("��Ĥ", mask);
		imshow("����ĥƤ", outFrame);
		imshow("����ĥƤ", detectMat);
		waitKey(30);
	}
}
