#ifndef IOPROCESSORTEST_H
#define IOPROCESSORTEST_H

#include <QtTest>
#include "ioprocessor.h"

class IOProcessorTest : public QObject
{
    Q_OBJECT
public:
    IOProcessorTest();

private Q_SLOTS:
    void loadImagesTests    ();

private:
    bool loadImagesTest     (QString dirPath);
};

#endif // IOPROCESSORTEST_H
