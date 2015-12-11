#ifndef IOPROCESSOR_H
#define IOPROCESSOR_H

#include <QObject>
#include <QVector>
#include <QDir>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

class IOProcessor : public QObject
{
    Q_OBJECT
public:
    explicit IOProcessor(QObject *parent = 0);

signals:

public slots:
    void loadImages(QString dirPath, QVector<Mat>& images);
};

#endif // IOPROCESSOR_H
