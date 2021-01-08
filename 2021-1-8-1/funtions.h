#pragma once
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

VideoCapture createInput(bool useCamera, std::string videoPath);
void segColor();
int kMeansDemo();
int createMaskByKmeans(cv::Mat src, cv::Mat& mask);
void addEffect();