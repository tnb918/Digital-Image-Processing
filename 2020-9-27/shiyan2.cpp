#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
int main()
{
	VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened())
	{
		std::cout << "���ܴ���Ƶ�ļ�" << std::endl;
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps" << fps << std::endl;
	while (1)
	{
		cv::Mat frame;
		bool rSuccess = cap.read(frame);
		if (!rSuccess)
		{
			std::cout << "���ܴ���Ƶ�ж�ȡ֡" << std::endl;
		}
		else
		{
			cv::imshow("frame", frame);
		}
		waitKey(30);
	}
	return 0;
}