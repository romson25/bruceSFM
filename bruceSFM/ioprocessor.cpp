#include "ioprocessor.h"

IOProcessor::IOProcessor(QObject *parent) : QObject(parent)
{

}

void IOProcessor::loadImages(QString dirPath, QVector<Mat> &images)
{
    QDir dir(dirPath);
    QStringList imgNameList(dir.entryList(QDir::Files, QDir::Time));

    foreach (QString imageName, imgNameList)
    {
        std::string absoluteFilePath(dirPath.toStdString()+"/"+imageName.toStdString());
        images.push_back(imread(absoluteFilePath,CV_LOAD_IMAGE_GRAYSCALE));

        if(images.last().empty())
            images.pop_back();

        //--zrezygnowałem z wstępnej analizy roszrzenia pliku
        //--przy założeniu że tylko pojedyncze pliki nie są zdjęciami
        //--takie zabezpieczenie uważam za prawidłowe
    }
}
