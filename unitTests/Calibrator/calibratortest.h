#ifndef CALIBRATORTEST_H
#define CALIBRATORTEST_H

#include <QtTest>
#include "calibrator.h"

class CalibratorTest : public QObject
{
    Q_OBJECT
public:
    CalibratorTest();

private Q_SLOTS:
    void calibrateTest1();
    void calibrateTest2();
    void loadTest1();
    void loadTest2();
    void getTest();
    void saveTest();

private:
    bool isMatEqual         (Mat &mat1, Mat &mat2);
    void initPatternKandD   (Mat &k, Mat &d);

//    const QString calibParamFilePath {QDir::currentPath()+"/../../Calibrator/calibParam.yml"};
//    const QString calibImgSetDirPath {QDir::currentPath()+"/../../Calibrator/calibSet"};

    const QString calibParamFilePath {"/../../Calibrator/calibParam.yml"};
    const QString calibImgSetDirPath {"/../../Calibrator/calibSet"};

};

#endif // CALIBRATORTEST_H
