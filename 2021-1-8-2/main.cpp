#include <opencv2/opencv.hpp>
#include "funtions.h"

using namespace cv;
using namespace std;

int main()
{
	//��ʼ��ʱ
	double start = static_cast<double>(cvGetTickCount());

	int method = DEMO_METHOD;

	if (method == 0) {
		yoloV3();
	}
	else if (method == 1) {
		openpose();
	}

	//������ʱ
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//��ʾʱ��
	cout << "processing time:" << time / 1000 << "ms" << endl;

	//�ȴ�������Ӧ�����������������
	system("pause");

	return 0;
}