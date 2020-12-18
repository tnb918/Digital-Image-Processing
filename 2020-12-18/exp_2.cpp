#include <opencv2/opencv.hpp> 
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;
	cap.open(0);
	Mat frame;			//����ͷ�ɼ���ǰ֡
	Mat meanMat;		//��Ÿ����ؾ�ֵ
	Mat varMat;			//��Ÿ����ط���
	vector<Mat> all;	//���ǰn֡ͼ��
	int nframe = 20;	//Ԥ�ȶ�ȡ��֡��
	int cnt = 0;		//����
	int TH = 2;			//����Ȩ��

	while (1)
	{
		cap >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		int height = frame.rows;
		int width = frame.cols;

		if (cnt < nframe)
		{
			//����ǰn֡ͼ��
			all.push_back(frame);
			meanMat.create(frame.size(), CV_8UC1);
			varMat.create(frame.size(), CV_32FC1);
			
			cout << "Successfully loaded frame of "<<cnt << endl;
		}
		else if (cnt == nframe)
		{
			//�����ֵ�ͷ��ʵ�ָ�˹��ģ
			cout << "Calculate the mean and variance......" << endl;
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					int mean = 0;
					float var = 0;
					for (int k = 0; k < nframe; k++)
					{
						mean += all[k].at<uchar>(i, j);//�����ֵ
					}
					meanMat.at<uchar>(i, j) = mean / nframe;
					for (int k = 0; k < nframe; k++)
					{
						var += pow((all[k].at<uchar>(i, j) - meanMat.at<uchar>(i, j)), 2);//���㷽��
					}
					varMat.at<float>(i, j) = var / nframe;
				}
			}
			cout << "The mean and variance have been calculated successfully" << endl;
		}
		else
		{
			//ʵ�ֱ������
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