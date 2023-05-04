//
// Created by Zeyad on 5/3/2023.
//

#ifndef UNTITLED_OPTIMAL_THRESHOLDING_H
#define UNTITLED_OPTIMAL_THRESHOLDING_H
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
using namespace cv;

class optimal_thresholding {

public:

    optimal_thresholding();

    int get_optimal_threshold(Mat& image);
    void apply_threshold(Mat& image, int threshold) ;

};


#endif //UNTITLED_OPTIMAL_THRESHOLDING_H
