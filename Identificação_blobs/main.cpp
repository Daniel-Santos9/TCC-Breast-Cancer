#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/features2d.hpp>
#include "encontra_area_blob.h"

using namespace std;
using namespace cv;

Mat umParaTresVermelho(Mat src){
    //Mat dst(src.rows, src.cols, Vec3b)
    Mat dst(src.rows,src.cols, DataType<Vec3b>::type);
    for(int i=0; i<src.rows;i++){
        for(int j=0; j<src.cols;j++){
            if(src.at<uchar>(i,j) == 0){
                dst.at<Vec3b>(i,j)[0] = src.at<uchar>(i,j);
                dst.at<Vec3b>(i,j)[1] = src.at<uchar>(i,j);
                dst.at<Vec3b>(i,j)[2] = src.at<uchar>(i,j);
            }else{
                dst.at<Vec3b>(i,j)[0] = 0;
                dst.at<Vec3b>(i,j)[1] = 0;
                dst.at<Vec3b>(i,j)[2] = 255;
            }
        }
    }
    return dst;
}


int main(){

    // Read image
        //string imageName[30] = {"mdb010.bmp","mdb021.bmp","mdb023.bmp","mdb025.bmp","mdb028.bmp","mdb083.bmp","mdb117.bmp","mdb132.bmp","mdb134.bmp","mdb150.bmp","mdb155.bmp","mdb158.bmp","mdb184.bmp","mdb202.bmp","mdb271.bmp","mdb006.bmp","mdb060.bmp","mdb077.bmp","mdb131.bmp","mdb133.bmp","mdb140.bmp","mdb232.bmp","mdb272.bmp","mdb298.bmp","mdb299.bmp","mdb301.bmp","mdb302.bmp","mdb304.bmp","mdb306.bmp","mdb310.bmp"};
        //string imageName[18] = {"Tmdb117.bmp","Tmdb021.bmp","Tmdb010.bmp","mdb271.bmp","mdb023.bmp","mdb010.bmp","mdb021.bmp","mdb025.bmp","mdb028.bmp","mdb083.bmp","mdb117.bmp","mdb132.bmp","mdb134.bmp","mdb150.bmp","mdb155.bmp","mdb158.bmp","mdb184.bmp","mdb202.bmp"};
        //string imageName[15]={"mdb006.bmp","mdb060.bmp","mdb077.bmp","mdb131.bmp","mdb133.bmp","mdb140.bmp","mdb232.bmp","mdb272.bmp","mdb298.bmp","mdb299.bmp","mdb301.bmp","mdb302.bmp","mdb304.bmp","mdb306.bmp","mdb310.bmp"};
        //string imageName[1]={ "completa_mdb083.bmp"};
       // string imageName[14]={"mdb010.bmp","mdb021.bmp","mdb023.bmp","mdb025.bmp","mdb028.bmp","mdb083.bmp","mdb117.bmp","mdb132.bmp","mdb134.bmp","mdb150.bmp","mdb155.bmp","mdb184.bmp","mdb264.bmp","mdb271.bmp"};
        string imageName[1] = {"Cmdb202.bmp"};
    for(int i=0; i<1;i++){

        Mat im = imread(imageName[i], IMREAD_GRAYSCALE );

        cout<<"imagem "<<i+1<<" concluida"<<endl;

        Mat original = imread("imagens\\"+imageName[i],1);
        if(im.empty()){
            cout<<"Imagem nao encontrada"<<endl;
            return EXIT_FAILURE;
        }
        if(original.empty()){
            cout<<"Imagem nao encontrada"<<endl;
            return EXIT_FAILURE;
        }

        // Setup SimpleBlobDetector parameters.
        SimpleBlobDetector::Params params;

        // Change thresholds
        params.minThreshold = 0;
        params.maxThreshold = 200;

        // Filter by Area.
        params.filterByArea = true;
        params.minArea = 950; //1500
        params.maxArea = 50000;

        // Filter by Circularity
        params.filterByCircularity = true;
        params.minCircularity = 0.3; //, 0.3
        //params.maxCircularity = 0.8; // não tinha
        // Filter by Convexity
        params.filterByConvexity = true;
        params.minConvexity = 0.2;// 0.87 , 0.47

        // Filter by Inertia
        params.filterByInertia = true;
        params.minInertiaRatio = 0.18;//0.01 , 0.3


        // Storage for blobs
        vector<KeyPoint> keypoints;


        Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

        // Detect blobs
        detector->detect( im, keypoints);

       // Point2f pontos = keypoints;

            //cout <<p.x ;
        //cout<<pontos.x<<endl;

        //system("pause");
    //#endif

        // Draw detected blobs as red circles.
        // DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures
        // the size of the circle corresponds to the size of blob

        Mat im_with_keypoints;
        //drawMatches();

        Mat resul = im.clone();
        drawKeypoints( im, keypoints, im_with_keypoints, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
       if(keypoints.empty()){
        cout<<"Sem blobs"<<endl;
        resul = 255;
       }
       else{
           int *pontos = (int *) malloc(4 * sizeof(int));
           resul = 255;
           for(int c=0; c<keypoints.size();c++){
               Point2f p= keypoints[c].pt;
              // cout<<p.x<<endl<<p.y;

               Extrai_pontos(im,p.y,p.x,pontos);
               int l1, l2, c1,c2;
               l1 = pontos[0];
               l2 = pontos[1];
               c1 = pontos[3];
               c2 = pontos[2];

               cout<<l1<<endl<<l2;

               for(int i=l1; i< l2;i++){
                   for(int j = c1; j<c2; j++){

                       if (im.at<uchar>(i,j) < 10){
                               cout<<  im.at<uchar>(i,j);
                               resul.at<uchar>(i,j) = 0;

                       }
                   }
               }



           }


        cout<<"com blobs"<<endl;
       }

       // Inicio

       Mat canny_output;
       vector<vector<Point> > contours;
       vector<Vec4i> hierarchy;

       // detect edges using canny
       Canny( resul, canny_output, 50, 150, 3 );

       // find contours
       findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

       // get the moments
       vector<Moments> mu(contours.size());
       for( int i = 0; i<contours.size(); i++ )
       { mu[i] = moments( contours[i], false ); }

       // get the centroid of figures.
       vector<Point2f> mc(contours.size());
       for( int i = 0; i<contours.size(); i++)
       { mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); }


       // draw contours
       Mat drawing(canny_output.size(), CV_8UC3);
       for( int i = 0; i<contours.size(); i++ )
       {
       Scalar color = Scalar(0,0,255); // B G R values
       drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
       //circle( drawing, mc[i], 4, color, -1, 8, 0 );
       }
       // Fim


      // Mat canny, draw;
       Mat final = original.clone();



       //cvtColor(src1, gray, CV_BGR2GRAY);

      // Canny( resul, canny, 50, 150, 5);

       //canny.convertTo(draw, CV_8U);
       //draw = Scalar(255,0,0);
       //Mat dist = umParaTresVermelho(draw); //resul

       for(int i =0; i< original.rows;i++){
           for(int j = 0; j< original.cols; j++){
               if((drawing.at<Vec3b>(i,j)[0] == 0) && (drawing.at<Vec3b>(i,j)[1] == 0) && (drawing.at<Vec3b>(i,j)[2] == 255) ){
                   final.at<Vec3b>(i,j)[0] = 0;
                   final.at<Vec3b>(i,j)[1] = 0;
                   final.at<Vec3b>(i,j)[2] = 255;
               }
           }
       }
       //final = original + drawing;

       cout<<"passou aqui"<<endl;

        //DRAW_RICH_KEYPOINTS
        // Show blobs
        imwrite("Resul_final\\img_seg\\"+imageName[i],resul);
        imwrite("Resul_final\\img_final\\"+imageName[i],final);
//        namedWindow(imageName[i],WINDOW_NORMAL);
//        namedWindow("resultado",WINDOW_NORMAL);
//        imshow(imageName[i], im_with_keypoints );
//        imshow("resultado",resul);
//        waitKey(0);
    }

}
