#include <math.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

const int MAX = 255;
const int MIN = 0;

using namespace cv;

float truncar(float value){
    float n;
    if(value > MAX){
        n = MAX;
    }else if(value < MIN){
        n = MIN;
    }else{
        n = value;
    }
    return n;
}

Mat Realce(int type, Mat img, float contraste = 0, float brilho = 0, float y = 0){
    Mat img2 = img.clone();
    for(int i=0; i < img.rows; i++){
        for(int j = 0;j < img.cols; j++){
            switch (type) {
                case 0:
                    img2.at<uchar>(i,j) = truncar(contraste*img.at<uchar>(i,j)+brilho);
                    break;
                case 1:
                    img2.at<uchar>(i,j) = truncar(contraste*log(1+img.at<uchar>(i,j)));
                    break;
                case 2:
                    img2.at<uchar>(i,j) = truncar(contraste*pow(img.at<uchar>(i,j)+0.01,y));
                    break;
                case 3:
                    img2.at<uchar>(i,j) = truncar(MAX-img.at<uchar>(i,j));
                    break;
                default:
                    img2.at<uchar>(i,j) = img.at<uchar>(i,j);
                    break;
            }
        }
    }
    return img2;
}


