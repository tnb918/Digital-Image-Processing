#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "funtions.h"
using namespace cv;
//�ֱ�ɾ������ͼ���еĸߵ�Ƶ��ʵ��ͼ����
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

	calcVisbalDft(resMat1, magMat1, ph1, normVal1);//���㸵��Ҷ�任���ӻ��ķ�ֵ��
	calcVisbalDft(resMat2, magMat2, ph2, normVal2);
	selectPolygon(magMat1, mask11, mask12);//���ѡ�����Ƶ�ʣ�������Ӧmask
	selectPolygon(magMat2, mask21, mask22);
	magMat1 = magMat1.mul(mask11);//ɾ��ԭƵ��ͼ�е�ѡ��Ƶ��
	magMat2 = magMat2.mul(mask22);
	calcDft2Image(magMat1, ph1, normVal1, dstMat1);//����Ҷ��任���ָ�������ͼ��
	calcDft2Image(magMat2, ph2, normVal2, dstMat2);

	Mat dspMat;
	addWeighted(dstMat1, 0.5, dstMat2, 0.5, 0, dspMat);
	imshow("ͼ��1", dstMat1);
	imshow("ͼ��2", dstMat2);
	imshow("��Ϻ��ͼ��", dspMat);
	waitKey(0);
	return 0;
}
