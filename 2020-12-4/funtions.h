#pragma once
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int dftDemo();
int mouseROI();

void on_mouse(int EVENT, int x, int y, int flags, void* userdata);
int selectPolygon(cv::Mat srcMat, cv::Mat& dstMat1, cv::Mat& dstMat2);
int calcVisibalMag(cv::Mat srcMat,cv::Mat & dstMat);
int calcVisbalDft(cv::Mat srcMat, cv::Mat & magMat,cv::Mat & ph,double & normVal);
int calcDft2Image(cv::Mat magMat,cv::Mat ph,double normVal, cv::Mat &dstMat);