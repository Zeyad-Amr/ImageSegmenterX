#include "mainwindow.h"
#include "k-means.h"


#include <cmath>

void RGBtoLUV(int R, int G, int B, double& L, double& U, double& V) {
    // Convert RGB to XYZ
    double r = R / 255.0;
    double g = G / 255.0;
    double b = B / 255.0;
    double x = 0.412453*r + 0.357580*g + 0.180423*b;
    double y = 0.212671*r + 0.715160*g + 0.072169*b;
    double z = 0.019334*r + 0.119193*g + 0.950227*b;

    // Convert XYZ to LUV
    double yr = y / 1.0;
    double ur = (4.0 * x) / (x + (15.0 * y) + (3.0 * z));
    double vr = (9.0 * y) / (x + (15.0 * y) + (3.0 * z));

    double L1 = 0.0, U1 = 0.0, V1 = 0.0;

    if (yr > 0.008856) {
        L1 = 116.0 * pow(yr, 1.0/3.0) - 16.0;
    } else {
        L1 = 903.3 * yr;
    }

    U1 = 13.0 * L1 * (ur - 0.19793943);
    V1 = 13.0 * L1 * (vr - 0.46831096);

    // Set output values
    L = L1;
    U = U1;
    V = V1;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Load the image using OpenCV
    cv::Mat image = cv::imread("D:/SBME/3rd year/2nd term/CV/Ass 2/repo/Photostudio/images/ccc.png");

    // Check if the image was loaded successfully
    if (image.empty()) {
        qDebug() << "Could not open or find the image";
        return -1;
    }
//    kMeansMainFunction(image,2);
    cv::Vec3b pixel = image.at<cv::Vec3b>(0,0);
    double l,u,v;
    RGBtoLUV(125,12,80,l,u,v);
    qDebug("%f %f %f\n",l,u,v);
    return a.exec();
}
