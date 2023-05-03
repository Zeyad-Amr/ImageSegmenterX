#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QComboBox>
#include <QImage>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onOpenImageClicked();
    void onImageSelected(const QString& filename);

private:
    QLabel *imageLabel;
    QPushButton *openImageButton;
    QFileDialog *imageFileDialog;
    QComboBox *modeComboBox;
    QImage image;

    void thresholdImage();
};

#endif // MAINWINDOW_H
