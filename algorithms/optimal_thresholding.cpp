//
// Created by Zeyad on 5/3/2023.
//

#include "optimal_thresholding.h"

optimal_thresholding::optimal_thresholding() {

}

void optimal_thresholding::apply(Mat image, Mat& output) {
    cvtColor(image, image, COLOR_BGR2GRAY);
    int threshold = get_optimal_threshold(image);
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            if (image.at<uchar>(i, j) > threshold) {
                image.at<uchar>(i, j) = 255;
            } else {
                image.at<uchar>(i, j) = 0;
            }
        }
    }
    output=image;
}

int optimal_thresholding::get_optimal_threshold(cv::Mat &image) {
    int hist[256] = {0};
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            hist[image.at<uchar>(i, j)]++;
        }
    }
    int total_pixels = image.rows * image.cols;
    double sum = 0;
    for (int i = 0; i < 256; i++) {
        sum += i * hist[i];
    }
    double sumB = 0;
    int wB = 0;
    int wF = 0;
    double max_variance = 0;
    int threshold = 0;
    for (int i = 0; i < 256; i++) {
        wB += hist[i];
        if (wB == 0) {
            continue;
        }
        wF = total_pixels - wB;
        if (wF == 0) {
            break;
        }
        sumB += i * hist[i];
        double meanB = sumB / wB;
        double meanF = (sum - sumB) / wF;
        double variance = wB * wF * pow(meanB - meanF, 2);
        if (variance > max_variance) {
            max_variance = variance;
            threshold = i;
        }
    }
    return threshold;
}