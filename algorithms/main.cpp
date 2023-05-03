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
#include "local_thresholding.h"
#include "agglomerative.h"

int main() {
    Mat image = imread("02.jfif");
    if (image.empty()) {
        cout << "Error: Could not read image file." << endl;
        return -1;
    }else{
        imshow("Original Image", image);
    }

    int option=7;
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
        kmean().apply(image, output, 3);
        imshow("K-mean",output);
    }else if(option==5){
        mean_shift().apply(image, output, 100);
        imshow("Mean Shift",output);
    }else if(option==6){
        local_thresholding().apply(image, output,40,10);
        imshow("Local Thresholding",output);
    }else if(option==7){
        agglomerative().apply(image, output);
        imshow("Agglomerative",output);
    }


    waitKey(0);
    return 0;
}


