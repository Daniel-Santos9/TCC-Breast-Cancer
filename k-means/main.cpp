#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "gravaDados.h"
#include "calcula_desc.h"
#include "normalizacao.h"
/*****************************************************************************************************************************/
//Namespaces
using namespace cv;
using namespace std;
//using namespace std::chrono;

/*****************************************************************************************************************************/
//Global Variables
const unsigned int SLIDER_MAX = 25;
const std::string WINDOW_NAME = "KMeans";
const std::string TRACKBAR_NAME = "Clusters";
int MAX_ITERATIONS = 2;
int sliderValue = 4;
Mat image;

/*****************************************************************************************************************************/
/**
    Returns the processed image using cv::kmeans
    @param const Mat& source The image to be processed.
    @return A reduced color image with (sliderValue) colors
*/
Mat applyKMeans(const Mat& source, double **descritor);

int encontra_iguais(int p1, int p2, int p3);

Mat moda(Mat image1, Mat image2, Mat image3);



/**
    Callback function for trackbar event
*/
//void trackBarMovement(int, void*);

/*****************************************************************************************************************************/

int main () {
    //std::string imageName[10] = {"mdb005.jpg","mdb010rm.bmp","mdb012rl.bmp","mdb015lm.bmp","mdb021ll.bmp","mdb025ll.bmp","mdb069ll.bmp","mdb083ll.bmp","mdb104rm.bmp","mdb132rx.bmp"};
    //std::string imageName[10] = {""};
    for(int i=0; i<1;i++){
        string imageName="mdb134.bmp";
       // Mat b = imread("mdb005.jpg",1)
        std::cout<<"Imagem: "<<i+1<<" - "<<imageName<<std::endl;
        Mat image = imread(imageName, 1);
        calc_desc(imageName,"","",30,1);
        if (!image.data){
            std::cout << "Invalid name" << std::endl;
            cv::destroyAllWindows();
            return EXIT_FAILURE;
        }

        system("pause");
//        exit(0);



        int masc = 9;
        int row = image.rows-masc;
        int col = image.cols-masc;

        //Mat descritores(image.rows-9,image.cols-9,CV_8U);
        double **descritor1;
        descritor1 = (double**) malloc ((row) * sizeof (double*));
        for(int i =0; i < row; i++){
            descritor1[i] = (double*) malloc ((col) * sizeof (double));
        }

        double **descritor2;
        descritor2 = (double**) malloc ((row) * sizeof (double*));
        for(int i =0; i < row; i++){
            descritor2[i] = (double*) malloc ((col) * sizeof (double));
        }

        double **descritor3;
        descritor3 = (double**) malloc ((row) * sizeof (double*));
        for(int i =0; i < row; i++){
            descritor3[i] = (double*) malloc ((col) * sizeof (double));
        }

        double **descritores_norm;
        descritores_norm = (double**) malloc ((row) * sizeof (double*));
        for(int i =0; i < row; i++){
            descritores_norm[i] = (double*) malloc ((col) * sizeof (double));
        }
        Mat descritores(row,col,CV_8U);

        FILE *arq1, *arq2, *arq3;
         arq1 = fopen("desc1.txt", "r");
         arq2 = fopen("desc6.txt", "r");
         arq3 = fopen("desc7.txt", "r");
        if (arq1 == NULL)				// Se n�o conseguiu abrir
        {
            printf("Problemas na ABERTURA do arquivo 1\n");
            return 0;
        }
        if (arq2 == NULL)				// Se n�o conseguiu abrir
        {
            printf("Problemas na ABERTURA do arquivo 2\n");
            return 0;
        }
        if (arq3 == NULL)				// Se n�o conseguiu abrir
        {
            printf("Problemas na ABERTURA do arquivo 3\n");
            return 0;
        }
        double c1,c2,c3;
        char v;
        for(int i=0+masc; i<row; i++){
            for(int j=0; j<col; j++){
                fscanf(arq1,"%lf%c",&c1,&v);
                descritor1[i][j] = c1;
                fscanf(arq2,"%lf%c",&c2,&v);
                descritor2[i][j] = c2;
                fscanf(arq3,"%lf%c",&c3,&v);
                descritor3[i][j] = c3;
               // cout<<descritores[i][j]<<endl;
            }
        }
        fecharArquivo(arq1);
        fecharArquivo(arq2);
        fecharArquivo(arq3);
        double valor;
         //Mat descritores_norm_conv = image.clone();
         cout<<"passou aqui"<<endl;

        Mat desc1 =  applyKMeans(image,descritor1);
        Mat desc2 = applyKMeans(image,descritor2);
        Mat desc3 = applyKMeans(image,descritor3);

        Mat imagem_moda = moda(desc1,desc2,desc3);


//        namedWindow("desc1");
//        namedWindow("desc2");
//        namedWindow("desc3");
//        namedWindow("Moda");
//        imshow("desc1",desc1);
//        imshow("desc2",desc2);
//        imshow("desc3",desc3);
//        imshow("Moda",imagem_moda);
//        waitKey(0);
//        destroyAllWindows();
//        system("pause");

        cout<<"eonioncnd"<<endl;


//        Mat a = descritores_norm_conv;

//        namedWindow("img");
//        imshow("img",descritores_norm_conv);
//        waitKey(0);
//        destroyWindow("img");


        //memcpy(descritores_norm_conv.data, descritores_norm, row*col*sizeof(int));

//        for(int i=0; i<row; i++){
//            for(int j=0; j<col; j++){
//               cout<<descritores_norm_conv.at<Vec3b>(i,j)<<endl;
//            }
//        }
        system("pause");

       // cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);

        //Mat resul =  applyKMeans(descritores_norm_conv);

       // cv::createTrackbar(TRACKBAR_NAME,WINDOW_NAME, &sliderValue, SLIDER_MAX, trackBarMovement );
        //cv::waitKey(0);
        //cv::destroyAllWindows();
        cv::imwrite("desc1_"+imageName[i],desc1);
        cv::imwrite("desc2_"+imageName[i],desc2);
        cv::imwrite("desc3_"+imageName[i],desc3);
        cv::imwrite("moda_"+imageName[i],imagem_moda);

    }

     return EXIT_SUCCESS;
}

