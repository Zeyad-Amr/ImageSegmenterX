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
private:
    static const int THRESHOLD = 50; // Threshold for region growing
    static void region_grow_gray(Mat& image, Mat& result, int x, int y);
    static void region_grow_color(Mat& image, Mat& result, int x, int y);
public:

    region_growing();

   static void apply(Mat& image);

};


#endif //UNTITLED_REGION_GROWING_H
