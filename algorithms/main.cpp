#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#include "optimal_thresholding.h"
#include "region_growing.h"
#include "spectral_thresholding.h"
#include "otsu_thresholding.h"
#include "kmean.h"
#include "mean_shift.h"
int main() {
    Mat image = imread("02.jfif");
    if (image.empty()) {
        cout << "Error: Could not read image file." << endl;
        return -1;
    }else{
        imshow("Original Image", image);
    }

    int option=5;
    Mat output;

    if(option==0){

        region_growing().apply(image, output);
        imshow("Region Growing Image", output);

    }else if(option==1){

        optimal_thresholding().apply(image, output);
        imshow("Optimal Threshold Image", output);

    }else if(option==2){

        spectral_thresholding().apply(image, output, 15);
        imshow("Spectral Thresholding", output);

    }else if(option==3){

        otsu_thresholding().apply(image, output);
        imshow("Otsu Thresholding",output);

    }else if(option==4){
        kmean().apply(image, output, 16);
        imshow("K-mean",output);
    }else if(option==5){
        mean_shift().apply(image, output, 30);
        imshow("Mean Shift",output);
    }


    waitKey(0);
    return 0;
}




