#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

int main()
{
	Mat srcMat = imread("Lena.jpg");
	Mat dstMat;
	if (srcMat.empty()) return -1;

	//��ת�Ƕȣ����ű���
	float angle = -10.0, scale = 1;
	//��ת����Ϊͼ������
	Point2f center(srcMat.cols * 0.5, srcMat.rows * 0.5);		
	//��ñ任����
	Mat affine_matrix = getRotationMatrix2D(center, angle, scale);
	//��ȡ����ı���
	Rect bbox = RotatedRect(center, srcMat.size(), angle).boundingRect();
	//��������������
	affine_matrix.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	affine_matrix.at<double>(1, 2) += bbox.height / 2.0 - center.y;
	//����任
	warpAffine(srcMat, dstMat, affine_matrix, bbox.size());

	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
}