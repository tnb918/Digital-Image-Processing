#include <iostream>
#include <opencv2/opencv.hpp>
#include<math.h>
using namespace cv;
using namespace std;

//函数声明
int calcHOG(Mat srcMat, float* hist, int nAngle, int cellSize);
float normL2(float* hist1, float* hist2, int num);

int main()
{
	Mat refMat = imread("hogTemplate.jpg", 0);
	Mat plMat = imread("img1.jpg", 0);
	Mat bgMat = imread("img2.jpg", 0);

	int cellSize = 16;
	int nAngle = 8;
	int nX = refMat.cols / cellSize;
	int nY = refMat.rows / cellSize;
	int bins = nX * nY * nAngle;

	//动态建立数组，开辟内存
	float* ref_hist = new float[bins];
	memset(ref_hist, 0, sizeof(float) * bins);
	float* pl_hist = new float[bins];
	memset(pl_hist, 0, sizeof(float) * bins);
	float* bg_hist = new float[bins];
	memset(bg_hist, 0, sizeof(float) * bins);

	int reCode = 0;
	//计算三张输入图片的HOG
	reCode = calcHOG(refMat, ref_hist, nAngle, cellSize);
	reCode = calcHOG(plMat, pl_hist, nAngle, cellSize);
	reCode = calcHOG(bgMat, bg_hist, nAngle, cellSize);

	if (reCode != 0)
	{
		delete[] ref_hist;
		delete[] pl_hist;
		delete[] bg_hist;
		return -1;
	}

	//计算直方图距离
	float dis1 = normL2(ref_hist, pl_hist, bins);
	float dis2 = normL2(ref_hist, bg_hist, bins);

	cout << "hogTemplate和img1的欧几里得距离为：" << dis1 << endl;
	cout << "hogTemplate和img2的欧几里得距离为：" << dis2 << endl;
	if (dis1 <= dis2)
	{
		cout << "img1与hogTemplate更相似" << endl;
	}
	else
	{		
		cout << "img2与hogTemplate更相似" << endl;
	}

	//手动释放内存
	delete[] ref_hist;
	delete[] pl_hist;
	delete[] bg_hist;
	return 0;
}

int calcHOG(Mat srcMat, float* hist, int nAngle, int cellSize)
{
	int nX = srcMat.cols / cellSize;
	int nY = srcMat.rows / cellSize;

	//计算梯度及角度
	Mat gx, gy;
	Mat mag, angle;
	Sobel(srcMat, gx, CV_32F, 1, 0, 1);
	Sobel(srcMat, gy, CV_32F, 0, 1, 1);

	//笛卡尔坐标转极坐标
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

			//赋值图像
			roiMat = srcMat(roi);
			roiMag = mag(roi);
			roiAgl = angle(roi);
			//当前cell第一个元素在数组中的位置
			int head = (i * nX + j) * nAngle;

			for (int n = 0; n < roiMat.rows; n++)
			{
				for (int m = 0; m < roiMat.cols; m++)
				{
					//计算角度在哪个bin，通过int自动取整实现
					int cellnum = (int)(roiAgl.at<float>(n, m) / (360 / nAngle));
					//以像素点的值为权重
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