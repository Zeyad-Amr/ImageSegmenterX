#ifndef ALGORITHMS_LOCAL_THRESHOLDING_H
#define ALGORITHMS_LOCAL_THRESHOLDING_H
#include "kmean.h"

class local_thresholding
{

private:
    static void getCumulative2d(Mat inputImg, Mat &cumulative);
    static tuple<int, int> getSumAndNum(const Mat &cumulative, int bottomRightX, int bottomRightY, int topLeftX, int topLeftY);

public:
    static void apply(Mat inputImg, Mat &output, int blockSize = 10, int C = 5);
};

#endif // ALGORITHMS_LOCAL_THRESHOLDING_H
