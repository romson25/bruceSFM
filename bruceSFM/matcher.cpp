#include "matcher.h"

Matcher::Matcher(QObject *parent) : QObject(parent), ratio{0.8f}
{}

void Matcher::computeKeyPoints        (const Mat& image, vector<KeyPoint>& keypoints)
{
  detector->detect(image, keypoints);
}
void Matcher::computeDescriptors      (const Mat& image, vector<KeyPoint>& keypoints, Mat& descriptors)
{
  extractor->compute(image, keypoints, descriptors);
}

int Matcher::ratioTest        (vector<vector<DMatch> > &matches)
{
    // Clear matches for which NN ratio is > than threshold
    // return the number of removed points
    // (corresponding entries being cleared,
    // i.e. size will be 0)

  int removed = 0;
  // for all matches
  for ( vector<vector<DMatch> >::iterator
        matchIterator= matches.begin(); matchIterator!= matches.end(); ++matchIterator)
  {
    // if 2 NN has been identified
    if (matchIterator->size() > 1)
    {
      // check distance ratio
      if ((*matchIterator)[0].distance / (*matchIterator)[1].distance > ratio)
      {
        matchIterator->clear(); // remove match
        removed++;
      }
    }
    else
    { // does not have 2 neighbours
      matchIterator->clear(); // remove match
      removed++;
    }
  }
  return removed;
}

void Matcher::symmetryTest    (const vector<vector<DMatch> >& matches1, const vector<vector<DMatch> >& matches2,
                               vector<DMatch>& symMatches)
{
// Insert symmetrical matches in symMatches vector

  // for all matches image 1 -> image 2
   for (vector<vector<DMatch> >::const_iterator
       matchIterator1 = matches1.begin(); matchIterator1 != matches1.end(); ++matchIterator1)
   {

      // ignore deleted matches
      if (matchIterator1->empty() || matchIterator1->size() < 2)
         continue;

      // for all matches image 2 -> image 1
      for (vector<vector<DMatch> >::const_iterator
          matchIterator2 = matches2.begin(); matchIterator2 != matches2.end(); ++matchIterator2)
      {
        // ignore deleted matches
        if (matchIterator2->empty() || matchIterator2->size() < 2)
           continue;

        // Match symmetry test
        if ((*matchIterator1)[0].queryIdx == (*matchIterator2)[0].trainIdx &&
            (*matchIterator2)[0].queryIdx == (*matchIterator1)[0].trainIdx)
        {
            // add symmetrical match
            DMatch correctMatch = DMatch(   (*matchIterator1)[0].queryIdx,
                                            (*matchIterator1)[0].trainIdx,
                                            (*matchIterator1)[0].distance   );
            symMatches.push_back(correctMatch);
            break; // next match in image 1 -> image 2
        }
      }
   }

}

void Matcher::robustMatch     (const Mat& img, vector<DMatch>& matches, vector<KeyPoint>& keypointsNextImg,
                               const Mat& descriptorsPrevImg, Mat& descriptorsNextImg)
{
  // 1a. Detection of the ORB features
  this->computeKeyPoints(img, keypointsNextImg);

  // 1b. Extraction of the ORB descriptors
  this->computeDescriptors(img, keypointsNextImg, descriptorsNextImg);

  // 2. Match the two image descriptors
  vector<vector<DMatch> > matches12, matches21;

  // 2a. From image 1 to image 2
  matcher->knnMatch(descriptorsNextImg, descriptorsPrevImg, matches12, 2); // return 2 nearest neighbours

  // 2b. From image 2 to image 1
  matcher->knnMatch(descriptorsPrevImg, descriptorsNextImg, matches21, 2); // return 2 nearest neighbours

  // 3. Remove matches for which NN ratio is > than threshold
  // clean image 1 -> image 2 matches
  ratioTest(matches12);
  // clean image 2 -> image 1 matches
  ratioTest(matches21);

  // 4. Remove non-symmetrical matches
  symmetryTest(matches12, matches21, matches);
}

