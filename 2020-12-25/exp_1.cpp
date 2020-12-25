#include<opencv2/opencv.hpp>
using namespace cv;

int main()
{
	VideoCapture cap;
	cap.open(0);

	int cnt = 0;
	Mat frame;
	Mat tempMat;
	Mat refMat;
	Mat resultMat;

	while (1)
	{
		cap >> frame;
		if (cnt == 0)
		{
			Rect2d r;
			r = selectROI(frame, true);
			tempMat = frame(r);
			tempMat.copyTo(refMat);
			destroyAllWindows();
			cnt++;
		}

		//ģ��ƥ��
		int match_method = 0;
		matchTemplate(frame, refMat, resultMat, match_method);

		//��һ��
		normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());

		//Ѱ�Ҽ�ֵ
		double minVal; double maxVal; 
		Point minLoc; Point maxLoc;
		minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
		
		//�����ο�
		Rect rect;
		rect.x = minLoc.x;
		rect.y = minLoc.y;
		rect.width = refMat.cols;
		rect.height = refMat.rows;
		rectangle(frame, rect, CV_RGB(255, 0, 0), 2, 8, 0);

		imshow("ģ��ƥ��", frame);
		waitKey(30);
	}

	return 0;
}