#ifndef KMEANS_H
#define KMEANS_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <QDebug>


using namespace std;

vector<int> find_closest_centroids(vector<vector<double>> X, vector<vector<double>> centroids);
vector<vector<double>> compute_centroids(vector<vector<double>> X, vector<int> idx, int K);
vector<vector<double>> run_kMeans(vector<vector<double>> X, vector<vector<double>> &initial_centroids,vector<int> &labels, int max_iters=10);
vector<vector<double>> kMeans_init_centroids(vector<vector<double>> X, int K);
void assignToClusters(vector<vector<double>> &vec,vector<int> labels,vector<vector<double>> centroids);
vector<vector<double>> convertMatToVector(cv::Mat image);
void processImageFromDataInVec(cv::Mat &image,vector<vector<double>> vec);
void printCentroids(vector<vector<double>> centroids);
void kMeansMainFunction(cv::Mat &image, int K);
void RGBtoLUV(int r, int g, int b, float& l, float& u, float& v);
void LUVtoRGB(float l, float u, float v, int& r, int& g, int& b);
#endif // KMEANS_H
