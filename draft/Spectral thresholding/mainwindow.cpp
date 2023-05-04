#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    setCentralWidget(imageLabel);

    openImageButton = new QPushButton(tr("Open Image"), this);
    connect(openImageButton, &QPushButton::clicked, this, &MainWindow::onOpenImageClicked);

    modeComboBox = new QComboBox(this);
    modeComboBox->addItem("2 Modes");
    modeComboBox->addItem("3 Modes");
    modeComboBox->addItem("4 Modes");

    QToolBar *toolBar = addToolBar(tr("File"));
    toolBar->addWidget(openImageButton);
    toolBar->addWidget(modeComboBox);

    imageFileDialog = new QFileDialog(this, tr("Open Image"), QDir::homePath(), tr("Images (*.png *.xpm *.jpg *.bmp)"));
    imageFileDialog->setFileMode(QFileDialog::ExistingFile);

    setWindowTitle(tr("Spectral Thresholding"));
}

MainWindow::~MainWindow()
{
    delete imageLabel;
    delete openImageButton;
    delete imageFileDialog;
    delete modeComboBox;
}

void MainWindow::onOpenImageClicked()
{
    imageFileDialog->show();
}

void MainWindow::onImageSelected(const QString& filename)
{
    image = QImage(filename);
    thresholdImage();
}

void MainWindow::thresholdImage()
{
    if (image.isNull()) {
        return;
    }

    int numModes = modeComboBox->currentIndex() + 2;

    // Convert the image to grayscale
    QImage grayImage = image.convertToFormat(QImage::Format_Grayscale8);

    // Compute the histogram of the image
    int histogram[256] = {0};
    for (int y = 0; y < grayImage.height(); y++) {
        const uchar *scanline = grayImage.scanLine(y);
        for (int x = 0; x < grayImage.width(); x++) {
            histogram[scanline[x]]++;
        }
    }

    // Find the local minima of the histogram
    std::vector<int> minima;
    for (int i = 1; i < 255; i++) {
        if (histogram[i] < histogram[i-1] && histogram[i] < histogram[i+1]) {
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

    QImage segmentedImage(grayImage.size(), QImage::Format_Grayscale8);
    for (int y = 0; y < grayImage.height(); y++) {
        const uchar *srcScanline = grayImage.scanLine(y);
        uchar *dstScanline = segmentedImage.scanLine(y);
        for (int x = 0; x < grayImage.width(); x++) {
            dstScanline[x] = srcScanline[x] > threshold ? 255 : 0;
        }
    }

    imageLabel->setPixmap(QPixmap::fromImage(segmentedImage));
}
