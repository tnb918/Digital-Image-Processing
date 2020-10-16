#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std; 

int main()
{
	Mat srcMat = imread("pcb.jpg", 0);
	Mat binary;
	Mat stru;
	Mat open;
	Mat labels;
	Mat stats;
	Mat centroids;
	int num;
	threshold(srcMat, binary, 100, 255, THRESH_OTSU);

	int height = binary.rows;//行数
	int width = binary.cols;//列数
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (binary.at<uchar>(j, i) == 0)
				binary.at<uchar>(j, i) = 255;
			else
				binary.at<uchar>(j, i) = 0;
		}
	}

	stru = getStructuringElement(MORPH_RECT, Size(20, 20), Point(-1, -1));
	morphologyEx(binary, open, 2, stru, Point(-1, -1), 1);

	num = connectedComponentsWithStats(open, labels, stats, centroids, 8, CV_32S);
	imshow("open",open);
	cout << "焊点的数量为" << num - 1 << endl;
	waitKey(0);
	return 0;
}