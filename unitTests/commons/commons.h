#ifndef Commons_H
#define Commons_H

#include "opencv2/core.hpp"
#include <QtMath>

using namespace cv;
using namespace std;

class Commons
{
public:
    Commons();

    static bool isKeypointsEqual    (const KeyPoint &kp1,
                                     const KeyPoint &kp2);

    static bool isKeypointsEqual    (const vector<KeyPoint> &vkp1,
                                     const vector<KeyPoint> &vkp2);

    static bool isMatEqual          (const Mat &mat1,
                                     const Mat &mat2);

    static bool isMatchesEqual      (const vector<DMatch> &matches1,
                                     const vector<DMatch> &matches2);

private:
    static bool compareKeypoints    (const KeyPoint &kp1, const KeyPoint &kp2);
};

#endif // Commons_H
