#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
int main()
{
	cv::Mat srcMat = imread("Lena.jpg",0);
	int height = srcMat.rows;
	int width = srcMat.cols;
	int num = height * width;
	float histgram[256] { 0 };
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			histgram[srcMat.at<uchar>(j, i)]++;
		}
	}
	for (int i = 0; i < 256; i++)
	{
		histgram[i] = histgram[i] / num;
		std::cout << histgram[i] << " ";
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}