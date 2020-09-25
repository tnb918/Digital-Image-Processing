#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
	cv::Mat srcMat = imread("C:/Users/TNB/Desktop/1.jpg");
	cv::Mat srcMat2;
	srcMat.copyTo(srcMat2);
	int height = srcMat.rows;//行数
	int width = srcMat.cols;//列数
	uchar threshold = 100;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			uchar average = (srcMat.at<Vec3b>(j, i)[0] + srcMat.at<Vec3b>(j, i)[1] + srcMat.at<Vec3b>(j, i)[2]) / 3;
			if (average > threshold)
			{
				srcMat.at<Vec3b>(j, i)[0] = 255;
				srcMat.at<Vec3b>(j, i)[1] = 255;
				srcMat.at<Vec3b>(j, i)[2] = 255;
			}
			else
			{
				srcMat.at<Vec3b>(j, i)[0] = 0;
				srcMat.at<Vec3b>(j, i)[1] = 0;
				srcMat.at<Vec3b>(j, i)[2] = 0;
			}
			srcMat2.at<Vec3b>(j, i)[0] = average;
			srcMat2.at<Vec3b>(j, i)[1] = average;
			srcMat2.at<Vec3b>(j, i)[2] = average;
		}
	}
	imshow("1", srcMat);
	imshow("2", srcMat2);
	waitKey(0);
	return 0;
}