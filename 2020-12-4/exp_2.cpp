#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "funtions.h"
using namespace cv;
//分别删除两张图像中的高低频，实现图像混合
int main()
{
	Mat srcMat1 = imread("Lena.jpg", 0); 
	Mat srcMat2 = imread("man.jpg", 0);
	Mat resMat1, resMat2;

	resize(srcMat1, resMat1, Size(500, 500));
	resize(srcMat2, resMat2, Size(500, 500));

	Mat magMat1, magMat2;
	Mat ph1, ph2;
	Mat dstMat1, dstMat2;
	Mat mask11, mask12, mask21, mask22;
	double normVal1, normVal2;

	calcVisbalDft(resMat1, magMat1, ph1, normVal1);//计算傅里叶变换可视化的幅值谱
	calcVisbalDft(resMat2, magMat2, ph2, normVal2);
	selectPolygon(magMat1, mask11, mask12);//鼠标选择处理的频率，产生对应mask
	selectPolygon(magMat2, mask21, mask22);
	magMat1 = magMat1.mul(mask11);//删除原频谱图中的选中频率
	magMat2 = magMat2.mul(mask22);
	calcDft2Image(magMat1, ph1, normVal1, dstMat1);//傅里叶逆变换，恢复处理后的图像
	calcDft2Image(magMat2, ph2, normVal2, dstMat2);

	Mat dspMat;
	addWeighted(dstMat1, 0.5, dstMat2, 0.5, 0, dspMat);
	imshow("图像1", dstMat1);
	imshow("图像2", dstMat2);
	imshow("混合后的图像", dspMat);
	waitKey(0);
	return 0;
}
