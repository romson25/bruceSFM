#include "calibratortest.h"

CalibratorTest::CalibratorTest      ()
{
    //TODO: zamiast pisać kilka testów dla różnych zestawów danych
    // lepiej byłoby użyć jednego testu z przygotowanym zestawem
    // i zwyczajnie go wczytać, następnie sprawdzić wyniki
}

void CalibratorTest::calibrateTest1 ()
{
    Calibrator calibrator;
    QVector<Mat> images;
    Size boardSize;
    Mat k, d;

    calibrator.calibrate(images, boardSize);
    calibrator.get(k, d);

    QVERIFY(k.empty() && d.empty());
}
void CalibratorTest::calibrateTest2 ()
{
//--załaduj zestaw zdjęć do wektora
    QVector<Mat> images;
    QDir dir(calibImgSetDirPath);
    qDebug()<<"Jestem w: "<<dir.absolutePath();
    QStringList imgNameList(dir.entryList(QDir::Files, QDir::Time));

    foreach (QString imageName, imgNameList)
    {
        QString absoluteFilePath(dir.absolutePath()+"/"+imageName);
        QFile file(absoluteFilePath);
        Mat img = imread(absoluteFilePath.toStdString(), IMREAD_GRAYSCALE);
        images.push_back(img);
        qDebug()<<"image.path: "<<absoluteFilePath;
    }

//--oblicz calibMatrix oraz distCoeff
    Size boardSize = Size(9,6);
    Calibrator calibrator;
    calibrator.calibrate(images, boardSize);
    Mat k, d;
    calibrator.get(k, d);

//--ustaw macierze wzorcowe correctK i correctD
    Mat correctK, correctD;
    initPatternKandD(correctK, correctD);

//--porównaj otrzymane macierze z macierzami wzorcowymi
    QVERIFY( isMatEqual(k, correctK) );
    QVERIFY( isMatEqual(d, correctD) );
}
void CalibratorTest::loadTest1      ()
{
    Calibrator calibrator;
    calibrator.load("bobo.yml");

    Mat k, d;
    calibrator.get(k, d);

    QVERIFY(k.empty() && d.empty());
}
void CalibratorTest::loadTest2      ()
{
//--wczytaj plik kalibracyjny
    Calibrator calibrator;
    calibrator.load(calibParamFilePath);

//--zapisz zapisane w nim macierze calibMatrix oraz distCoeff
    Mat k, d;
    calibrator.get(k, d);

//--przygotuj macierze wzorcowe
    Mat correctK, correctD;
    initPatternKandD(correctK, correctD);

//--porównaj je
    QVERIFY( isMatEqual(k, correctK));
    QVERIFY( isMatEqual(d, correctD));
}
void CalibratorTest::getTest        ()
{
    //--pytanie brzmi jak napisać unit test dla getterów i setterów?
}
void CalibratorTest::saveTest       ()
{
    Calibrator calibrator;
    calibrator.load(calibParamFilePath);
    QString path {"testCalibFile.yml"};
    calibrator.save(path);

    qDebug()<<"Sprawdzam jedynie czy plik został zapisany, a nie czy jego zawartość jest poprawna";

    QFile file(path);
    QVERIFY( file.exists() );

    //TODO: jak sprawdzić działanie savera bez użycia loadera ?!
}

bool CalibratorTest::isMatEqual         (Mat &mat1, Mat &mat2)
{
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
