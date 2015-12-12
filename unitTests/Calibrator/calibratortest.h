#ifndef CALIBRATORTEST_H
#define CALIBRATORTEST_H

#include <QtTest>
#include <QDir>
#include <commons.h>
#include "calibrator.h"

class CalibratorTest : public QObject
{
    Q_OBJECT
public:
    CalibratorTest();

private Q_SLOTS:
    void calibrateTests ();
    void loadTests      ();
    void getTest        ();
    void saveTest       ();

private:
    bool calibrateTest  (QString calibSetDirPath, Size chessboardSize);
    bool loadTest       (QString calibFilePath);

    void initPatternKandD   (Mat &k, Mat &d);
};

#endif // CALIBRATORTEST_H
