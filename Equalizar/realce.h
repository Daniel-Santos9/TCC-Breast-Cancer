#ifndef REALCE_H
#define REALCE_H


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
using namespace cv;


class realce
{
public:
    realce();
    ~realce();
};


const int reta_simples = 0;
const int logaritimica = 1;
const int exponencial  = 2;
const int negativa     = 3;

float truncar(float value);

Mat Realce(int type, Mat img, float contraste = 0, float brilho = 0, float y = 0);

#endif // REALCE_H
