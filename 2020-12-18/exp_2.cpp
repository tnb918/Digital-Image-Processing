#include <opencv2/opencv.hpp> 
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;
	cap.open(0);
	Mat frame;			//摄像头采集当前帧
	Mat meanMat;		//存放各像素均值
	Mat varMat;			//存放各像素方差
	vector<Mat> all;	//存放前n帧图像
	int nframe = 20;	//预先读取的帧数
	int cnt = 0;		//计数
	int TH = 2;			//方差权重

	while (1)
	{
		cap >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		int height = frame.rows;
		int width = frame.cols;

		if (cnt < nframe)
		{
			//加载前n帧图像
			all.push_back(frame);
			meanMat.create(frame.size(), CV_8UC1);
			varMat.create(frame.size(), CV_32FC1);
			
			cout << "Successfully loaded frame of "<<cnt << endl;
		}
		else if (cnt == nframe)
		{
			//计算均值和方差，实现高斯建模
			cout << "Calculate the mean and variance......" << endl;
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					int mean = 0;
					float var = 0;
					for (int k = 0; k < nframe; k++)
					{
						mean += all[k].at<uchar>(i, j);//计算均值
					}
					meanMat.at<uchar>(i, j) = mean / nframe;
					for (int k = 0; k < nframe; k++)
					{
						var += pow((all[k].at<uchar>(i, j) - meanMat.at<uchar>(i, j)), 2);//计算方差
					}
					varMat.at<float>(i, j) = var / nframe;
				}
			}
			cout << "The mean and variance have been calculated successfully" << endl;
		}
		else
		{
			//实现背景差分
			Mat result;
			frame.copyTo(result);
			for (int m = 0; m < height; m++)
			{
				for (int n = 0; n < width; n++)
				{
					if (abs(frame.at<uchar>(m, n) - meanMat.at<uchar>(m, n)) > TH * varMat.at<float>(m, n))
					{
						result.at<uchar>(m, n) = 255;
					}
					else 
					{
						result.at<uchar>(m, n) = 0;
					}
				}
			}
			imshow("frame", frame);
			imshow("result", result);
			waitKey(30);
		}
		cnt++;
	}
}