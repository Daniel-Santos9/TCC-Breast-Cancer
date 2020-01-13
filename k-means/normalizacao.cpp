#include "cruzaFuncPonteiros.h"
#include "QTime"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "QString"
#include "normalizacao.h"

using namespace std;
double normaliza(double **val_descritores, double x, int row, int col, int d1, int d2){

    double y;
    //int d1 = 0, d2=1;
    double Xmin = retorna_xmin(val_descritores,row,col);
    double Xmax = retorna_xmax(val_descritores,row,col);

    y = (((x - Xmin)*(d2 - d1)) /  (Xmax-Xmin))+ d1;

    return y;
}

double retorna_xmax(double **val_descritores,int row,int col){
    double Xmax = -99999999999;
    for(int i=0; i<row;i++){
        for(int j=0; j<col;j++){
            if(val_descritores[i][j]>Xmax)
                Xmax = val_descritores[i][j];
        }
    }

    return Xmax;
}

double retorna_xmin(double **val_descritores,int row,int col){
    double Xmin = 999999999;
    for(int i=0; i<row;i++){
        for(int j=0; j<col;j++){
            if(val_descritores[i][j]< Xmin)
                Xmin = val_descritores[i][j];
        }
    }

    return Xmin;
}


