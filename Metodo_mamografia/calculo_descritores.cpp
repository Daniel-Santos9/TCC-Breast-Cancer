#include <string>
#include "descritores.h"
#include "gravaDados.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

//#include "mlp.h"
//#include "pdi.h"

double*** calc_desc(string pasta1Imagem, int nImagens, int nAmostras, int altura, int largura, int profundidade) {

    //String imagensDoentes[20] = {"mdb005ll.bmp","mdb010rm.bmp","mdb012rl.bmp","mdb015lm.bmp","mdb021ll.bmp","mdb025ll.bmp","mdb069ll.bmp","mdb083ll.bmp","mdb104rm.bmp","mdb132rx.bmp","mdb023ll.bmp","mdb028rl.bmp","mdb117ll.bmp","mdb134rx.bmp","mdb155ll.bmp","mdb158rm.bmp","mdb184rl.bmp","mdb202rl.bmp","mdb264rm.bmp","mdb271ll.bmp"};
   // string imagensDoentes[5]={"IMD002.bmp","IMD004.bmp","IMD009.bmp","IMD013.bmp","IMD015.bmp"};
   // string imagensNormais[30] ={"mdb011ll.pgm","mdb026rl.pgm","mdb027ll.pgm","mdb057ll.pgm","mdb077ll.pgm","mdb078rl.pgm","mdb131lx.pgm","mdb133lx.pgm","mdb136rx.pgm","mdb139lx.pgm","mdb140rx.pgm","mdb153lx.pgm","mdb154rx.pgm","mdb168rl.pgm","mdb294rl.pgm","mdb297ll.pgm","mdb298rl.pgm","mdb299ll.pgm","mdb300rl.pgm","mdb301lm.pgm","mdb302rm.pgm","mdb303lm.pgm","mdb304rm.pgm","mdb305lm.pgm","mdb306rm.pgm","mdb307ll.pgm","mdb308rl.pgm","mdb309ll.pgm","mdb310rl.pgm","mdb313ll.pgm"};
    //string imagensDoentes[30]= {"mdb005ll.pgm","mdb010rm.pgm","mdb012rl.pgm","mdb015lm.pgm","mdb025ll.pgm","mdb069ll.pgm","mdb080rm.pgm","mdb083ll.pgm","mdb097ll.pgm","mdb104rm.pgm","mdb132rx.pgm","mdb142rx.pgm","mdb144rx.pgm","mdb190rl.pgm","mdb314rl.pgm","mdb023ll.pgm","mdb028rl.pgm","mdb058rl.pgm","mdb092rm.pgm","mdb117ll.pgm","mdb134rx.pgm","mdb155ll.pgm","mdb158rm.pgm","mdb178rs.pgm","mdb181lm.pgm","mdb184rl.pgm","mdb202rl.pgm","mdb206rl.pgm","mdb264rm.pgm","mdb271ll.pgm"};
    //string imagensDoentes[22]={"mdb005ll.bmp","mdb010rm.bmp","mdb012rl.bmp","mdb015lm.bmp","mdb021ll.bmp","mdb025ll.bmp","mdb083ll.bmp","mdb104rm.bmp","mdb132rx.bmp","mdb150rx.bmp","mdb248rl.bmp","mdb023ll.bmp","mdb028rl.bmp","mdb092rm.bmp","mdb117ll.bmp","mdb134rx.bmp","mdb155l.bmp","mdb158rm.bmp","mdb184rl.bmp","mdb202rl.bmp","mdb264rm.bmp","mdb271ll.bmp"};

    // normais
    // string imageName[15]={"mdb006.bmp","mdb060.bmp","mdb077.bmp","mdb131.bmp","mdb133.bmp","mdb140.bmp","mdb232.bmp","mdb272.bmp","mdb298.bmp","mdb299.bmp","mdb301.bmp","mdb302.bmp","mdb304.bmp","mdb306.bmp","mdb310.bmp"};
    //doentes
    string imageName[15]={"mdb010.bmp","mdb021.bmp","mdb023.bmp","mdb025.bmp","mdb028.bmp","mdb083.bmp","mdb117.bmp","mdb132.bmp","mdb134.bmp","mdb150.bmp","mdb155.bmp","mdb184.bmp","mdb202.bmp","mdb264.bmp","mdb271.bmp"};


//    string imagensNormais[20]={"mdb006rl.bmp","mdb060rs.bmp","mdb077ll.bmp","mdb131lx.bmp","mdb133lx.bmp","mdb140rx.bmp","mdb168rl.bmp","mdb232rl.bmp","mdb272rl.bmp","mdb273ll.bmp","mdb297ll.bmp","mdb298rl.bmp","mdb299ll.bmp","mdb301lm.bmp","mdb302rm.bmp","mdb304rm.bmp","mdb305lm.bmp","mdb306rm.bmp","mdb309ll.bmp","mdb310rl.bmp"};
//    string imagensDoentes[1] = "mdb005.jpg";
    int x, y, z;
    double ***descritores;
    descritores = (double***) malloc( nImagens * sizeof (double**));
    for (int i = 0; i < nImagens; ++i){
        descritores[i] = (double**) malloc( nAmostras * sizeof (double*));
        for (int j = 0; j < nAmostras; ++j){
            descritores[i][j] = (double*) malloc( profundidade * sizeof (double));

        }
    }

    //unsigned long inp=3;        // Numero de entradas da RNA
    //unsigned long outp=1;       // Numero de saidas
    //double** tr_inp = (double**) malloc( nAmostras * sizeof (double*));
 //       for (int i = 0; i < nAmostras; ++i)
 //          tr_inp[i] = (double*) malloc( inp * sizeof (double)); // Vetor de entradas para treinamento
    //
    //double** tr_out = (double**) malloc( nAmostras * sizeof (double*));
 //       for (int i = 0; i < nAmostras; ++i)
 //          tr_out[i] = (double*) malloc( outp * sizeof (double)); // Vetor de saidas desejadas

    //matriz[x*largura*profundidade+y*largura+z] = 0;

    //cout<<pasta1Imagem;

    for(int indiceReferencia=0; indiceReferencia< nImagens; indiceReferencia++){
        cout<<(indiceReferencia/100)*nImagens<<"%"<<endl;
        //cout<<"imagem: "<<nImagens<<endl;
//        string  pasta2Imagem="/home/Normal/";
//        string pasta3Imagem = "";

        // Bloco 1 >> ABRE UMA NOVA IMAGEM COLORIADA (img) E A CONVERTE PARA TONS DE CINZA (imgCinza)
        string caminho1Imagem = imageName[indiceReferencia];	// Pasta de onde serão buscadas as imagens


        cout<<caminho1Imagem<<endl;
        Mat imgCinza =  imread(caminho1Imagem,0);
//        namedWindow("mostra");
//        imshow("mostra", imgCinza);
//        waitKey(0);
//        destroyWindow("mostra");

        if(!imgCinza.data)
        {
            cout <<  "Imagem nao encontrada" << std::endl ;
            //return 0;
        }else{
              cout<<"Imagem encontrada"<<endl;
        }
    // FIM DE BLOCO 1

    // Bloco 2 >> coletas pontos do Arquivo
        int valor; char espaco;
        int ***pontos;
        pontos = (int***) malloc( nImagens * sizeof (int**));
        for (int i = 0; i < nImagens; ++i){
            pontos[i] = (int**) malloc( nAmostras * sizeof (int*));
            for (int j = 0; j < nAmostras; ++j){
                pontos[i][j] = (int*) malloc( 2 * sizeof (int));
            }
        }
//FILE *arq2 = fopen("Normal2.txt", "w");
        FILE *arq = fopen("pontosNormais.txt", "r");	// Cria um arquivo texto para gravaįão dos pontos
        if (arq == NULL)				// Se nāo conseguiu criar
        {
            printf("Problemas na leitura do arquivo de pontos Normais\n");
            system("pause");
        } else {
            for (int i = 0; i < nImagens; i++){
                for (int j = 0; j < nAmostras; j++){
                    for (int l = 0; l < 2; ++l){
                        fscanf(arq,"%d%c",&valor,&espaco);
                        pontos[i][j][l] = valor;
                    }
                }
            }
            fclose(arq);

        }

        cout<<"passou aqui"<<endl;
    // FIM DE BLOCO 2

    // Bloco 3 >> EXTRAI A VINZINHAĮA DE CADA PIXEL REFERENCIADO PELO USUÁRIO
        int masc = 9; // Tamanho da vizinhanįa: masc x masc
        int** amostras = (int**) malloc(nAmostras * sizeof (int*));
            for (int i = 0; i < nAmostras; ++i)
               amostras[i] = (int*) malloc( masc*masc * sizeof (int));

        float f = (masc/2.0)-0.5;
        int fator = (int)f;
        int x,y, cont;

//cout <<"linhas: "<< imgCinza.rows;

        for(int i=0; i<nAmostras; i++)
        {
            cout<<"Imagem:"<<indiceReferencia<<" ; "<<"Amostra: "<<i<<endl;
            //cout<<"amostra: "<<i<<endl;
            y = pontos[indiceReferencia][i][0];
            x = pontos[indiceReferencia][i][1];
            //cout<<"x="<<x<<" y="<<y<<"\n";
            //system("pause");

            cont=0;
            for(int a=0; a<masc; a++)
            {
              //  cout<<cont<<endl;
    //            cout<<"Passou aqui"<<endl;
                for(int b=0; b<masc; b++){
                  //  cout<<"Passou aqui - ponto: ("<<y+a-fator<<", "<< x+b-fator<<")"<<endl;
                    amostras[i][cont] = (int) imgCinza.at<uchar>(y+b-fator,x+a-fator);
                    cont++;
              //      cout<<cont<<endl;
                }
            }
        }

       // cout<<"Passou aqui"<<endl;
        //pontos = Liberar_matriz_real(nAmostras, 2, pontos);
        for (int i=0; i < nImagens; i++){
            for (int j=0; j<nAmostras; j++) {
                free (pontos[i][j]);
            }
            free (pontos[i]);
        }
        free (pontos);
    // FIM DE BLOCO 3

    // Bloco 4 >> EXTRAI OS DESCRITORES DE TEXTURA
        int tone_count=255; /* number of tones actually in the img. atleast 1 less than 255 */
        float **P_matrix;

        int **grays;
        grays = (int**) malloc( masc * sizeof (int*));
            for (int i = 0; i < masc; ++i)
               grays[i] = (int*) malloc( masc * sizeof (int));

        double desc[14];
        FILE* arquivo = abrirArquivo("DescritoresNormais.txt");
        for(int am=0; am<nAmostras; am++)
        {

           // cout<<"Eitaaaa mizera"<<endl;
            cont=0;
            for(int i=0; i<masc; i++)
            {
                for(int j=0; j<masc; j++)
                {
                    grays[i][j]=amostras[am][cont];
                    cont++;
                }
            }
            cout<<"1";
            int rows = masc;
            int cols = masc;

            P_matrix = CoOc_simetrH_Mat (grays, rows, cols, 0, tone_count);

           //desc[13] = f14_ccm(P_matrix,tone_count);

            desc[0] = f1_asm(P_matrix,tone_count);
            desc[1] = f2_contrast(P_matrix, tone_count);
            desc[2] = f3_corr(P_matrix,tone_count);
            desc[3] = f4_var(P_matrix, tone_count);
            desc[4] = f5_idm(P_matrix, tone_count);
            desc[5] = f6_savg(P_matrix, tone_count);
            desc[7] = f8_sentropy(P_matrix, tone_count);
            desc[6] = f7_svar(P_matrix,desc[7],tone_count);
            desc[8] = f9_entropy(P_matrix,tone_count);
            desc[9] = f10_dvar(P_matrix, tone_count);
            desc[10] = f11_dentropy(P_matrix, tone_count);
            desc[11] = f12_icorr(P_matrix, tone_count);
            desc[12] = f13_icorr(P_matrix, tone_count);
           

            cout<<"entrou aqui";


            
            
            
            
            
            //2Š combinaįão
            //desc[0] = f1_asm(P_matrix, tone_count);
            //desc[1] = f5_idm(P_matrix, tone_count);
            //desc[2] = f6_savg(P_matrix, tone_count)/100;

            //3Š combinaįão
            //desc[0] = f1_asm(P_matrix, tone_count);
            //desc[1] = f3_corr(P_matrix, tone_count);
            //desc[2] = f6_savg(P_matrix, tone_count)/100;

            x=indiceReferencia;
            y=am;
            for(z=0; z<13; z++){
                descritores[x][y][z]=desc[z]; //Imagem x, no ponto y, descritor z;
                //cout<<desc[z]<<endl;    //[x*largura*profundidade+y*largura+z] =desc[z];
            }

            if (gravarDados(13, desc, arquivo)==true)
                cout<<"Gravando Descritores"<<endl;
            else cout<<"erro em arquivo de descritores!\n";
            P_matrix = Liberar_matriz_float (tone_count, tone_count, P_matrix);
            double **P_matrix;
        }
        fecharArquivo(arquivo);
    }
    return descritores;
// FIM DE BLOCO 4
}
