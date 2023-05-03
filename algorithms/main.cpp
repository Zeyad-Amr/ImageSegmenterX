#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#include "optimal_thresholding.h"
#include "region_growing.h"
#include "spectral_thresholding.h"
#include "otsu_thresholding.h"
int main() {
    Mat image = imread("02.jfif");
    if (image.empty()) {
        cout << "Error: Could not read image file." << endl;
        return -1;
    }else{
        imshow("Original Image", image);
    }

    int option=3;

    if(option==0){

        region_growing().apply(image);
        imshow("Region Growing Image", image);

    }else if(option==1){

        optimal_thresholding().apply(image);
        imshow("Optimal Threshold Image", image);

    }else if(option==2){

        spectral_thresholding().apply(image, 15);
        imshow("Spectral Thresholding", image);

    }else if(option==3){

        otsu_thresholding().apply(image);
        imshow("Otsu Thresholding", image);

    }


    waitKey(0);
    return 0;
}