/*****************************************************************************************************************************/

Mat applyKMeans(const Mat& source, double **descritor){ //const Mat& source

    // ---------------------------- Fim Bloco 1 ---------------------------------------- \\



    //sliderValue
//    if (sliderValue==0){
//        sliderValue=1;
//    }

//    std::chrono::high_resolution_clock::time_point start,end; // for time measurement
//    std::chrono::duration<double> elapsedTime;			 	  // for time measurement
//    start = std::chrono::high_resolution_clock::now();
    //cv::cvtColor(source, source, CV_BGR2GRAY);

    int masc = 9;
    int row = source.rows-masc;
    int col = source.cols-masc;
    const unsigned int singleLineSize = source.rows * source.cols;
  //  Mat data = source.reshape((-1,3));
    Mat data = source.reshape(1, singleLineSize);
    data.convertTo(data, CV_32F);

    for(int i=0+masc; i<row; i++){
        for(int j=0+masc; j<col; j++){
               data.at<float>(i,j)=descritor[i][j];

        }
    }

    //system("pause");

//    Mat data;
//    source.convertTo(data, CV_32FC3);
//    data.reshape (1,singleLineSize);

    std::vector<int> labels;
    cv::Mat1f colors;

    cv::kmeans(data, sliderValue,labels,cv::TermCriteria(cv::TermCriteria::EPS+cv::TermCriteria::COUNT, 10, 1.),MAX_ITERATIONS,cv::KMEANS_PP_CENTERS,colors);
    for (unsigned int i = 0 ; i < singleLineSize ; i++ ){
                data.at<float>(i, 0) = colors(labels[i], 0);
                data.at<float>(i, 1) = colors(labels[i], 1);
                data.at<float>(i, 2) = colors(labels[i], 2);
    }
        cout<<"1koodmciomd"<<endl;
    Mat outputImage = data.reshape(3, source.rows);
    outputImage.convertTo(outputImage, CV_8U);
//    end = std::chrono::high_resolution_clock::now();
//    elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    //std::cout<< "Elapsed time for processing with " << sliderValue <<" clusters " << elapsedTime.count() << "s" << std::endl;
    return outputImage;



}

int encontra_iguais(int p1, int p2, int p3){

    if(p1 == p2 || p1 == p3){
        return p1;
    }
    else if( p2 == p3){
        return p2;
    }
    else if( p1 != p2 && p2 != p3 && p1 !=p3){
        return p3;
    }

}

Mat moda(Mat image1, Mat image2, Mat image3){
//    int valor =0;
//    int p1=0, p2=0, p3=0;
//    Mat a(image1.rows, image1.cols, CV_8U);
//    for(int i=0; i< image1.rows; i++){
//        for(int j=0; j<image1.cols; j++){
//            p1 = image1.at<uchar>(i,j);
//            p2 = image2.at<uchar>(i,j);
//            p3 = image3.at<uchar>(i,j);
//            a.at<uchar>(i,j) = encontra_iguais(p1,p2,p3);

//        }
//    }
   Mat a = image1 + image2 + image3;
    return a;
}




/*****************************************************************************************************************************/

//void trackBarMovement(int, void*){
//    cv::imshow(WINDOW_NAME, applyKMeans(image,));
//}
