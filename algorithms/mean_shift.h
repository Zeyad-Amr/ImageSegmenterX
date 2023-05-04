//
// Created by Zeyad on 5/3/2023.
//

#ifndef ALGORITHMS_MEAN_SHIFT_H
#define ALGORITHMS_MEAN_SHIFT_H
#include "kmean.h"

class mean_shift
{
private:
    static void showCentroids(Mat &image, vector<vector<double>> &centroids);
    static vector<int> getLabels(vector<vector<double>> &X, vector<vector<double>> &centroids);
    static vector<vector<double>> getCentroids(vector<vector<double>> &X, double radius, double threshold);
    static vector<double> getFate(vector<vector<double>> &X, vector<double> &pointFeatureSet, double radius, double threshold);
    static double linalgNorm(vector<double> arr1, vector<double> arr2);

public:
    static void apply(Mat image, Mat &output, int radius = 15);
};

#endif // ALGORITHMS_MEAN_SHIFT_H
