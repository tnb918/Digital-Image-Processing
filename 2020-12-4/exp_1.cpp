#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "funtions.h"
using namespace cv;

int main()
{
	//��ͼ��ת��Ϊ���ӵĸ���Ҷ�任ͼ��
	//dftDemo();
	//�������ȡͼ��ROIʵ������
	//mouseROI();

	/*******************************************
	1.����һ��ͼƬ����������ӻ��ķ�ֵ��
	2.�ٷ�ֵ��ͼ�ϣ�ͨ�����ѡ����Ҫȥ����Ƶ��
	3.ȥ����ѡ����źţ�Ȼ��ԭͼ��
	**********************************************/
	Mat srcMat = imread("Lena.jpg",0);
	Mat magMat, ph, dstMat;
	Mat mask1, mask2;
	double normVal;

	calcVisbalDft(srcMat, magMat, ph, normVal);//���㸵��Ҷ�任���ӻ��ķ�ֵ��
	selectPolygon(magMat, mask1, mask2);//���ѡ�����Ƶ�ʣ�������Ӧmask
	magMat = magMat.mul(mask1);//ɾ��ԭƵ��ͼ�е�ѡ��Ƶ��
	calcDft2Image(magMat, ph, normVal, dstMat);//����Ҷ��任���ָ�������ͼ��

	imshow("�����Ƶ��.jpg", magMat);
	imshow("ԭͼ", srcMat);
	imshow("������ͼ", dstMat);

	waitKey(0);
	return 0;
}
