#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("coin.jpg", 0);
	Mat binary;
	Mat labels;
	Mat stats;
	Mat centroids;
	int num;

	threshold(srcMat, binary, 100, 255, THRESH_BINARY);
	num = connectedComponentsWithStats(binary, labels, stats, centroids, 8, CV_32S);

	for (int i = 1; i < num; i++)
	{
		Rect rect;
		rect.x = stats.at<int>(i, 0);
		rect.y = stats.at<int>(i, 1);
		rect.width = stats.at<int>(i, 2);
		rect.height = stats.at<int>(i, 3);
		rectangle(srcMat, rect, CV_RGB(0, 0, 0), 1, 8, 0);
	}

	imshow("pic_rec", srcMat);
	cout << "硬币的数量为" << num - 1 << endl;
	waitKey(0);
	return 0;
}