//
// Created by Zeyad on 5/3/2023.
//

#ifndef UNTITLED_SPECTRAL_THRESHOLDING_H
#define UNTITLED_SPECTRAL_THRESHOLDING_H
#include <opencv2/opencv.hpp>
using namespace cv;

class spectral_thresholding {

private:

    static void computeHistogram(const Mat& image, int histogram[]);
public:
    spectral_thresholding();

  static  void apply(Mat& image, int numModes);


};


#endif //UNTITLED_SPECTRAL_THRESHOLDING_H
