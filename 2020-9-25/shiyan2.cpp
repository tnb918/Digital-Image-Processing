#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
	cv::Mat srcMat = imread("C:/Users/TNB/Desktop/1.jpg",0);
	imshow("1", srcMat);
	waitKey(0);
	return 0;
}