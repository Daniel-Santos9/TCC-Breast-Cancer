#include "cruzaFuncPonteiros.h"
#include "QTime"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "QString"
#include "descritores.h"

using namespace cv;
using namespace std;

vetDescritor descritor[] = {
    f1_asm,					//segundo momento angular 0
    f2_contrast,			//contraste                1 Esse
   // f3_corr,				//correlacao              2
    f4_var,					//variancia
    f5_idm,					//hogeneidade               3
    f6_savg,				//soma das medias           4 Esse
    f8_sentropy,			//soma da entropia
    f7_svar,				//soma da variancia         5 Esse
    f9_entropy,				//entropia
    f10_dvar,				//diferen�a da variancia  6
    f11_dentropy,			//diferen�a da entropia    7
    f12_icorr,				//informa��es de correla��o 1
    f13_icorr				//informa��es de correla��o 2
};

void calc_desc(string nomeImagem, string pasta1Imagem, string pasta2Imagem, int nAmostras, int descritor){
    int tone_count=255;

    int masc = 3; // Tamanho da vizinhan�a: masc x masc
    int** amostras = (int**) malloc( nAmostras * sizeof (int*));
        for (int i = 0; i < nAmostras; ++i)
           amostras[i] = (int*) malloc( masc*masc * sizeof (int));

    float f = (masc/2.0)-0.5;
    int fator = (int)f;
    int x,y, cont;
    int rows = masc;
    int cols = masc;
    double desc1[1];
    double desc2[1];
    double desc3[1];
    double desc4[1];
    double desc5[1];
    double desc6[1];
    double desc7[1];
    double desc8[1];
    double desc9[1];
    double desc10[1];
    double desc11[1];
    double desc12[1];
    double desc13[1];
    float **P_matrix;
    FILE* arquivo1 = abrirArquivo("desc1.txt");
    FILE* arquivo2 = abrirArquivo("desc2.txt");
    FILE* arquivo3 = abrirArquivo("desc3.txt");
    FILE* arquivo4 = abrirArquivo("desc4.txt");
    FILE* arquivo5 = abrirArquivo("desc5.txt");
    FILE* arquivo6 = abrirArquivo("desc6.txt");
    FILE* arquivo7 = abrirArquivo("desc7.txt");
    FILE* arquivo8 = abrirArquivo("desc8.txt");
    FILE* arquivo9 = abrirArquivo("desc9.txt");
    FILE* arquivo10 = abrirArquivo("desc10.txt");
    FILE* arquivo11 = abrirArquivo("desc11.txt");
    FILE* arquivo12 = abrirArquivo("desc12.txt");
    FILE* arquivo13 = abrirArquivo("desc13.txt");

    int **grays;
    grays = (int**) malloc( masc * sizeof (int*));
        for (int i = 0; i < masc; ++i)
           grays[i] = (int*) malloc( masc * sizeof (int));


    Mat imgCinza2 =  imread(nomeImagem,0);
    if(imgCinza2.empty())
    {
        cout <<  "Imagem nao encontrada" << std::endl ;
        return;
    }

     // cv::resize(imgCinza1, imgCinza2, cv::Size(), 0.60, 0.60);
//    namedWindow("img - resize");
//    imshow("img - resize",imgCinza2);
//    waitKey(0);
//    destroyWindow("img- resize");
//   // Mat img_desc(imgCinza2.rows, imgCinza2.cols, CV_8U);

    cout<<"Linhas:"<<imgCinza2.rows<<" Colunas:"<<imgCinza2.cols<<endl;/*
    cout<<"Linhas re:"<<imgCinza2.rows<<" Colunas re:"<<imgCinza2.cols<<endl;*/
    system("pause");
    //P_matrix = Liberar_matriz_real (tone_count, tone_count, P_matrix);
    Mat testeMLP(imgCinza2.rows, imgCinza2.cols, CV_8UC1);
    //testeMLP.setTo(cv::Scalar::all(0));
    cout<<"Passou aqui"<<endl;
    Vec3b pix;
    float perc=0;
   float max=imgCinza2.rows-masc;
    //arquivo = abrirArquivo();
    for(int i=0+masc; i<imgCinza2.rows-masc; i++)
    {
        perc=(i*100.0)/max;
        //system ("cls");
       // cout<<"Descritor:"<<descr1<<endl;
        cout<<perc<<"% concluido.\n";
        for(int j=0+masc; j<imgCinza2.cols-masc; j++)
        {
            if((int)imgCinza2.at<uchar>(i,j))
            {
                cont=0;
                for(int a=0; a<masc; a++)
                {
                    for(int b=0; b<masc; b++){
                        amostras[0][cont] = (int)imgCinza2.at<uchar> (i+a-fator, j+b-fator);
                        cont++;
                    }
                }
                cont=0;
                for(int i=0; i<masc; i++)
                {
                    for(int j=0; j<masc; j++)
                    {
                        grays[i][j]=amostras[0][cont];
                        cont++;
                    }
                }

//                for(int i = 0; i <nAmostras; i++){
//                  for(int j = 0; j < (masc*masc); j++){
//                    free(amostras[i][j]);
//                  }
//                  free(amostras[i]);;
//                }


               // free(amostras);

                P_matrix = CoOc_simetrH_Mat (grays, rows, cols, 0, tone_count);

                desc1[1] = f1_asm(P_matrix,tone_count);
                desc2[1] = f2_contrast(P_matrix,tone_count);
                desc3[1] = f3_corr(P_matrix,tone_count);
                desc4[1] = f4_var(P_matrix,tone_count);
                desc5[1] = f5_idm(P_matrix,tone_count);
                desc6[1] = f6_savg(P_matrix,tone_count);
                desc7[1] = f7_svar(P_matrix,tone_count);
                desc8[1]= f8_sentropy(P_matrix,tone_count);
                desc9[1] = f9_entropy(P_matrix,tone_count);
                desc10[1] = f10_dvar(P_matrix,tone_count);
                desc11[1] = f11_dentropy(P_matrix,tone_count);
                desc12[1] = f12_icorr(P_matrix,tone_count);
                desc13[1] = f13_icorr(P_matrix,tone_count);


                gravarDados(1,desc1,arquivo1);
                gravarDados(1,desc2,arquivo2);
                gravarDados(1,desc3,arquivo3);
                gravarDados(1,desc4,arquivo4);
                gravarDados(1,desc5,arquivo5);
                gravarDados(1,desc6,arquivo6);
                gravarDados(1,desc7,arquivo7);
                gravarDados(1,desc8,arquivo8);
                gravarDados(1,desc9,arquivo9);
                gravarDados(1,desc10,arquivo10);
                gravarDados(1,desc11,arquivo11);
                gravarDados(1,desc12,arquivo12);
                gravarDados(1,desc13,arquivo13);
//                for(int i = 0; i < masc; i++){
//                  for(int j = 0; j < masc; j++){
//                    free(grays[i][j]);
//                  }
//                  free(grays[i]);;
//                }

                //amostras = Liberar_matriz_int(nAmostras,(masc*masc), amostras);
                P_matrix = Liberar_matriz_float(tone_count, tone_count, P_matrix);
                //double correlation = f3_corr(P_matrix, tone_count);
                //double idm = f5_idm(P_matrix, tone_count);
                //double se = f6_savg(P_matrix, tone_count);

                //calculo de descritores com vetor de fun��es (sorteio din�mico 3 a 3):
            }
        }
    }

   // return img_desc;
}
