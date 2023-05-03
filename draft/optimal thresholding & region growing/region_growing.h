//
// Created by Zeyad on 5/3/2023.
//

#ifndef UNTITLED_REGION_GROWING_H
#define UNTITLED_REGION_GROWING_H
#include <iostream>
#include <cmath>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace cv;

class region_growing {
public:
    const int THRESHOLD = 50; // Threshold for region growing
    region_growing();
    void region_grow_gray(Mat& image, Mat& result, int x, int y);
    void region_grow_color(Mat& image, Mat& result, int x, int y);

};


#endif //UNTITLED_REGION_GROWING_H
