#include<opencv2/opencv.hpp>
using namespace cv;

int main()
{
	Mat srcMat = imread("1.jpg", 0);
	Mat dstMat;
	srcMat.copyTo(dstMat);

	float Lut[256]{ 0 };	
	float gamma = 0.5;
	float temp;

	//建立查询表数组
	for (int i = 0; i < 256; i++)
	{
		temp = (float)i / 255;
		temp = pow(temp, gamma);
		Lut[i] = temp * 255;
	}

	//遍历Mat
	int height = srcMat.rows;
	int width = srcMat.cols;
	for (int m = 0; m < height; m++)
	{
		for (int n = 0; n < width; n++)
		{
			dstMat.at<uchar>(m, n) = Lut[srcMat.at<uchar>(m, n)];
		}
	}

	imshow("原图", srcMat);
	imshow("gamma变换后", dstMat);
	waitKey(0);
	return 0;
}