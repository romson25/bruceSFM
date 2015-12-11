#include "calibrator.h"

Calibrator::Calibrator(QObject *parent) : QObject(parent)
{}

void Calibrator::calibrate  (const QVector<Mat>& images, Size chessboardSize)
{
    clearPreviousData();

    setObjectCorners(chessboardSize);
    addChessboardCorners(images, chessboardSize);

    if(readyForCalibration())
    {
        Size boardImgSize = chessboardImageSize(images.first());

        calibrateCamera(objectPoints, imagePoints, boardImgSize , k, d, rvecs, tvecs);
        checkCorrectness();
    }
    else
        qDebug()<<"Niewystarczająca ilość zdjęć szachownicy, macierz k nie obliczona";
}
void Calibrator::load       (QString filePath)
{
    clearPreviousData();

    FileStorage fs(filePath.toStdString(), FileStorage::READ);
    fs["cameraMatrix"]  >> k;
    fs["distCoeffs"]    >> d;
    fs.release();

    checkCorrectness();
}
void Calibrator::save       (QString filePath)
{
    if(k.empty() || d.empty())
        qDebug()<<"Macierze k lub/i d nie są obliczone, więc nie zostaną zapisane/a do pliku";
    else
    {
        FileStorage fs(filePath.toStdString(), FileStorage::WRITE);

        fs << "cameraMatrix" << k;
        fs << "distCoeffs" << d;

        fs.release();
    }
}
void Calibrator::get        (Mat& calibMatrix, Mat& distCoeff)
{
    calibMatrix = k;
    distCoeff = d;
}

void Calibrator::clearPreviousData      ()
{
    k.release();
    d.release();
    imagePoints.clear();
    objectPoints.clear();
    objectCorners.clear();
}
void Calibrator::setObjectCorners       (Size boardSize)
{
    for(int i = 0; i < boardSize.area(); i++)
        objectCorners.push_back(Point3f(i/boardSize.width, i%boardSize.width, 0.0f));
}
void Calibrator::addChessboardCorners   (const QVector<Mat>& images, Size boardSize)
{
    vector<Point2f> imageCorners;
    TermCriteria    criteria    = TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 30, 0.1);
    int             flags       = CV_CALIB_CB_ADAPTIVE_THRESH + CV_CALIB_CB_FILTER_QUADS + CV_CALIB_CB_FAST_CHECK;

    foreach (Mat img, images)
    {
        if(!img.empty())
        {
            if(findChessboardCorners(img, boardSize, imageCorners, flags))
            {
                cornerSubPix(img, imageCorners, Size(5,5), Size(-1,-1), criteria);

                objectPoints.push_back(objectCorners);
                imagePoints.push_back(imageCorners);
            }
            else
                qDebug()<<"Nie znaleziono szachownicy na zdjęciu";
        }
        else
            qDebug()<<"wczytane zdjęcie szachownicy jest puste";
    }
}
bool Calibrator::readyForCalibration    ()
{
    return (imagePoints.size() >= 10); // vector imagePoints zawiera conajmniej 10 zdjeć z szachownicą
}
void Calibrator::checkCorrectness       ()
{
    if(k.empty() || d.empty())
        qDebug()<<"błąd podczas procesu kalibracji, macierze k, d są puste";
    else
        emit calibrated(k, d);
}
Size Calibrator::chessboardImageSize    (const Mat& img)
{
    int rows = img.rows;
    int cols = img.cols;

    return Size(cols, rows);
}



