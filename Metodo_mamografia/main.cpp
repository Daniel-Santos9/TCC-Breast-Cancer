#include <iostream>
#include <string>
#include <QDirIterator>
#include "coletaPontos.h"
#include "calculo_descritores.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
using namespace std;

int main(){

    // normais
     //string imageName[15]={"mdb006.bmp","mdb060.bmp","mdb077.bmp","mdb131.bmp","mdb133.bmp","mdb140.bmp","mdb232.bmp","mdb272.bmp","mdb298.bmp","mdb299.bmp","mdb301.bmp","mdb302.bmp","mdb304.bmp","mdb306.bmp","mdb310.bmp"};
    //doentes
     string imageName[15]={"mdb010.bmp","mdb021.bmp","mdb023.bmp","mdb025.bmp","mdb028.bmp","mdb083.bmp","mdb117.bmp","mdb132.bmp","mdb134.bmp","mdb150.bmp","mdb155.bmp","mdb184.bmp","mdb202.bmp","mdb264.bmp","mdb271.bmp"};


    // ---------------------------------------------- BLOCO 1 ----------------------------------------------------//
    
    //                                             COLETAR PONTOS                                                //
    



//   for(int i=0; i<=15;i++)
//       //coletarPontos();
//        coletarPontos(imageName[i],"","",10,15,0);

//   exit(0);
   
   
  //--------------------------------------------- FIM DO BLOCO 1 ------------------------------------------------ */
//   //Matriz de coocorrencia
     double ***descritores;

   int nImagens = 15;
   int nAmostras = 10;
   int profundidade = 13; //descritores

   descritores = (double***) malloc( nImagens * sizeof (double**));
   for (int i = 0; i < nImagens; ++i){
       descritores[i] = (double**) malloc( nAmostras * sizeof (double*));
       for (int j = 0; j < nAmostras; ++j){
           descritores[i][j] = (double*) malloc( profundidade * sizeof (double));
       }
   }

//   //string pasta = "\\home\\daniel\\Área\ de\ Trabalho\\Metodo_mamografia\\build-Metodo_mamografia-Desktop-Debug\\";
//   //cout << pasta;
   descritores = calc_desc("",15,10,0,0,profundidade);

   return 0;
}
