#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
	cv::Mat srcMat = imread("C:/Users/TNB/Desktop/1.jpg");
	int height = srcMat.rows;//行数
	int width = srcMat.cols;//列数
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			uchar average = (srcMat.at<Vec3b>(j, i)[0] + srcMat.at<Vec3b>(j, i)[1] + srcMat.at<Vec3b>(j, i)[2])/3;
			srcMat.at<Vec3b>(j, i)[0] = average;
			srcMat.at<Vec3b>(j, i)[1] = average;
			srcMat.at<Vec3b>(j, i)[2] = average;
		}
	}
	imshow("1",srcMat );
	waitKey(0);
	return 0;
}