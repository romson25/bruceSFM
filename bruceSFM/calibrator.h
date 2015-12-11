#ifndef CALIBRATOR_H
#define CALIBRATOR_H

#include <QObject>
#include <QDebug>
#include <QDir>

#include <vector>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/ccalib.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>

#include "brucesfm_global.h"

using namespace cv;
using namespace std;

class BRUCESFMSHARED_EXPORT Calibrator : public QObject
{
    Q_OBJECT
public:
    explicit Calibrator(QObject *parent = 0);

signals:
    void calibrated(const Mat& k, const Mat& d);

public slots:
    void calibrate  (const QVector<Mat>& images, Size chessboardSize);
    void load       (QString calibParamFilePath);
    void save       (QString calibParamFilePath);
    void get        (Mat& k, Mat& d);

private:
    void clearPreviousData      ();
    void setObjectCorners       (Size boardSize);
    void addChessboardCorners   (const QVector<Mat>& images, Size chessboardSize);
    bool readyForCalibration    ();
    void checkCorrectness       ();
    Size chessboardImageSize    (const Mat& img);

    Mat k = Mat(3, 3, CV_32FC1);    //--camera matrix
    Mat d;                          //--distortion
    vector<Mat> rvecs, tvecs;       //--rotate and translate

    vector<vector<Point2f>> imagePoints;
    vector<vector<Point3f>> objectPoints;

    vector<Point3f> objectCorners;
};
#endif // CALIBRATOR_H
