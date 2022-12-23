#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <QDebug>
#include <vector>
using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this);
    string str = filename.toStdString();
    image = imread(str, IMREAD_GRAYSCALE);
    equalizeHist(image,img2);
}

void MainWindow::on_pushButton_2_clicked()
{
    imshow("Chosen image",image);
}

void MainWindow::on_pushButton_3_clicked()
{
    imshow("Equalized image",img2);
}

void MainWindow::on_pushButton_4_clicked()
{
    int n = image.rows;
    int m = image.cols;
    Mat img;
    cv::resize(image, img, Size(), 1, 1, INTER_CUBIC);
    for(int i=0;i<image.rows;i+=3) {
        for(int j=0;j<image.cols;j+=3) {
            uchar mx = 0;
            for(int ii = i;ii<=min(i+2, n);ii++) {
                for(int jj=j;jj<=min(j+2, m);jj++) {
                    uchar x = img.at<uchar>(ii,jj);
                    mx = max(x, mx);
                }
            }
            for(int ii = i;ii<=min(i+2, n);ii++) {
                for(int jj=j;jj<=min(j+2, m);jj++) {
                    img.at<uchar>(ii,jj) = mx;
                }
            }
        }
    }
    imshow("Maximum filter", image);
}

void MainWindow::on_pushButton_5_clicked()
{
    int n = image.rows;
    int m = image.cols;
    Mat img;
    cv::resize(image, img, Size(), 1, 1, INTER_CUBIC);
    for(int i=0;i<image.rows;i+=3) {
        for(int j=0;j<image.cols;j+=3) {
            uchar mx = 0;
            for(int ii = i;ii<=min(i+2, n);ii++) {
                for(int jj=j;jj<=min(j+2, m);jj++) {
                    uchar x = img.at<uchar>(ii,jj);
                    mx = min(x, mx);
                }
            }
            for(int ii = i;ii<=min(i+2, n);ii++) {
                for(int jj=j;jj<=min(j+2, m);jj++) {
                    img.at<uchar>(ii,jj) = mx;
                }
            }
        }
    }
    imshow("Minimum filter", image);
}

void MainWindow::on_pushButton_6_clicked()
{
    int n = image.rows;
    int m = image.cols;
    vector <uchar> v;
    Mat img;
    cv::resize(image, img, Size(), 1, 1, INTER_CUBIC);
    for(int i=0;i<image.rows;i+=3) {
        for(int j=0;j<image.cols;j+=3) {
            uchar mx = 0;
            v.clear();
            for(int ii = i;ii<=min(i+2, n);ii++) {
                for(int jj=j;jj<=min(j+2, m);jj++) {
                    uchar x = img.at<uchar>(ii,jj);
                    v.push_back(x);
                }
            }
            sort(v.begin(),v.end());
            mx = v[v.size()/2];
            for(int ii = i;ii<=min(i+2, n);ii++) {
                for(int jj=j;jj<=min(j+2, m);jj++) {
                    img.at<uchar>(ii,jj) = mx;
                }
            }
        }
    }
    imshow("Minimum filter", image);
}
