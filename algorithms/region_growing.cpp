//
// Created by Zeyad on 5/3/2023.
//

#include "region_growing.h"

region_growing::region_growing() {}

void region_growing::region_grow_gray(Mat& image, Mat& result, int x, int y) {
    if (x < 0 || x >= image.cols || y < 0 || y >= image.rows || result.at<uchar>(y, x) != 0) {
        // Out of bounds or already processed
        return;
    }
    if (abs(image.at<uchar>(y, x) - image.at<uchar>(0, 0)) > THRESHOLD) {
        // Outside of threshold range
        return;
    }
    result.at<uchar>(y, x) = 255;
    region_grow_gray(image, result, x - 1, y); // Check left pixel
    region_grow_gray(image, result, x + 1, y); // Check right pixel
    region_grow_gray(image, result, x, y - 1); // Check top pixel
    region_grow_gray(image, result, x, y + 1); // Check bottom pixel
}

void region_growing::region_grow_color(Mat& image, Mat& result, int x, int y) {
    if (x < 0 || x >= image.cols || y < 0 || y >= image.rows || result.at<uchar>(y, x) != 0) {
        // Out of bounds or already processed
        return;
    }
    Vec3b pixel = image.at<Vec3b>(y, x);
    Vec3b seed = image.at<Vec3b>(0, 0);
    int distance = sqrt(pow(seed[0] - pixel[0], 2) + pow(seed[1] - pixel[1], 2) + pow(seed[2] - pixel[2], 2));
    if (distance > THRESHOLD) {
        // Outside of threshold range
        return;
    }
    result.at<uchar>(y, x) = 255;
    region_grow_color(image, result, x - 1, y); // Check left pixel
    region_grow_color(image, result, x + 1, y); // Check right pixel
    region_grow_color(image, result, x, y - 1); // Check top pixel
    region_grow_color(image, result, x, y + 1); // Check bottom pixel
}

void region_growing::apply(cv::Mat &image) {

    Mat result(image.rows, image.cols, CV_8UC1, Scalar(0));
    if (image.channels() == 1) {
        // Grayscale image
        for (int y = 0; y < image.rows; y++) {
            for (int x = 0; x < image.cols; x++) {
                region_grow_gray(image, result, x, y);
            }
        }
    } else  {
        // Colored image
        for (int y = 0; y < image.rows; y++) {
            for (int x = 0; x < image.cols; x++) {
                region_grow_color(image, result, x, y);
            }
        }
    }
    image =result;
}
