//
// Created by Zeyad on 5/3/2023.
//

#ifndef UNTITLED_OTSU_THRESHOLDING_H
#define UNTITLED_OTSU_THRESHOLDING_H
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

class otsu_thresholding {
public:
    otsu_thresholding();
    static void apply(Mat& inputImg);

};


#endif //UNTITLED_OTSU_THRESHOLDING_H
