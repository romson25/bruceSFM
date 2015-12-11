#include "matchertest.h"

MatcherTest::MatcherTest()
{
    //TODO: testy powinny być niezależne od siebie, tylko ciekawe jak w tym przypadku to zrobić ?!
}

void MatcherTest::computeKeyPointsTest1     ()
{
    Matcher matcher {};

    Mat img = imread("../../extraData/testImageSet/pen1.jpg", IMREAD_GRAYSCALE);
    vector<KeyPoint> keypoints {};

    matcher.computeKeyPoints(img, keypoints);

    KeyPoint firstCorrect   = KeyPoint(1442, 276, 31);
    KeyPoint lastCorrect    = KeyPoint(1057.04, 146.91, 111.079);

    bool isCorrectKeypointsNumber   { keypoints.size() == 500 };
    bool isEqualsFirstKeypoints     { isKeypointsEqual(keypoints.front(), firstCorrect) };
    bool isEqualsLastKeypoints      { isKeypointsEqual(keypoints.back(), lastCorrect) };

    QVERIFY( (isCorrectKeypointsNumber && isEqualsFirstKeypoints && isEqualsLastKeypoints) );
}
void MatcherTest::computeKeyPointsTest2     ()
{
    Mat img = imread("../../extraData/testImageSet/pen2.png", IMREAD_GRAYSCALE);
    vector<KeyPoint> keypoints;
    if(keypoints.empty())
        return;

    Matcher matcher;
    matcher.computeKeyPoints(img, keypoints);

    KeyPoint firstCorrect   = KeyPoint(1442, 276, 31);
    KeyPoint lastCorrect    = KeyPoint(1057.04, 146.91, 111.079);

    bool isCorrectKeypointsNumber   {keypoints.size() == 500};
    bool isEqualsFirstKeypoints     { isKeypointsEqual(keypoints.front(), firstCorrect) };
    bool isEqualsLastKeypoints      { isKeypointsEqual(keypoints.back(), lastCorrect) };

    QVERIFY(!isCorrectKeypointsNumber || !isEqualsFirstKeypoints || !isEqualsLastKeypoints);
}
void MatcherTest::computeDescriptorsTest1   ()
{
    vector<KeyPoint> keypoints;
    Mat descriptors;
    Mat img = imread("../../extraData/testImageSet/pen1.jpg", IMREAD_GRAYSCALE);

    Matcher matcher;
    matcher.computeKeyPoints(img, keypoints);
    matcher.computeDescriptors(img, keypoints, descriptors);

    FileStorage fsr("../../extraData/MatcherSetCorrectDescriptors.yml", FileStorage::READ);
    Mat correctDescriptors;
    fsr["descriptors"] >> correctDescriptors;
    fsr.release();

    cout<<"^^^^^^^^^^correct^^^^^^^^^^^\n"<<correctDescriptors<<endl;
    cout<<"\n^^^^^^^^^^computed^^^^^^^^^^^\n"<<descriptors<<endl;
    QVERIFY( isMatEqual(descriptors, correctDescriptors) );
}
void MatcherTest::computeDescriptorsTest2   ()
{
    //--załadowane zdjęcie nie pasuje do przygotowanego zestawu
    //--dlatego wynik isMatEqual powinien być negatywny

    //--przygotuj zmienne
    vector<KeyPoint> keypoints;
    Mat descriptors;
    Mat img = imread("../../extraData/testImageSet/pen2.jpg", IMREAD_GRAYSCALE);

    //--oblicz keypointy i descriptory
    Matcher matcher;
    matcher.computeKeyPoints(img, keypoints);
    matcher.computeDescriptors(img, keypoints, descriptors);

    //--wczytaj poprawny zestaw danych
    FileStorage fsr("../../extraData/MatcherSetCorrectDescriptors.yml", FileStorage::READ);
    Mat correctDescriptors;
    fsr["descriptors"] >> correctDescriptors;
    fsr.release();

    //--porównaj otrzymane wyniki z przygotowanym zestawem
    QVERIFY( !isMatEqual(descriptors, correctDescriptors) );
}
void MatcherTest::robustMatchTest1          ()
{
    Mat img1 = imread("../../extraData/testImageSet/pen1.jpg", IMREAD_GRAYSCALE);
    Mat img2 = imread("../../extraData/testImageSet/pen2.jpg", IMREAD_GRAYSCALE);
    vector<KeyPoint> img1kp{}, img2kp{};
    Mat img1desc{}, img2desc{};

    Matcher matcher;
    matcher.computeKeyPoints(img1, img1kp);
    matcher.computeKeyPoints(img2, img2kp);
    matcher.computeDescriptors(img1, img1kp, img1desc);
    matcher.computeDescriptors(img2, img2kp, img2desc);

    vector<DMatch> matches {};
    matcher.robustMatch(matches, img1desc, img2desc);

    FileStorage fs("../../extraData/MatcherSetCorrectMatches", FileStorage::READ);
    vector<DMatch> correctMatches{};
    fs << "matches" <<correctMatches;
    fs.release();

    QVERIFY( isMatchesEqual(matches, correctMatches) );
}
void MatcherTest::robustMatchTest2          ()
{
    Mat img1 = imread("../../extraData/testImageSet/pen2.jpg", IMREAD_GRAYSCALE);
    Mat img2 = imread("../../extraData/testImageSet/badName.jpg", IMREAD_GRAYSCALE);
    vector<KeyPoint> img1kp{}, img2kp{};
    Mat img1desc{}, img2desc{};

    Matcher matcher;
    matcher.computeKeyPoints(img1, img1kp);
    matcher.computeKeyPoints(img2, img2kp);
    matcher.computeDescriptors(img1, img1kp, img1desc);
    matcher.computeDescriptors(img2, img2kp, img2desc);

    vector<DMatch> matches {};
    matcher.robustMatch(matches, img1desc, img2desc);

    FileStorage fs("../../extraData/MatcherSetCorrectMatches", FileStorage::READ);
    vector<DMatch> correctMatches{};
    fs << "matches" <<correctMatches;
    fs.release();

    QVERIFY( isMatchesEqual(matches, correctMatches) );
}

