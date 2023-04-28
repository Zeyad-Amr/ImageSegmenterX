#include "mainwindow.h"
#include "k-means.h"

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
    kMeansMainFunction(image,2);

    return a.exec();
}
