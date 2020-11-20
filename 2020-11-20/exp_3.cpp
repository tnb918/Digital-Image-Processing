#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("3.jpg");
	Mat disMat = imread("3.jpg");
	Mat hsvMat;
	Mat detectMat;

	double scale = 0.1;

	double i_minH = 10;
	double i_maxH = 180;
	double i_minS = 50;
	double i_maxS = 255;
	double i_minV = 46;
	double i_maxV = 255;

	Size ResImgSiz = Size(srcMat.cols * scale, srcMat.rows * scale);
	Mat rFrame = Mat(ResImgSiz, srcMat.type());
	resize(srcMat, rFrame, ResImgSiz, INTER_LINEAR);

	cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);

	rFrame.copyTo(detectMat);

	cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

	vector<vector<Point>> contours;
	findContours(detectMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	for (int i = 0; i < contours.size(); i++)
	{
		RotatedRect rbox = minAreaRect(contours[i]);
		float width = (float)rbox.size.width;
		float height = (float)rbox.size.height;
		float area = width * height;
		float ration = width / height;
		if (area > 500)
		{
			drawContours(rFrame, contours, i, Scalar(0, 255, 255), 1, 8);
			Point2f vtx[4];
			rbox.points(vtx);
			for (int i = 0; i < 4; ++i)
			{
				line(rFrame, vtx[i], vtx[i < 3 ? i + 1 : 0], Scalar(0, 0, 255), 2, CV_AA);
			}
		}
	}
	imshow("whie:in the range", detectMat);
	imshow("rFrame", rFrame);

	waitKey(0);
	return 0;
}