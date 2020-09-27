#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
int main()
{
	cv::Mat srcMat = imread("C:\\Users\\TNB\Desktop\\Lena.jpg",0);
	int height = srcMat.rows;
	int width = srcMat.cols;
	float histgram[256] { 0 };
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			histgram[srcMat.at<uchar>(j, i)]++;
		}
	}
	system("pause");
	return 0;
}