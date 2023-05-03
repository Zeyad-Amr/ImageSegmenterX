//
// Created by Zeyad on 5/3/2023.
//

#include "local_thresholding.h"

void local_thresholding::apply(Mat inputImg,Mat& out, int blockSize, int C) {

    cvtColor(inputImg, inputImg, COLOR_BGR2GRAY);
    printf("entered applyLocalThreshold");
    Mat output(inputImg.rows, inputImg.cols, CV_8UC1, Scalar(0));
    Mat cumulative(inputImg.rows, inputImg.cols, CV_32SC1, Scalar(0));

    getCumulative2d(inputImg, cumulative);
    printf("got cumulative");
    for (int x = 0; x < inputImg.rows; ++x) {
        for (int y = 0; y < inputImg.cols; ++y) {
            int halfHeight = blockSize / 2;
            int neighborhoodSum, num;
            tie(neighborhoodSum, num) = getSumAndNum(cumulative, x + halfHeight, y + halfHeight, x - halfHeight, y - halfHeight);

            // Compute the local threshold using the mean and constant C
            int threshold = cvRound(static_cast<double>(neighborhoodSum) / num - C);

            // Apply the threshold to the pixel
            if (inputImg.at<uchar>(x, y) >= threshold) {
                output.at<uchar>(x, y) = 255;
            }
            else {
                output.at<uchar>(x, y) = 0;
            }
        }
    }

    out=output;
}

void local_thresholding::getCumulative2d(Mat inputImg, Mat& cumulative) {
    int w = inputImg.rows;
    int h = inputImg.cols;

    cumulative.at<int>(0, 0) = inputImg.at<uchar>(0, 0);

    for (int i = 1; i < w; ++i) {
        cumulative.at<int>(i, 0) = cumulative.at<int>(i - 1, 0) + inputImg.at<uchar>(i, 0);
    }

    for (int i = 1; i < h; ++i) {
        cumulative.at<int>(0, i) = cumulative.at<int>(0, i - 1) + inputImg.at<uchar>(0, i);
    }

    for (int i = 1; i < w; ++i) {
        for (int j = 1; j < h; ++j) {
            cumulative.at<int>(i, j) = cumulative.at<int>(i - 1, j) + cumulative.at<int>(i, j - 1) - cumulative.at<int>(i - 1, j - 1) + inputImg.at<uchar>(i, j);
        }
    }
}

tuple<int, int> local_thresholding::getSumAndNum(const Mat& cumulative, int bottomRightX, int bottomRightY, int topLeftX, int topLeftY) {
    int w = cumulative.rows;
    int h = cumulative.cols;

    // Make sure coordinates are inside the shape and if not let it be.
    bottomRightX = max(min(w-1, bottomRightX), 0);
    bottomRightY = max(min(h-1, bottomRightY), 0);
    topLeftX = max(min(w-1, topLeftX), 0);
    topLeftY = max(min(h-1, topLeftY), 0);

    int bottomLeftX = bottomRightX;
    int bottomLeftY = topLeftY;

    int topRightX = topLeftX;
    int topRightY = bottomRightY;

    int blockSum = cumulative.at<int>(bottomRightX, bottomRightY);
    if (topRightX > 0) {
        blockSum -= cumulative.at<int>(topRightX - 1, topRightY);
    }
    if (bottomLeftY > 0) {
        blockSum -= cumulative.at<int>(bottomLeftX, bottomLeftY - 1);
    }
    if (topLeftX > 0 && topLeftY > 0) {
        blockSum += cumulative.at<int>(topLeftX - 1, topLeftY - 1);
    }

    int n = (bottomRightX - topRightX + 1) * (bottomRightY - bottomLeftY + 1);

    return make_tuple(blockSum, n);
}