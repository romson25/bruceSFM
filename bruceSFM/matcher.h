#ifndef Matcher_H_
#define Matcher_H_

#include <QObject>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <iostream>
#include "brucesfm_global.h"

using namespace cv;
using namespace std;

class BRUCESFMSHARED_EXPORT Matcher : public QObject
{
    Q_OBJECT
public:
  explicit Matcher(QObject *parent = 0);

  void computeKeyPoints     (const Mat& image, vector<KeyPoint>& keypoints);
  void computeDescriptors   (const Mat& image, vector<KeyPoint>& keypoints, Mat& descriptors);

  int ratioTest     (vector<vector<DMatch> > &matches);

  void symmetryTest (const vector<vector<DMatch> >& matches1,
                     const vector<vector<DMatch> >& matches2,
                     vector<DMatch>& symMatches );

  void robustMatch  (const Mat& img, vector<DMatch>& matches, vector<KeyPoint>& keypointsNextImg,
                     const Mat& descriptorsPrevImg, Mat& descriptorsNextImg);

private:
  Ptr<FeatureDetector>      detector    {ORB::create()};
  Ptr<DescriptorExtractor>  extractor   {ORB::create()};
  Ptr<DescriptorMatcher>    matcher     {new BFMatcher(NORM_HAMMING2, true)};

  float ratio;
};

#endif /* Matcher_H_ */
