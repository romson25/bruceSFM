#ifndef MATCHERTEST_H
#define MATCHERTEST_H

#include <QObject>
#include <QtTest>

#include "matcher.h"
#include <commons.h>

class MatcherTest : public QObject
{
    Q_OBJECT
public:
    MatcherTest();

private Q_SLOTS:
    void computeKeyPointsTests  ();
    void computeDescriptorsTests();
    void robustMatchTests       ();

private:
    bool computeKeyPointsTest   (QString imageAbsolutePath);
    bool computeDescriptorsTest (QString imageAbsolutePath);
    bool robustMatchTest        (QString image1AbsolutePath, QString image2AbsolutePath);
};

#endif // MATCHERTEST_H
