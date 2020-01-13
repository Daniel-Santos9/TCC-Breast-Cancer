#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/features2d.hpp>

using namespace std;
using namespace cv;

void Extrai_pontos(Mat img, int x, int y, int *pontos){
    // i = 80 / j = 77
    int i=x, j=y, cont=0, maior=0, jmaior1=0;
    while(img.at<uchar>(i,j) <50){

        while(img.at<uchar>(i,j) < 50){
            cont++;
            j++;
        }
        if(cont>maior){
            maior=cont;
            jmaior1=j;
        }
        cont=0;
         i++;
         j=y;
    }
    i=x; cont=0; j=y;
    while(img.at<uchar>(i,j) < 50){

        while(img.at<uchar>(i,j) < 50){
            cont++;
            j++;
        }
        if(cont>maior){
            maior=cont;
            jmaior1=j;
        }
        cont=0;
         i--;
         j=y;
    }

//    for(int h=0; h<img.rows;h++){
//        img.at<uchar>(h,jmaior1) = 0;
//    }

    i=x; cont=0; j=y; maior=0;
    int jmaior2=0;
    while(img.at<uchar>(i,j) <50){

        while(img.at<uchar>(i,j) < 50){
            cont++;
            j--;
        }
        if(cont>maior){
            maior=cont;
            jmaior2=j;
        }
        cont=0;
         i++;
         j=y;
    }
    i=x; cont=0; j=y;
    while(img.at<uchar>(i,j) < 50){

        while(img.at<uchar>(i,j) < 50){
            cont++;
            j--;
        }
        if(cont>maior){
            maior=cont;
            jmaior2=j;
        }
        cont=0;
         i--;
         j=y;
    }

//    for(int h=0; h<img.rows;h++){
//        img.at<uchar>(h,jmaior2) = 0;
//    }

    i=x; cont=0; j=y; maior=0;
    int imaior2=0;
    while(img.at<uchar>(i,j) <50){

        while(img.at<uchar>(i,j) < 50){
            cont++;
            i++;
        }
        if(cont>maior){
            maior=cont;
            imaior2=i;
        }
        cont=0;
         j++;
         i=x;
    }
    i=x; cont=0; j=y;
    while(img.at<uchar>(i,j) < 50){

        while(img.at<uchar>(i,j) < 50){
            cont++;
            i++;
        }
        if(cont>maior){
            maior=cont;
            imaior2=i;
        }
        cont=0;
         j--;
         i=x;
    }

//    for(int h=0; h<img.rows;h++){
//        img.at<uchar>(imaior2,h) = 0;
//    }

    i=x; cont=0; j=y; maior=0;
    int imaior1=0;
    while(img.at<uchar>(i,j) <50){

        while(img.at<uchar>(i,j) < 50){
            cont++;
            i--;
        }
        if(cont>maior){
            maior=cont;
            imaior1=i;
        }
        cont=0;
         j++;
         i=x;
    }
    i=x; cont=0; j=y;
    while(img.at<uchar>(i,j) < 50){

        while(img.at<uchar>(i,j) < 50){
            cont++;
            i--;
        }
        if(cont>maior){
            maior=cont;
            imaior1=i;
        }
        cont=0;
         j--;
         i=x;
    }

//    for(int h=0; h<img.rows;h++){
//        img.at<uchar>(imaior1,h) = 0;
//    }
//    cout<<imaior1<<endl;
//    cout<<imaior2<<endl;

    pontos[0] = imaior1;
    pontos[1] = imaior2;
    pontos[2] = jmaior1;
    pontos[3] = jmaior2;

//    namedWindow("img");
//    imshow("img",img);
//    waitKey(0);
//    destroyAllWindows();

   // return pontos;

}
