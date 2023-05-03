#ifndef MEANSHIFT_H
#define MEANSHIFT_H

#include "k-means.h"
void meanShiftMainFunction(cv::Mat &image, int radius=15);
void showCentroids(cv::Mat& image, std::vector<std::vector<double>>& centroids);
std::vector<int> getLabels(std::vector<std::vector<double>>& X, std::vector<std::vector<double>>& centroids);
std::vector<std::vector<double>> getCentroids(std::vector<std::vector<double>>& X, double radius, double threshold);
std::vector<double> getFate(std::vector<std::vector<double>>& X, std::vector<double>& pointFeatureSet, double radius, double threshold);
double linalgNorm(std::vector<double> arr1,std::vector<double> arr2);

#endif // MEANSHIFT_H
