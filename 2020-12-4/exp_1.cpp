#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "funtions.h"
using namespace cv;

int main()
{
	//把图像转换为可视的傅里叶变换图像
	//dftDemo();
	//鼠标点击提取图像ROI实例程序
	//mouseROI();

	/*******************************************
	1.输入一张图片，计算其可视化的幅值谱
	2.再幅值谱图上，通过鼠标选择需要去除的频率
	3.去除被选择的信号，然后复原图像
	**********************************************/
	Mat srcMat = imread("Lena.jpg",0);
	Mat magMat, ph, dstMat;
	Mat mask1, mask2;
	double normVal;

	calcVisbalDft(srcMat, magMat, ph, normVal);//计算傅里叶变换可视化的幅值谱
	selectPolygon(magMat, mask1, mask2);//鼠标选择处理的频率，产生对应mask
	magMat = magMat.mul(mask1);//删除原频谱图中的选中频率
	calcDft2Image(magMat, ph, normVal, dstMat);//傅里叶逆变换，恢复处理后的图像

	imshow("处理后频谱.jpg", magMat);
	imshow("原图", srcMat);
	imshow("处理后的图", dstMat);

	waitKey(0);
	return 0;
}
