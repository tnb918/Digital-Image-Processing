#include <opencv2/opencv.hpp>
#include "funtions.h"

using namespace cv;
using namespace std;

int main()
{
	//开始计时
	double start = static_cast<double>(cvGetTickCount());

	/* K-means对随机点进行分类 */
	//kMeansDemo();

	/* K-means实现抠图操作 */
	//segColor();

	/* 添加特效 */
	addEffect();

	//结束计时
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//显示时间
	cout << "processing time:" << time / 1000 << "ms" << endl;

	//等待键盘响应，按任意键结束程序
	system("pause");
	return 0;
}