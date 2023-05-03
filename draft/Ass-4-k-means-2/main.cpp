#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <set>
#include "k-means.h"
#include "mean-shift.h"
#include "localthreshold.h"

#include <cmath>
#include <vector>
#include <cmath>

//void localThreshold( cv::Mat& input, cv::Mat& output, int blockSize, double C) {
//     if(blockSize%2==0){
//         blockSize=blockSize+1;
//     }

//     vector<int> pixelValues(blockSize * blockSize);
//     output.create(input.rows, input.cols, CV_8UC1);

//     for (int y = 0; y < input.rows; y++)
//         {
//             for (int x = 0; x < input.cols; x++)
//             {
//                 // Get the neighborhood around the pixel
//                 int index = 0;
//                 for (int j = -blockSize / 2; j <= blockSize / 2; j++)
//                 {
//                     for (int i = -blockSize / 2; i <= blockSize / 2; i++)
//                     {
//                         // Check if the pixel is within the image boundaries
//                         int px = x + i;
//                         int py = y + j;
//                         if (px >= 0 && px < input.cols && py >= 0 && py < input.rows)
//                         {
//                             pixelValues[index++] = input.at<uchar>(py, px);
//                         }
//                     }
//                 }

//                 // Compute the local threshold using the mean and constant C
//                 int threshold = (int)round(cv::mean(pixelValues)[0] - C);

//                 // Apply the threshold to the pixel
//                 if (input.at<uchar>(y, x) >= threshold)
//                 {
//                     output.at<uchar>(y, x) = 255;
//                 }
//                 else
//                 {
//                     output.at<uchar>(y, x) = 0;
//                 }
//             }
//         }
//}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Load the image using OpenCV
    cv::Mat image = cv::imread("D:/SBME/3rd year/2nd term/CV/Ass 2/repo/Photostudio/images/01.jpeg",0);
    qDebug("rows: %d, cols: %d",image.rows,image.cols);

    // Check if the image was loaded successfully
    if (image.empty()) {
        qDebug() << "Could not open or find the image";
        return -1;
    }
//    cv::imshow("output",image);
//    cv::waitKey(0);
//    kMeansMainFunction(image,16);
//    meanShiftMainFunction(image,30);
    cv::Mat output;
    applyLocalThreshold(image,40,10);
//    cv::imshow("output",output);
//    cv::waitKey(0);
//    cv::imwrite("D:/SBME/3rd year/2nd term/CV/Ass 4.1/a04-16/localThresholdQt.jpg",output);
    qDebug("saved");
    return 0;
    return a.exec();
}


