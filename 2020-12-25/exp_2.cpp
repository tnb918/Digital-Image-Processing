#include <opencv2/opencv.hpp>
#include<math.h>
using namespace cv;
using namespace std;

//��������
int calcHOG(Mat srcMat, float* hist, int nAngle, int cellSize);
float normL2(float* hist1, float* hist2, int num);

int main()
{
	Mat srcMat = imread("src.jpg", 0);
	Mat refMat = imread("ref.jpg", 0);
	Mat objMat;
	int cellSize = 16;
	int nAngle = 8;
	int nX = refMat.cols / cellSize;
	int nY = refMat.rows / cellSize;
	int bins = nX * nY * nAngle;
	float dis0, dis1;

	//��̬�������飬�����ڴ�
	float* ref_hist = new float[bins];
	memset(ref_hist, 0, sizeof(float) * bins);
	//��ѭ���������̶�ģ���HOG���ӿ������ٶ�
	int reCode = 0;
	reCode = calcHOG(refMat, ref_hist, nAngle, cellSize);
	if (reCode != 0)
	{
		delete[] ref_hist;
		return -1;
	}

	Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.width = refMat.cols;
	rect.height = refMat.rows;

	for (int i = 0; i < srcMat.rows - refMat.rows + 1; i++)
	{
		for (int j = 0; j < srcMat.cols - refMat.cols + 1; j++)
		{
			float* obj_hist = new float[bins];
			memset(obj_hist, 0, sizeof(float) * bins);
			
			Rect2d r = Rect(j, i, refMat.cols, refMat.rows);
			objMat = srcMat(r);

			reCode = calcHOG(objMat, obj_hist, nAngle, cellSize);
			dis1 = normL2(ref_hist, obj_hist, bins);
			if (i == 0 && j == 0)
			{
				dis0 = dis1;
			}
			else
			{
				if (dis1 < dis0)
				{
					rect.x = j;
					rect.y = i;
					dis0 = dis1;
				}
			}
			delete[] obj_hist;
		}
	}
	delete[] ref_hist;

	//���ƾ��ο�
	rectangle(srcMat, rect, CV_RGB(255, 0, 0), 2, 8, 0);
	imshow("ģ��", refMat);
	imshow("Ŀ������׷��",srcMat);
	waitKey(0);

	return 0;
}

int calcHOG(Mat srcMat, float* hist, int nAngle, int cellSize)
{
	int nX = srcMat.cols / cellSize;
	int nY = srcMat.rows / cellSize;

	//�����ݶȼ��Ƕ�
	Mat gx, gy;
	Mat mag, angle;
	Sobel(srcMat, gx, CV_32F, 1, 0, 1);
	Sobel(srcMat, gy, CV_32F, 0, 1, 1);

	//�ѿ�������ת������
	cartToPolar(gx, gy, mag, angle, true);

	for (int i = 0; i < nY; i++)
	{
		for (int j = 0; j < nX; j++)
		{
			Mat roiMat;
			Mat roiMag;
			Mat roiAgl;
			Rect roi;
			roi.x = j * cellSize;
			roi.y = i * cellSize;
			roi.width = cellSize;
			roi.height = cellSize;

			//��ֵͼ��
			roiMat = srcMat(roi);
			roiMag = mag(roi);
			roiAgl = angle(roi);
			//��ǰcell��һ��Ԫ���������е�λ��
			int head = (i * nX + j) * nAngle;

			for (int n = 0; n < roiMat.rows; n++)
			{
				for (int m = 0; m < roiMat.cols; m++)
				{
					//����Ƕ����ĸ�bin��ͨ��int�Զ�ȡ��ʵ��
					int cellnum = (int)(roiAgl.at<float>(n, m) / (360 / nAngle));
					//�����ص��ֵΪȨ��
					hist[head + cellnum] += roiMag.at<float>(n, m);
				}
			}
		}
	}
	return 0;
}

float normL2(float* hist1, float* hist2, int num)
{
	float result = 0;
	for (int i = 0; i < num; i++)
	{
		result += pow(hist1[i] - hist2[i], 2);
	}
	result = sqrt(result);
	return result;
}