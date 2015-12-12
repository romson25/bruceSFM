#include "ioprocessortest.h"

IOProcessorTest::IOProcessorTest()
{}

void IOProcessorTest::loadImagesTests   ()
{
    const QString validDirPath   = "../../extraData/testImageSet";
    const QString invalidDirPath = "../../badPath/testImageSet";

    QVERIFY(  loadImagesTest(validDirPath)   );
    QVERIFY( !loadImagesTest(invalidDirPath) );
}

bool IOProcessorTest::loadImagesTest    (QString dirPath)
{
//--wczytaj zdjęcia z folderu do wektora images
    QVector<Mat> images;
    IOProcessor io;
    io.loadImages(dirPath, images);

//--jeżeli wektor jest pusty zwróć false
    if(images.empty())
        return false;

//--sprawdź czy wczytane zdjęcia spełniają wszystkie kryteria
    bool validImagesLength  { images.length() == 2 };       //--powinny zostać załadowane dwa zdjęcia
    bool equalSize          { images.first().size == images.last().size };  //--o tym samym rozmiarze
    bool validImagesHight   { images.first().rows == 1600 };    //--tj. 2560px
    bool validImagesWidth   { images.first().cols == 2560 };    //--na 1600px
    bool correctLoaded      { validImagesLength && equalSize && validImagesHight && validImagesWidth };

    return correctLoaded;
}

QTEST_APPLESS_MAIN(IOProcessorTest)
