#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#include "optimal_thresholding.h"
#include "region_growing.h"
int main() {
    Mat image = imread("03.jfif", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "Error: Could not read image file." << endl;
        return -1;
    }else{
        imshow("Original Image", image);
    }
    bool option=true;



    if(option){
        region_growing rg = region_growing();
        Mat result(image.rows, image.cols, CV_8UC1, Scalar(0));
        if (image.channels() == 1) {
            cout<<"Grayscale"<<endl;
            // Grayscale image
            for (int y = 0; y < image.rows; y++) {
                for (int x = 0; x < image.cols; x++) {
                    rg.region_grow_gray(image, result, x, y);
                }
            }
        } else  {
            cout<<"Colored"<<endl;
            // Colored image
            for (int y = 0; y < image.rows; y++) {
                for (int x = 0; x < image.cols; x++) {
                    rg.region_grow_color(image, result, x, y);
                }
            }
        }

        imshow("Region Growing Image", result);

    }else  {
        optimal_thresholding opt_thd = optimal_thresholding();
        int threshold = opt_thd.get_optimal_threshold(image);
        opt_thd.apply_threshold(image, threshold);
        imshow("Optimal Threshold Image", image);

    }



    waitKey(0);
    return 0;
}

