#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
   // string imageName[39] = {"mdb005.bmp","mdb010.bmp","mdb012.bmp","mdb015.bmp","mdb021.bmp","mdb025.bmp","mdb083.bmp","mdb083.bmp","mdb132.bmp","mdb150.bmp","mdb248.bmp","mdb023.bmp","mdb028.bmp","mdb092.bmp","mdb117.bmp","mdb155.bmp","mdb158.bmp","mdb184.bmp","mdb202.bmp","mdb264.bmp","mdb271.bmp","mdb006.bmp","mdb060.bmp","mdb131.bmp","mdb133.bmp","mdb134.bmp","mdb140.bmp","mdb168.bmp","mdb232.bmp","mdb272.bmp","mdb273.bmp","mdb297.bmp","mdb298.bmp","mdb299.bmp","mdb301.bmp","mdb302.bmp","mdb304.bmp","mdb305.bmp","mdb306.bmp"};
    //string imageName[10] = {"mdb023.bmp","mdb028.bmp","mdb092.bmp","mdb117.bmp","mdb155.bmp","mdb158.bmp","mdb184.bmp","mdb202.bmp","mdb264.bmp","mdb271.bmp","mdb006.bmp","mdb060.bmp","mdb131.bmp","mdb133.bmp","mdb140.bmp","mdb168.bmp","mdb232.bmp","mdb272.bmp","mdb273.bmp","mdb297.bmp","mdb298.bmp","mdb299.bmp","mdb301.bmp","mdb302.bmp","mdb304.bmp","mdb305.bmp","mdb306.bmp"};
    string prefi_img[3] = {"desc3_","desc9_","desc4_"};
    //string imageName[10]={"mdb006.bmp","mdb077.bmp","mdb131.bmp","mdb133.bmp","mdb140.bmp","mdb232.bmp","mdb272.bmp","mdb298.bmp","mdb299.bmp","mdb310.bmp"};
    //string imageName[12]={"mdb010.bmp","mdb021.bmp","mdb023.bmp","mdb025.bmp","mdb028.bmp","mdb083.bmp","mdb150.bmp","mdb155.bmp","mdb158.bmp","mdb184.bmp","mdb202.bmp","mdb271.bmp"};
    //string imageName[6]={"mdb083.bmp","mdb117.bmp","mdb132.bmp","mdb150.bmp","mdb184.bmp","mdb202.bmp"};
    //string imageName[5]={"mdb060.bmp","mdb301.bmp","mdb302.bmp","mdb304.bmp","mdb306.bmp"};
   // string imageName[3]={"mdb195.bmp","mdb248.bmp","mdb264.bmp"};
    // string imageName[2]={"mdb117.bmp","mdb132.bmp"};

    string imageName[1]={"mdb134.bmp"};
    string caminho1, caminho2, caminho3;
    string salvar, pasta = "complemento\\";
    int img;
    for(img=0; img<1;img++){

//        if(img <= 10){
//            pasta = "Benigno\\";
//        }else{
//            pasta = "Maligno\\";
//        }
//        for(h=0; h<13;h++){
            salvar = imageName[img];
            caminho1 = pasta+imageName[img]+"\\"+prefi_img[0] + imageName[img];
            caminho2 = pasta+imageName[img]+"\\"+prefi_img[1] + imageName[img];
            caminho3 = pasta+imageName[img]+"\\"+prefi_img[2] + imageName[img];
            cout<<caminho1<<endl;
           // cout<<caminho<<endl;
            Mat image1 = imread(caminho1, 0);
            Mat image2 = imread(caminho2, 0);
            Mat image3 = imread(caminho3, 0);
            if (!image1.data){
                std::cout << "Invalid name" << std::endl;
                //return EXIT_FAILURE;
            }
            if (!image2.data){
                std::cout << "Invalid name" << std::endl;
                //return EXIT_FAILURE;
            }

            if (!image3.data){
                std::cout << "Invalid name" << std::endl;
                //return EXIT_FAILURE;
            }

           Mat image = image1 + image2 + image3;
           //image = image - image1 + image2;
            Mat otsu = image.clone();
//            int maior = -9999;
//            int menor = 99999;
//            for(int i =0; i< image.rows;i++){
//                for(int j=0; j< image.cols; j++){
//                    if(image.at<uchar>(i,j) > maior){
//                        maior= image.at<uchar>(i,j);
//                    }else if (image.at<uchar>(i,j)<menor){
//                        menor = image.at<uchar>(i,j);
//                    }

//                }
//            }
            int cinza =0;
            int value = threshold(image,otsu,0,255, THRESH_OTSU);
            int vet[256];
            for(int z = 0; z <255; z++)
                vet[z] = 0;

            for(int a = 0; a < image.rows; a++){
                for(int b = 0; b < image.cols; b ++){
                    cinza = image.at<uchar>(a,b);
                    //cout<<cinza<<endl;
                    vet[cinza]+= 1;
                }
            }

            int valmaior = -999;
            int indicemaior = -1;
            for(int z =0; z< 255; z++){
                //cout<<vet[z]<<endl;
                if(vet[z]> valmaior){
                    valmaior =  vet[z];
                    indicemaior = z;
                }
            }
           cout<<"valor maior: "<<valmaior<<endl;
           cout<<"indice maior: "<<indicemaior<<endl;
           cout<<"valor otsu: "<<value<<endl;

            int limiar = 0;
            if(indicemaior > 230)
                 limiar = value - (value * 0.25); //25
            else if (indicemaior > 200 && indicemaior <= 230)
                 limiar = value - (value * 0.30); //15
            else if (indicemaior > 170 && indicemaior <= 200)
                   limiar = value - (value * 0.30); //30
            else if (indicemaior > 130 && indicemaior <= 170)
                   limiar = value - (value * 0.30); //30
            else if (indicemaior > 100 && indicemaior <= 130)
                   limiar = value - (value * 0.30); //30
            else
                limiar = value - (value * 0.30);
            //system("pause");
           //int limiar = value - (value * 0.35);
           //cout<<"passou aqui";
           cout<<"Limiar: "<<limiar<<endl;

            for(int i =0; i< image.rows;i++){
                for(int j=0; j< image.cols; j++){
                    if(image.at<uchar>(i,j) < (limiar)){
                        otsu.at<uchar>(i,j) = 0;
                    }else{
                        otsu.at<uchar>(i,j) = 255;
                    }

                }
           }

//                namedWindow("otsu",WINDOW_NORMAL);
//                namedWindow("original", WINDOW_NORMAL);
//                imshow("otsu",otsu);
//                imshow("original",image);
//                waitKey(0);
//                destroyAllWindows();
            imwrite("Resultado\\"+imageName[img]+"\\"+salvar,otsu);
            imwrite("Resultado\\"+imageName[img]+"\\"+"original"+salvar,image);
                cout<< "imagem "<< img+1<<" salva!"<<endl;
        }

   // double valor = threshold(image,otsu,0,255, THRESH_BINARY | THRESH_OTSU);
    //threshold(img,0,255,THRESH_OTSU)
   // cout<<valor;
//    namedWindow("otsu");
//    imshow("otsu",otsu);
//    waitKey(0);
//    destroyWindow("otsu");


    }

//}
