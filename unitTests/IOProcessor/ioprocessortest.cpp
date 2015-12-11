#include "ioprocessortest.h"

IOProcessorTest::IOProcessorTest()
{

}

void IOProcessorTest::loadImagesTest1   ()
{
    IOProcessor io{};
    QVector<Mat> images;
    io.loadImages("../../extraData/testImageSet", images);

    bool isCorrectLoaded {};

    if(images.length() == 2)                            //--powinny zostać załadowane dwa zdjęcia
        if(images.first().size == images.last().size)   //--o tym samym rozmiarze
            if(images.first().cols == 2560)             //--tj. 2560px
                if(images.first().rows == 1600)         //--na 1600px
                    isCorrectLoaded = true;

    QVERIFY(isCorrectLoaded);
}
void IOProcessorTest::loadImagesTest2   ()
{
    IOProcessor io{};
    QVector<Mat> images;
    io.loadImages("../../extraData/badPath", images);

    QVERIFY(images.length() == 0);
}

QTEST_APPLESS_MAIN(IOProcessorTest)
