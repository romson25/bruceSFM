#include "ioprocessor.h"

IOProcessor::IOProcessor(QObject *parent) : QObject(parent)
{

}

void IOProcessor::loadImages(QString dirPath, QVector<Mat> &images)
{
    QDir dir(dirPath);

//--jeżeli folder nie istnieje zakończ działanie funkcji
    if( !dir.exists() )
        return;

//--stwórz listę wszystkich plików sortując po czasie modyfikacji w tym folderze
    QStringList imgNameList(dir.entryList(QDir::Files, QDir::Time));

    foreach (QString imageName, imgNameList)
    {
        std::string absoluteFilePath(dirPath.toStdString()+"/"+imageName.toStdString());
        images.push_back(imread(absoluteFilePath,CV_LOAD_IMAGE_GRAYSCALE));

        //--zrezygnowałem z wstępnej analizy roszrzenia pliku
        //--przy założeniu że tylko pojedyncze pliki nie są zdjęciami
        //--takie zabezpieczenie uważam za prawidłowe

        if(images.last().empty())
            images.pop_back();

    }
}
