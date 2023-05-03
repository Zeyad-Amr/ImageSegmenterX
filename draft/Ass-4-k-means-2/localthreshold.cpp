#include "localthreshold.h"



cv::Mat applyLocalThreshold(cv::Mat inputImg, int blockSize, int C) {
    qDebug("entered applyLocalThreshold");
    cv::Mat output(inputImg.rows, inputImg.cols, CV_8UC1, cv::Scalar(0));
    cv::Mat cumulative(inputImg.rows, inputImg.cols, CV_32SC1, cv::Scalar(0));

    getCumulative2d(inputImg, cumulative);
    qDebug("got cumulative");
    for (int x = 0; x < inputImg.rows; ++x) {
        for (int y = 0; y < inputImg.cols; ++y) {
            int halfHeight = blockSize / 2;
            int neighborhoodSum, num;
            std::tie(neighborhoodSum, num) = getSumAndNum(cumulative, x + halfHeight, y + halfHeight, x - halfHeight, y - halfHeight);

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
    qDebug("finished all pixels");
    cv::imshow("output",output);
    cv::waitKey(0);
    qDebug("mm%d %d",output.rows,output.cols);

    return output;
}

void getCumulative2d(cv::Mat inputImg, cv::Mat& cumulative) {
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

std::tuple<int, int> getSumAndNum(const cv::Mat& cumulative, int bottomRightX, int bottomRightY, int topLeftX, int topLeftY) {
    int w = cumulative.rows;
    int h = cumulative.cols;

    // Make sure coordinates are inside the shape and if not let it be.
    bottomRightX = std::max(std::min(w-1, bottomRightX), 0);
    bottomRightY = std::max(std::min(h-1, bottomRightY), 0);
    topLeftX = std::max(std::min(w-1, topLeftX), 0);
    topLeftY = std::max(std::min(h-1, topLeftY), 0);

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

    return std::make_tuple(blockSum, n);
}
