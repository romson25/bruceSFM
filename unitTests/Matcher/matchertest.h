#ifndef MATCHERTEST_H
#define MATCHERTEST_H

#include <QObject>
#include <QtTest>

#include "matcher.h"

class MatcherTest : public QObject
{
    Q_OBJECT
public:
    MatcherTest();

private Q_SLOTS:
    void computeKeyPointsTest1();
    void computeKeyPointsTest2();

    void computeDescriptorsTest1();
    void computeDescriptorsTest2();

    void robustMatchTest1();
    void robustMatchTest2();

private:
    bool isKeypointsEqual   (const KeyPoint &kp1, const KeyPoint &kp2);
    bool isMatEqual         (const Mat &mat1, const Mat &mat2);
    bool isMatchesEqual     (const vector<DMatch> &matches1, const vector<DMatch> &matches2);
};

#endif // MATCHERTEST_H
