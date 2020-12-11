#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;

String window_name = "gammaMat";

void gamma(int num, void* data)
{
	Mat src = *(Mat*)(data);
	Mat dst;
	src.copyTo(dst);

	float Lut[256]{ 0 };
	float temp;
	float gamma = (float)num / 100;

	//建立查询表数组
	for (int i = 0; i < 256; i++)
	{
		temp = (float)i / 255;
		temp = pow(temp, gamma);
		Lut[i] = temp * 255;
	}

	//遍历Mat
	int height = src.rows;
	int width = src.cols;
	for (int m = 0; m < height; m++)
	{
		for (int n = 0; n < width; n++)
		{
			dst.at<Vec3b>(m, n)[0] = Lut[src.at<Vec3b>(m, n)[0]];
			dst.at<Vec3b>(m, n)[1] = Lut[src.at<Vec3b>(m, n)[1]];
			dst.at<Vec3b>(m, n)[2] = Lut[src.at<Vec3b>(m, n)[2]];
		}
	}
	imshow(window_name, dst);
}

int main()
{
	Mat srcMat = imread("2.jpg");
	int lowGamma = 0;
	int maxGamma = 100;
	imshow(window_name, srcMat);
	createTrackbar("gamma*100", window_name, &lowGamma, maxGamma, gamma, &srcMat);
	//gamma值为0.35时大致可以识别文字内容
	waitKey(0);
	return 0;
}