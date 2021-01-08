#pragma once
#include <opencv2/opencv.hpp>
#include <dnn.hpp>

using namespace cv;
using namespace std;
using namespace dnn;

//选择需要演示的demo
#define DEMO_METHOD		0			//0:yolov3 demo	1:openpose demo	

//参数设置
#define YOLOV3_VIDEO		"test.mp4"		
#define OPENPOSE_VIDEO		"test.mp4"		

//通过非极大值抑制去掉置信度较低的bouding box
void postprocess(cv::Mat& frame, std::vector<cv::Mat>& outs);

// 获得输出名字
std::vector<cv::String> getOutputsNames(const cv::dnn::Net& net);

//绘制检测结果
void drawPred(int classId, float conf, int left, int top, int right, int bottom, cv::Mat& frame);

int yoloV3();

int openpose();