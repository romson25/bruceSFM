#ifndef Matcher_H_
#define Matcher_H_

#include <QObject>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>

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


  void robustMatch  (vector<DMatch>& matches,
                     const Mat& img1descriptors,
                     const Mat& img2descriptors);

private:
  int ratioTest     (vector<vector<DMatch> > &matches);

  void symmetryTest (const vector<vector<DMatch> >& matches1,
                     const vector<vector<DMatch> >& matches2,
                     vector<DMatch>& symMatches );

  Ptr<FeatureDetector>      detector    {ORB::create()};
  Ptr<DescriptorExtractor>  extractor   {ORB::create()};
  Ptr<DescriptorMatcher>    matcher     {new BFMatcher(NORM_HAMMING2, false)};

  float ratio;
};

#endif /* Matcher_H_ */
