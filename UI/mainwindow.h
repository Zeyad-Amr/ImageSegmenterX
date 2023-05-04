
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QLabel>
#include <QFileDialog>
#include <QButtonGroup>

#include "kmean.h"
#include "optimal_thresholding.h"
#include "otsu_thresholding.h"
#include "region_growing.h"
#include "spectral_thresholding.h"
#include "agglomerative.h"
#include "local_thresholding.h"
#include "mean_shift.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    cv::Mat inputImage;
    cv::Mat outputImage;

private slots:
    void on_input_btn_clicked();

    QString getFile();
    cv::Mat getMat(QString fileName);
    QImage convertMatToQimage(cv::Mat imgMat, int flag = 0);
    void setLabelImg(QLabel *label, QImage qimage, unsigned int w = 0, unsigned int h = 0);

    void on_optimal_clicked();
    void on_otsu_clicked();
    void on_mean_shift_clicked();
    void on_k_means_clicked();
    void on_local_clicked();
    void on_agglo_clicked();
    void on_spectral_clicked();
    void on_region_clicked();
    void on_radioButton_1_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_radioButton_4_clicked();
};

#endif // MAINWINDOW_H
