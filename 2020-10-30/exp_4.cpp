#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0);
	double scale = 0.5;
	while (1)
	{
		Mat frame;
		Mat xoutFrame;
		Mat youtFrame;

		cap >> frame;
		Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

		Sobel(rFrame, xoutFrame, CV_8UC1, 1, 0, 3);
		Sobel(rFrame, youtFrame, CV_8UC1, 0, 1, 3);

		imshow("original", rFrame);
		imshow("X_Sobel", xoutFrame);
		imshow("Y_Sobel", youtFrame);
		waitKey(30);
	}
}