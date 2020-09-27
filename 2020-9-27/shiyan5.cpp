#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;

//返回数组中的最大值
float arrayMax(float arr[], int len)
{
	float arrmax = 0;
	for (int i = 0; i < len; i++)
	{
		if (arr[i] > arrmax)
			arrmax = arr[i];
	}
	return arrmax;
}

int main()
{
	cv::Mat srcMat = imread("Lena.jpg", 0);
	int height = srcMat.rows;
	int width = srcMat.cols;
	int num = height * width;
	float histgram[256] = { 0 };
	//遍历像素,结果存入数组
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			histgram[srcMat.at<uchar>(j, i)]++;
		}
	}

	//进行归一化操作
	for (int i = 0; i < 256; i++)
	{
		histgram[i] = histgram[i] / num;
	}

	//对y按比例进行缩放，方便图形显示
	float max = arrayMax(histgram, 256);
	float yscaleRate = 256 / max; 
	float xscaleRate = 1;
	for (int i = 0; i < 256; i++)
	{
		histgram[i] = histgram[i] * yscaleRate;
	}

	//创建空白Mat,通过画线绘制直方图
	cv::Mat dispMat;
	dispMat.create(Size(256,256), CV_8UC1);
	cv::Point pt1;
	pt1.x = 0;
	pt1.y = 256-histgram[0];
	cv::Point pt2;
	pt2.x = 0;
	pt2.y = 256;
	for (int i = 0; i < 256; i++)
	{
		line(dispMat, pt1, pt2, CV_RGB(255, 0, 0), 1, 8, 0);
		pt1.x += xscaleRate;
		pt2.x = pt1.x;
		pt1.y = 256 - histgram[i];
	}
	namedWindow("灰度直方图", WINDOW_NORMAL);
	cv::imshow("灰度直方图",dispMat);
	waitKey(0);
	return 0;
}