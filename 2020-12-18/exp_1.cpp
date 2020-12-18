#include <opencv2/opencv.hpp> 
#include<iostream>
using namespace cv;

int main() 
{
	VideoCapture cap;
	cap.open(0);
	Mat frame;
	Mat bgMat;
	Mat subMat;
	Mat bny_subMat;
	int cnt = 0;

	while (1)
	{
		cap >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		if (cnt == 0)
		{
			//��һ֡����ñ���ͼ��
			frame.copyTo(bgMat);
			cnt++;
		}
		else
		{
			//�ӵڶ�֡��ʼ�������
			//����ͼ�κ͵�ǰ ͼ�����
			absdiff(frame, bgMat, subMat);
			//��ֽ����ֵ��
			threshold(subMat, bny_subMat, 50, 255, CV_THRESH_BINARY);

			imshow("b_subMat", bny_subMat);
			imshow("subMat", subMat);
			waitKey(30);
		}
	}
	return 0;
}