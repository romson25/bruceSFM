#include "commons.h"

Commons::Commons()
{}

bool Commons::isKeypointsEqual  (const KeyPoint &kp1,
                                 const KeyPoint &kp2)
{
    return compareKeypoints(kp1, kp2);
}

bool Commons::isKeypointsEqual  (const vector<KeyPoint> &vkp1,
                                 const vector<KeyPoint> &vkp2)
{
//--zwróć false jeżeli wektory są puste lub mają różny rozmiar
    bool emptyVectors           { vkp1.empty() || vkp2.empty() };
    bool differentVectorsSize   { vkp1.size()  ==  vkp2.size() };

    if( emptyVectors || differentVectorsSize)
        return false;

//--porównaj wszystkie odpowiadające sobie keypointy
    for(int i=vkp1.size(); i==0; --i)
    {
        //--jeżeli którakolwiek para nie jest sobie równa zwróc false
//        if( !compareKeypoints( vkp1.at(i), vkp2.at(i) ) )
//            return false;
    }

    return true;
}

bool Commons::isMatEqual        (const Mat &mat1,
                                 const Mat &mat2)
{
//--porównać można tylko Mat o tych samych rozmiarach
    bool equalRows { (mat1.rows == mat2.rows) };
    bool equalCols { (mat1.cols == mat2.cols) };

    if( !equalCols || !equalRows )
        return false;

//--przekonwertuj do tych samych typów
    Mat a;
    mat1.convertTo(a, CV_32FC1);
    Mat b;
    mat2.convertTo(b, CV_32FC1);
    Mat c;

//--Mat c ma ten sam rozmiar co a i b,
//--jeżeli a(i,j) == b(i,j) wtedy c(i,j) jest równe 255 else 0
    compare(a, b, c, CMP_EQ);
//--więc jeżeli wszystkie elementy w c są nie zerowe, Mat a i Mat b są równe
    int rightCountNonZero = mat1.rows * mat1.cols;

    return (countNonZero(c) == rightCountNonZero);
}

bool Commons::isMatchesEqual    (const vector<DMatch> &matches1,
                                 const vector<DMatch> &matches2)
{
    bool matchesEmpty     { matches1.empty() || matches2.empty() };
    bool matchesEqualSize { matches1.size() == matches2.size() };

//--jeżeli którykolwiek z matches jest pusty lub oba nie mają tego samego rozmiaru
//--natychmiast wyjdź i zwróć false
    if( matchesEmpty || !matchesEqualSize)
        return false;

//--porównaj odpowiadające sobie wartości queryIdx oraz trainIdx
    for(uint i = 0; i<matches1.size(); i++)
    {
        //TODO: problem z odczytem i porównaniem wartości distance które są typu float
        bool isEqualQueryIdx { matches1.at(i).queryIdx == matches2.at(i).queryIdx };
        bool isEqualTrainIdx { matches1.at(i).trainIdx == matches2.at(i).trainIdx };

        if( !isEqualQueryIdx || !isEqualTrainIdx )
            return false;
    }

    return true;
}

bool Commons::compareKeypoints(const KeyPoint &kp1, const KeyPoint &kp2)
{
//    //--porównywanie floatów - hehe kto by pomyślał taki psikus hehe
//    //    bool equalX     { qAbs(kp1.pt.x - kp2.pt.x) < 0.01 };
//    //    bool equalY     { qAbs(kp1.pt.y - kp2.pt.y) < 0.01 };
//    //    bool equalSize  { qAbs(kp1.size - kp2.size) < 0.01 };
//    //-- zamiast zgadywać epsilon (wyżej 0.01) świadomie obcinam do liczb całkowitych

    bool equalX     { (int)kp1.pt.x == (int)kp2.pt.x };
    bool equalY     { (int)kp1.pt.y == (int)kp2.pt.y };
    bool equalSize  { (int)kp1.size == (int)kp2.size };
    bool equal      { equalX && equalY && equalSize };

    return equal;
}
