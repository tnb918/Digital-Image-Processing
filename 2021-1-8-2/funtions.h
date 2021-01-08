#pragma once
#include <opencv2/opencv.hpp>
#include <dnn.hpp>

using namespace cv;
using namespace std;
using namespace dnn;

//ѡ����Ҫ��ʾ��demo
#define DEMO_METHOD		0			//0:yolov3 demo	1:openpose demo	

//��������
#define YOLOV3_VIDEO		"test.mp4"		
#define OPENPOSE_VIDEO		"test.mp4"		

//ͨ���Ǽ���ֵ����ȥ�����ŶȽϵ͵�bouding box
void postprocess(cv::Mat& frame, std::vector<cv::Mat>& outs);

// ����������
std::vector<cv::String> getOutputsNames(const cv::dnn::Net& net);

//���Ƽ����
void drawPred(int classId, float conf, int left, int top, int right, int bottom, cv::Mat& frame);

int yoloV3();

int openpose();