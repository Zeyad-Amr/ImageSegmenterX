#ifndef LOCALTHRESHOLD_H
#define LOCALTHRESHOLD_H
#include "k-means.h"

cv::Mat applyLocalThreshold(cv::Mat inputImg, int blockSize = 10,int C = 5);
void getCumulative2d(cv::Mat inputImg, cv::Mat& cumulative);
std::tuple<int, int> getSumAndNum(const cv::Mat& cumulative, int bottomRightX, int bottomRightY, int topLeftX, int topLeftY);

#endif // LOCALTHRESHOLD_H
