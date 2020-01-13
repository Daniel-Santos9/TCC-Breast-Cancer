#include "QTime"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "QString"
#include <QDirIterator>
#include <QCoreApplication>
#include <string>
#include "realce.h"

using namespace cv;
using namespace std;



vector<string> getFolderFiles(string path, string fileExt)
{
    vector<std::string> filenames;
    int cont=0;
    QDirIterator dirIt(path.c_str(),QDirIterator::Subdirectories);
    while (dirIt.hasNext()) {
        dirIt.next();
        if (QFileInfo(dirIt.filePath()).isFile()){
            if (QFileInfo(dirIt.filePath()).suffix() == fileExt.c_str()) {
                filenames.push_back( dirIt.fileName().toUtf8().constData() );
                cont++;
            }
        }
    }
    cout<<cont<<" imagens encontradas\n";
    system("pause");
    return filenames;
}

int main()
{

    string diretorio = "C:\\Users\\Daniel\ Santos\\Downloads\\mias\\bmp\\";
    string diretorio1 = "C:\\Users\\Daniel\ Santos\\Downloads\\mias\\negativo\\";
    Mat img, img2; int cont =0, h=0;int a=2;
  //  string destino[20]={"masc3\\","masc5\\","masc7\\","masc9\\","masc11\\","masc13\\","masc15\\","masc17\\","masc19\\","masc21\\","masc23\\","masc25\\","masc27\\","masc29\\","masc41\\","masc51\\","masc61\\","masc71\\","masc81\\","masc91\\"};
    vector<string> nome = getFolderFiles(diretorio,"bmp");
        for (vector<string>::iterator i = nome.begin(); i!=nome.end(); i++){
            string n0 = diretorio+(*i);
            string dst = diretorio1+(*i);
            cout<<dst<<endl;
            //system("pause");
            //cout<<n0;
            img = imread(n0,0);
            if (!img.data) {
                cout<<"nao foi possivel abrir a imagem\n"<<(*i);
                exit(0);
            }

            Mat img_negativo = 255 - img;

            Mat img2 = Realce(2,img_negativo,1,1,0.9);
            Mat media;
            medianBlur(img2,media,15);
           // Mat media2 = Realce(1,media,1.2,0,3);

//            Mat imgGau = img.clone();
//            GaussianBlur(img,imgGau,Size(masc,masc),0,0,BORDER_DEFAULT);
//            equalizeHist(imgGau,img2);
            //system("cls");
            cout<<"Borrando imagem"<<endl;

           // string filename = "Equualizada_"+ (n0);

            if (img2.data) {
                imwrite((dst) + ".bmp",media);
                cout<<"Salvou!" << cont;
                cont++;
            }else{
                cout<<"problema!";
            }
        }


        cont=0;

    return 0;
}
