//
// Created by Zeyad on 5/3/2023.
//

#include "spectral_thresholding.h"
using namespace cv;

spectral_thresholding::spectral_thresholding() {

}
void spectral_thresholding:: computeHistogram(const Mat& image, int histogram[]) {
    memset(histogram, 0, sizeof(int) * 256);
    for (int y = 0; y < image.rows; y++) {
        const uchar* row_ptr = image.ptr<uchar>(y);
        for (int x = 0; x < image.cols; x++) {
            histogram[row_ptr[x]]++;
        }
    }
}

void spectral_thresholding::apply(Mat& image, int numModes) {
    if (image.empty()) {
        return;
    }

    // Convert the image to grayscale
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    // Compute the histogram of the image
    int histogram[256] = {0};
    computeHistogram(grayImage, histogram);

    // Find the local minima of the histogram
    std::vector<int> minima;
    for (int i = 1; i < 255; i++) {
        if (histogram[i] < histogram[i - 1] && histogram[i] < histogram[i + 1]) {
            minima.push_back(i);
        }
    }

    // Sort the minima by their histogram value in descending order
    std::sort(minima.begin(), minima.end(), [&](int a, int b) {
        return histogram[a] > histogram[b];
    });

    // Threshold the image using the specified number of modes
    int threshold = 0;
    for (int i = 0; i < std::min(numModes, static_cast<int>(minima.size())); i++) {
        threshold += minima[i];
    }
    threshold /= numModes;

    // Threshold the image manually
    Mat segmentedImage(grayImage.size(), CV_8UC1);
    for (int y = 0; y < grayImage.rows; y++) {
        const uchar* srcRow = grayImage.ptr<uchar>(y);
        uchar* dstRow = segmentedImage.ptr<uchar>(y);
        for (int x = 0; x < grayImage.cols; x++) {
            dstRow[x] = srcRow[x] > threshold ? 255 : 0;
        }
    }

    image = segmentedImage;
}
