#include "matchertest.h"

MatcherTest::MatcherTest()
{
    //TODO: testy powinny być niezależne od siebie, tylko ciekawe jak w tym przypadku to zrobić ?!
}

void MatcherTest::computeKeyPointsTests     ()
{
    const QString validImage       = "../../extraData/testImageSet/pen1.jpg";
    const QString invalidImage     = "../../extraData/testImageSet/pen2.jpg";
    const QString invalidPathImage = "../../extraData/badPath/pen1.jpg";

    QVERIFY(  computeKeyPointsTest( validImage )        );
    QVERIFY( !computeKeyPointsTest( invalidImage )      );
    QVERIFY( !computeKeyPointsTest( invalidPathImage )  );
}
void MatcherTest::computeDescriptorsTests   ()
{
    const QString validImage       = "../../extraData/testImageSet/pen1.jpg";
    const QString invalidImage     = "../../extraData/testImageSet/pen2.jpg";
    const QString invalidPathImage = "../../extraData/badPath/pen1.jpg";

    QVERIFY(  computeDescriptorsTest( validImage )        );
    QVERIFY( !computeDescriptorsTest( invalidImage )      );
    QVERIFY( !computeDescriptorsTest( invalidPathImage )  );
}
void MatcherTest::robustMatchTests          ()
{
    //--teoretycznie test 12 i 21 powinnien dać taki sam wynik, matchesy powinny być takie same
    //--i prawdopodobnie tak jest jednak są ułożone w innnej kolejności w wektorze i pliku
    //--a algorytm porównawczy nie uwzględnia dlatego uzna że 12 i 21 to zupełnie inne matchesy

    const QString validImage1       = "../../extraData/testImageSet/pen1.jpg";
    const QString validImage2       = "../../extraData/testImageSet/pen2.jpg";
    const QString invalidImage      = "../../extraData/badPath/toNiePng.png";
    const QString invalidPathImage  = "../../extraData/badPath/pen1.jpg";

    QVERIFY(  robustMatchTest( validImage1, validImage2 ) );
//    QVERIFY(  robustMatchTest( validImage2, validImage1 ) );

    QVERIFY( !robustMatchTest( validImage1, invalidImage ) );
    QVERIFY( !robustMatchTest( invalidImage, validImage1 ) );
    QVERIFY( !robustMatchTest( validImage2, invalidImage ) );
    QVERIFY( !robustMatchTest( invalidImage, validImage2 ) );

    QVERIFY( !robustMatchTest( invalidImage, invalidPathImage ) );
    QVERIFY( !robustMatchTest( invalidPathImage, validImage2  ) );

    QVERIFY( !robustMatchTest( invalidPathImage, validImage1 ) );
    QVERIFY( !robustMatchTest( invalidPathImage, validImage2 ) );
}

bool MatcherTest::computeKeyPointsTest  (QString imageAbsolutePath)
{
    Mat img = imread(imageAbsolutePath.toStdString(), IMREAD_GRAYSCALE);

//--odrzuć już na początku wszystkie nie poprawnie załadowane zdjęcia
    if(img.empty())
        return false;

//--oblicz keypointy
    vector<KeyPoint> keypoints;
    Matcher matcher;
    matcher.computeKeyPoints(img, keypoints);

//--zainicjuj poprawny zestaw keypointów sporządzony dla ../../extraData/testImageSet/pen1.jpg
    KeyPoint firstCorrectKeypoint   = KeyPoint(1442, 276, 31);
    KeyPoint lastCorrectKeypoint    = KeyPoint(1057.04, 146.91, 111.079);
    uint correctKeypointsNumber     = 500;

//--porównaj obliczone keypointy z przygotowanym zestawem
    bool equalKeypointsNumber   { keypoints.size() == correctKeypointsNumber };
    bool equalFirstKeypoints    { Commons::isKeypointsEqual(keypoints.front(), firstCorrectKeypoint) };
    bool equalLastKeypoints     { Commons::isKeypointsEqual(keypoints.back(), lastCorrectKeypoint) };

    return equalKeypointsNumber && equalFirstKeypoints && equalLastKeypoints;
}
bool MatcherTest::computeDescriptorsTest(QString imageAbsolutePath)
{
    Mat img = imread(imageAbsolutePath.toStdString(), IMREAD_GRAYSCALE);

//--odrzuć już na początku wszystkie nie poprawnie załadowane zdjęcia
    if(img.empty())
        return false;

//--oblicz keypointy i deskryptory
    vector<KeyPoint> keypoints;
    Mat descriptors;
    Matcher matcher;
    matcher.computeKeyPoints(img, keypoints);
    matcher.computeDescriptors(img, keypoints, descriptors);

//--wczytaj poprawny zestaw deskryptorów sporządzony dla ../../extraData/testImageSet/pen1.jpg
    FileStorage fs("../../extraData/MatcherSetCorrectDescriptors.yml", FileStorage::READ);
    Mat correctDescriptors;
    fs["descriptors"] >> correctDescriptors;
    fs.release();

//--porównaj obliczone deskryptory z przygotowanym zestawem
    return Commons::isMatEqual(descriptors, correctDescriptors);
}
bool MatcherTest::robustMatchTest       (QString image1AbsolutePath, QString image2AbsolutePath)
{
    Mat img1 = imread(image1AbsolutePath.toStdString(), IMREAD_GRAYSCALE);
    Mat img2 = imread(image2AbsolutePath.toStdString(), IMREAD_GRAYSCALE);

//--odrzuć już na początku wszystkie nie poprawnie załadowane zdjęcia
    if( img1.empty() || img2.empty())
        return false;

//--oblicz keypointy i deskryptory dla wczytanej pary zdjęć
    vector<KeyPoint> img1kp, img2kp;
    Mat img1desc, img2desc;
    Matcher matcher;
    matcher.computeKeyPoints(img1, img1kp);
    matcher.computeKeyPoints(img2, img2kp);
    matcher.computeDescriptors(img1, img1kp, img1desc);
    matcher.computeDescriptors(img2, img2kp, img2desc);

//--oblicz matches
    vector<DMatch> matches;
    matcher.robustMatch(matches, img1desc, img2desc);

//--wczytaj poprawny zestaw matches sporządzony dla ../../extraData/testImageSet/pen1.jpg
    FileStorage fs("../../extraData/MatcherSetCorrectMatches.yml", FileStorage::READ);
    vector<DMatch> correctMatches;
    fs["matches"] >> correctMatches;
    fs.release();

//--porównaj otrzymane matches z przygotowanym zestawem
    return Commons::isMatchesEqual(matches, correctMatches);
}

QTEST_APPLESS_MAIN(MatcherTest)
