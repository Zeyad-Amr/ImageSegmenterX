#include <QMainWindow>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QImage>
#include <vector>
#include <cmath>

struct Pixel {
    int x;
    int y;
    float r;
    float g;
    float b;
};

struct Cluster {
    std::vector<Pixel> pixels;
    float rSum;
    float gSum;
    float bSum;
};

float distance(const Pixel& p1, const Pixel& p2) {
    float dr = p1.r - p2.r;
    float dg = p1.g - p2.g;
    float db = p1.b - p2.b;
    return std::sqrt(dr*dr + dg*dg + db*db);
}

std::vector<Cluster> agglomerativeClustering(const std::vector<Pixel>& pixels, int nClusters) {
    std::vector<Cluster> clusters;
    for (const Pixel& pixel : pixels) {
        clusters.push_back({ { pixel }, pixel.r, pixel.g, pixel.b });
    }
    while (clusters.size() > nClusters) {
        int c1 = 0, c2 = 1;
        float minDist = distance(clusters[0].pixels[0], clusters[1].pixels[0]);
        for (int i = 0; i < clusters.size(); i++) {
            for (int j = i+1; j < clusters.size(); j++) {
                float dist = distance(clusters[i].pixels[0], clusters[j].pixels[0]);
                if (dist < minDist) {
                    c1 = i;
                    c2 = j;
                    minDist = dist;
                }
            }
        }
        clusters[c1].pixels.insert(clusters[c1].pixels.end(), clusters[c2].pixels.begin(), clusters[c2].pixels.end());
        clusters[c1].rSum += clusters[c2].rSum;
        clusters[c1].gSum += clusters[c2].gSum;
        clusters[c1].bSum += clusters[c2].bSum;
        clusters.erase(clusters.begin() + c2);
    }
    return clusters;
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Create the menu bar
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu(tr("&File"));

    // Create the "Open" menu item
    QAction *openAction = fileMenu->addAction(tr("&Open"));
    connect(openAction, &QAction::triggered, this, &MainWindow::openImage);

    // Create the "Segment" menu item
    QAction *segmentAction = fileMenu->addAction(tr("&Segment"));
    connect(segmentAction, &QAction::triggered, this, &MainWindow::segmentImage);

    // Set the menu bar
    setMenuBar(menuBar);

    // Create the label to display the image
    imageLabel = new QLabel(this);
    setCentralWidget(imageLabel);
}

void MainWindow::openImage() {
    // Open the file dialog to select an image file
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Images (*.png *.bmp *.jpg)"));
    if (!fileName.isEmpty()) {
        // Load the image and display it
        image.load(fileName);
        imageLabel->setPixmap(QPixmap::fromImage(image));
        imageLabel->adjustSize();
    }
}

void MainWindow::segmentImage() {
    if (image.isNull()) {
        // If no image is loaded, display an error message
        QMessageBox::warning(this, tr("Error"), tr("No image loaded."));
        return;
    }

    // Convert the image to a vector of pixels
    std::vector<Pixel> pixels;
    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            QRgb color = image.pixel(x, y);
            pixels.push_back({ x, y, qRed(color), qGreen(color), qBlue(color) });
        }
    }

    // Perform the clustering on the pixels
    std::vector<Cluster> clusters = agglomerativeClustering(pixels, 5);

    // Create the segmented image
    QImage segmentedImage(image.width(), image.height(), QImage::Format_RGB32);
    QPainter painter(&segmentedImage);
    for (const Cluster& cluster : clusters) {
        QColor color(cluster.rSum / cluster.pixels.size(), cluster.gSum / cluster.pixels.size(), cluster.bSum / cluster.pixels.size());
        for (const Pixel& pixel : cluster.pixels) {
            painter.setPen(color);
            painter.drawPoint(pixel.x, pixel.y);
        }
    }
    painter.end();

    // Display the segmented image
    imageLabel->setPixmap(QPixmap::fromImage(segmentedImage));
    imageLabel->adjustSize();
}

#include "main.moc"
