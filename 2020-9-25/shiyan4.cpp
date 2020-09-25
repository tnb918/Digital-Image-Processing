#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
	cv::Mat srcM = imread("C:/Users/TNB/Desktop/1.jpg");
	cv::Mat deepMat;
	cv::Mat shallowMat;
	shallowMat = srcM;
	srcM.copyTo(deepMat);
	int height = srcM.rows;//����
	int width = srcM.cols;//����
	uchar threshold = 100;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			uchar average = (srcM.at<Vec3b>(j, i)[0] + srcM.at<Vec3b>(j, i)[1] + srcM.at<Vec3b>(j, i)[2]) / 3;
			if (average > threshold)
			{
				srcM.at<Vec3b>(j, i)[0] = 255;
				srcM.at<Vec3b>(j, i)[1] = 255;
				srcM.at<Vec3b>(j, i)[2] = 255;
			}
			else
			{
				srcM.at<Vec3b>(j, i)[0] = 0;
				srcM.at<Vec3b>(j, i)[1] = 0;
				srcM.at<Vec3b>(j, i)[2] = 0;
			}
		}
	}
	imshow("ԭͼ", srcM);
	imshow("���", deepMat);
	imshow("ǳ����", shallowMat);
	waitKey(0);
	return 0;
}