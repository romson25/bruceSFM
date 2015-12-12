#include "calibratortest.h"

CalibratorTest::CalibratorTest      ()
{}

void CalibratorTest::calibrateTests ()
{
    const QString   validCalibSetDirPath = "../../Calibrator/calibSet";
    const QString invalidCalibSetDirPath = "../../invalidPath/calibSet";
    const Size      validChessboardSize  = Size(9,6);
    const Size    invalidChessboardSize  = Size(6,3);

    QVERIFY(  calibrateTest(  validCalibSetDirPath,   validChessboardSize) );
    QVERIFY( !calibrateTest(invalidCalibSetDirPath,   validChessboardSize) );
    QVERIFY( !calibrateTest(  validCalibSetDirPath, invalidChessboardSize) );
    QVERIFY( !calibrateTest(invalidCalibSetDirPath, invalidChessboardSize) );
}
void CalibratorTest::loadTests      ()
{
    const QString   validCalibParamFilePath = "../../Calibrator/calibParam.yml";
    const QString invalidCalibParamFilePath = "../../invalidPath/calibParam.yml";

    QVERIFY(  loadTest(  validCalibParamFilePath) );
    QVERIFY( !loadTest(invalidCalibParamFilePath) );
}
void CalibratorTest::getTest        ()
{
    //--pytanie brzmi jak napisać unit test dla getterów i setterów?
}
void CalibratorTest::saveTest       ()
{
    const QString calibParamFilePath = "../../Calibrator/calibParam.yml";

//--załaduj plik kalibracyjny
    Calibrator calibrator;
    calibrator.load(calibParamFilePath);

//--zapisz go pod ścieżką path
    QString path = "testCalibFile.yml";
    calibrator.save(path);

//--sprawdź czy plik został stworzony
    QFile file(path);
    QVERIFY( file.exists() );

    qDebug()<<"Sprawdzam jedynie czy plik został zapisany, a nie czy jego zawartość jest poprawna";
    //TODO: jak sprawdzić działanie savera bez użycia loadera ?!
}

bool CalibratorTest::calibrateTest  (QString calibSetDirPath, Size chessboardSize)
{
//--stwórz listę wszystkich plików w tym folderze sortując po dacie modyfikacji
    QDir dir(calibSetDirPath);
    QStringList imgNameList(dir.entryList(QDir::Files, QDir::Time));
    QVector<Mat> images;

//--załaduj zestaw zdjęć do wektora
    foreach (QString imageName, imgNameList)
    {
        QString absoluteFilePath(dir.absolutePath()+"/"+imageName);
        Mat img = imread(absoluteFilePath.toStdString(), IMREAD_GRAYSCALE);
        images.push_back(img);
    }

//--oblicz calibMatrix oraz distCoeff
    Calibrator calibrator;
    calibrator.calibrate(images, chessboardSize);
    Mat k, d;
    calibrator.get(k, d);

//--ustaw macierze wzorcowe correctK i correctD
    Mat correctK, correctD;
    initPatternKandD(correctK, correctD);

//--porównaj otrzymane macierze z macierzami wzorcowymi
    bool equalK = Commons::isMatEqual(k, correctK);
    bool equalD = Commons::isMatEqual(d, correctD);

    return equalK && equalD;
}
bool CalibratorTest::loadTest       (QString calibFilePath)
{
//--wczytaj plik kalibracyjny
    Calibrator calibrator;
    calibrator.load(calibFilePath);

//--zapisz zawarte w nim macierze calibMatrix oraz distCoeff
    Mat k, d;
    calibrator.get(k, d);

//--przygotuj macierze wzorcowe
    Mat correctK, correctD;
    initPatternKandD(correctK, correctD);

//--porównaj odczytane macierze z macierzami wzorcowymi
    bool validK = Commons::isMatEqual(k, correctK);
    bool validD = Commons::isMatEqual(d, correctD);

    return validK && validD;
}

void CalibratorTest::initPatternKandD   (Mat &k, Mat &d)
{
    float kData[3][3]= {{1257.184908297359, 0, 628.1002388099488},
                        {0, 1256.139852293813,  496.7439557156057},
                        {0., 0., 1.}};
    float dData[1][5]= {0.2123359783129842, -1.22688007306083, -0.003497250906871663, 0.003423705590830523,  1.618594160498801};

    Mat k1 = Mat(3, 3, CV_32FC1, &kData);
    Mat d1 = Mat(1, 5, CV_32FC1, &dData);

    k1.convertTo(k, CV_32FC1);
    d1.convertTo(d, CV_32FC1);

    /* TODO: zagadka brzmi:
     *
     * Jeżeli zamienię:


    Mat k1 = Mat(3, 3, CV_32FC1, &kData);   |
    Mat d1 = Mat(1, 5, CV_32FC1, &dData);   |
                                            |-> na      k = Mat(3, 3, CV_32FC1, &kData);
    k1.convertTo(k, CV_32FC1);              |           d = Mat(1, 5, CV_32FC1, &dData);
    d1.convertTo(d, CV_32FC1);              |

    to dlaczego po wyjściu z funkcji k i d będą wypełnione przypadkowymi liczbami?!

     */
}

QTEST_APPLESS_MAIN(CalibratorTest)