bool MatcherTest::isKeypointsEqual  (const KeyPoint &kp1, const KeyPoint &kp2)
{
    //--porównywanie floatów - hehe ktoby pomyślał taki psikus hehe

    bool isEqualX { qAbs(kp1.pt.x - kp2.pt.x) < 0.01 };
    bool isEqualY { qAbs(kp1.pt.y - kp2.pt.y ) < 0.01 };
    bool isEqualSize { qAbs(kp1.size - kp2.size) < 0.01 };

    return isEqualX && isEqualY && isEqualSize;
}
bool MatcherTest::isMatEqual        (const Mat &mat1, const Mat &mat2)
{
//--ta sama funkcja jest w CalibratorTest, po co pisać ją dwa razy ?!

//--porównać można tylko Mat o tych samych rozmiarach
    bool isEqualRows {mat1.rows == mat2.rows};
    bool isEqualCols {mat1.cols == mat2.cols};

    if( !isEqualCols || !isEqualRows )
        return false;
//--przekonwertuj do tych samych typów
    Mat a;
    mat1.convertTo(a, CV_32FC1);
    Mat b;
    mat2.convertTo(b, CV_32FC1);
    Mat c;

//--jeżeli odpowiadające sobie elementy są równe element w C.at(i,j) == 255, jeżeli nie jest = 0
    compare(a, b, c, CMP_EQ);
//--ilość elementów nie zerowych musi być równa ilości elementów macierzy
    int rightCountNonZero = mat1.rows * mat1.cols;

    return countNonZero(c) == rightCountNonZero;
}
bool MatcherTest::isMatchesEqual    (const vector<DMatch> &matches1, const vector<DMatch> &matches2)
{
    if(matches1.size() != matches2.size())
        return false;

    for(uint i = 0; i <matches1.size(); i++)
    {
        bool isEqualDistance { matches1.at(i).distance == matches2.at(i).distance };
        bool isEqualQueryIdx { matches1.at(i).queryIdx == matches2.at(i).queryIdx };
        bool isEqualTrainIdx { matches1.at(i).trainIdx == matches2.at(i).trainIdx };

        if( !isEqualDistance || !isEqualQueryIdx || !isEqualTrainIdx)
            return false;
    }

    return true;
}

QTEST_APPLESS_MAIN(MatcherTest)
