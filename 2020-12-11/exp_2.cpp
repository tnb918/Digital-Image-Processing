#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("Lena.jpg");
	Mat dstMat;

	vector<Mat> channels;
	split(srcMat, channels);
	Mat B = channels.at(0);
	Mat G = channels.at(1);
	Mat R = channels.at(2);

	equalizeHist(B, B);
	equalizeHist(G, G);
	equalizeHist(R, R);

	merge(channels, dstMat);

	imshow("ԭͼ", srcMat);
	imshow("ֱ��ͼ���⻯��", dstMat);
	waitKey(0);
	return 0;
}