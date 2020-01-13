#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/features2d.hpp>

using namespace std;
using namespace cv;


float acuracia(int VP, int VN, int FP, int FN){
    float Ac;

    Ac = (VP+VN) / float((VP + VN + FP + FN));

    return Ac;

}

float sensibilidade (int VP, int FN){
    float Sen;

        Sen = (VP)/float((VP+FN));

    return Sen;
}

float especificidade (int VN, int FP){
    float Esp;

    Esp = (VN)/float((VN+FP));

    return Esp;

}

int main (){
    int VP =0, VN =0, FP =0, FN =0;
    string imageName[30]={"mdb010.bmp","mdb021.bmp","mdb023.bmp","mdb025.bmp","mdb028.bmp","mdb083.bmp","mdb117.bmp","mdb132.bmp","mdb134.bmp","mdb150.bmp","mdb155.bmp","mdb184.bmp","mdb202.bmp","mdb264.bmp","mdb271.bmp","mdb006.bmp","mdb060.bmp","mdb077.bmp","mdb131.bmp","mdb133.bmp","mdb140.bmp","mdb232.bmp","mdb272.bmp","mdb298.bmp","mdb299.bmp","mdb301.bmp","mdb302.bmp","mdb304.bmp","mdb306.bmp","mdb310.bmp"};

    Mat original, ident;
    long int Ri,Gi,Bi,Ro,Go,Bo;
    for(int i=0; i<30; i++){
       // VP =0, VN =0, FP =0, FN =0;
        ident = imread(imageName[i],1);
        cout<<"Imagem "<< i+1<<" analisada"<<endl;
        original = imread("Imagens\\"+imageName[i],1);

        if(ident.empty()){
            cout<<"imagem ident nao encontrada"<<endl;
        }

        if(original.empty()){
            cout<<"imagem original nao encontrada"<<endl;
        }

        //VP =0; VN =0; FN=0; FP=0;
        for(int i=0; i<original.rows; i++){
              //cout<<"passou aqui"<<endl;
            for(int j=0; j<original.cols; j++){

                Bi = ident.at<Vec3b>(i,j)[0];
                Gi = ident.at<Vec3b>(i,j)[1];
                Ri = ident.at<Vec3b>(i,j)[2];
                Bo = original.at<Vec3b>(i,j)[0];
                Go = original.at<Vec3b>(i,j)[1];
                Ro = original.at<Vec3b>(i,j)[2];
                //cout<< Ro<<endl;
                if((Bi == 0 && Gi == 0 && Ri == 255) && (Bo == 0 && Go == 0 && Ro == 255)){
                    VP++;
                }

                if((Bi == 0 && Gi == 0 && Ri == 255) && (!(Bo == 0 && Go == 0 && Ro == 255))){
                    FP++;
                }

                if((!(Bi == 0 && Gi == 0 && Ri == 255)) && (!(Bo == 0 && Go == 0 && Ro == 255))){
                    VN++;
                }

                if((!(Bi == 0 && Gi == 0 && Ri == 255)) && ((Bo == 0 && Go == 0 && Ro == 255))){
                    FN++;
                }
            }
        }

//        float Ac = acuracia(VP,VN,FP,FN);
//        float Sen = sensibilidade(VP,FN);
//        float Esp = especificidade(VN,FP);
//        cout<<"Imagem: "<<imageName[i]<<endl;
//        cout<<"Valor Verdadeiro Positivo: "<<VP<<endl;
//        cout<<"Valor Falso Positivo: "<<FP<<endl;
//        cout<<"Valor Verdadeiro Negativo: "<<VN<<endl;
//        cout<<"Valor Falso Negativo: "<<FN<<endl;
//        cout<<"---------------------------  --  ------------------------------------"<<endl;
//        cout<<"Sensibilidade: "<<Sen<<endl;
//        cout<<"Especificidade: "<<Esp<<endl;
//        cout<<"Acuracia: "<<Ac<<endl;


//             cout<<"---------------------------  --  ------------------------------------"<<endl<<endl;

       // system("pause");
    }



    float Ac = acuracia(VP,VN,FP,FN);
    float Sen = sensibilidade(VP,FN);
    float Esp = especificidade(VN,FP);
    cout<<"Valor Verdadeiro Positivo: "<<VP<<endl;
    cout<<"Valor Verdadeiro Negativo: "<<VN<<endl;
    cout<<"Valor Falso Positivo: "<<FP<<endl;
    cout<<"Valor Falso Negativo: "<<FN<<endl;
    cout<<"---------------------------  --  ------------------------------------"<<endl;
    cout<<"Acuracia: "<<Ac<<endl;
    cout<<"Sensibilidade: "<<Sen<<endl;
    cout<<"Especificidade: "<<Esp<<endl;

}
