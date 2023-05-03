//
// Created by Zeyad on 5/3/2023.
//

#ifndef ALGORITHMS_KMEAN_H
#define ALGORITHMS_KMEAN_H
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class kmean {
private:
    static vector<int> find_closest_centroids(vector<vector<double>> X, vector<vector<double>> centroids);
    static vector<vector<double>> compute_centroids(vector<vector<double>> X, vector<int> idx, int K);
    static vector<vector<double>> run_kMeans(vector<vector<double>> X, vector<vector<double>> &initial_centroids,vector<int> &labels, int max_iters=10);
    static vector<vector<double>> kMeans_init_centroids(vector<vector<double>> X, int K);
    static void assignToClusters(vector<vector<double>> &vec,vector<int> labels,vector<vector<double>> centroids);
    static vector<vector<double>> convertMatToVector(Mat image);
    static void processImageFromDataInVec(Mat &image,vector<vector<double>> vec);
    static void printCentroids(vector<vector<double>> centroids);
    static void RGBtoLUV(int r, int g, int b, float& l, float& u, float& v);
    static void LUVtoRGB(float l, float u, float v, int& r, int& g, int& b);
public:
    static void apply(Mat image,Mat& output, int K);
};


#endif //ALGORITHMS_KMEAN_H
