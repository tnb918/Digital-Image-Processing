#include <opencv2/opencv.hpp>
#include "funtions.h"

using namespace cv;
using namespace std;

int main()
{
	//开始计时
	double start = static_cast<double>(cvGetTickCount());

	int method = DEMO_METHOD;

	if (method == 0) {
		yoloV3();
	}
	else if (method == 1) {
		openpose();
	}

	//结束计时
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//显示时间
	cout << "processing time:" << time / 1000 << "ms" << endl;

	//等待键盘响应，按任意键结束程序
	system("pause");

	return 0;
}