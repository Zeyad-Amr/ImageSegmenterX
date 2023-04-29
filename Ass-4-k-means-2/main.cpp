#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <set>
#include "k-means.h"
#include "mean-shift.h"

#include <cmath>
#include <vector>
#include <cmath>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Load the image using OpenCV
    cv::Mat image = cv::imread("D:/SBME/3rd year/2nd term/CV/Ass 2/repo/Photostudio/images/ellipse.png");
    qDebug("rows: %d, cols: %d",image.rows,image.cols);

    // Check if the image was loaded successfully
    if (image.empty()) {
        qDebug() << "Could not open or find the image";
        return -1;
    }

//    kMeansMainFunction(image,16);
    meanShiftMainFunction(image,30);

    return 0;
    return a.exec();
}


