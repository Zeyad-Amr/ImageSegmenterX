//
// Created by Zeyad on 5/3/2023.
//

#ifndef UNTITLED_AGGLOMERATIVE_H
#define UNTITLED_AGGLOMERATIVE_H

#include <cmath>
#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace cv;
using namespace std;



class agglomerative {
private:
   static double euclidean_distance(const vector<double> &point1, const vector<double> &point2);

    static double clusters_distance(const vector<vector<double>> &cluster1, const vector<vector<double>> &cluster2);

    static vector<vector<vector<double>>> initial_clusters(Mat img_matrix);

    static void fit(int k, Mat &img, vector<int> &labels, map<int, vector<double>> &centers, map<vector<double>, int> &cluster_map);

    static int predict_cluster(map<vector<double>, int> &cluster_map, vector<double> &point);

    static vector<double> predict_center(map<int, vector<double>> &centers, map<vector<double>, int> &cluster_map, vector<double> &point);

    static pair<Mat, Mat> adjust(Mat &image);

    static Mat segmentation(int k, Mat &img, Mat &resized);

public:
    static void apply(Mat image, Mat& output){
        Mat img;
        Mat resized;
        agglomerative ag= agglomerative();
        tie(img, resized) =ag.adjust(image);
        output = ag.segmentation(24, img, resized);
    }
};

#endif //UNTITLED_AGGLOMERATIVE_H
