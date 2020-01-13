#include "cruzaFuncPonteiros.h"
#include "QTime"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "QString"

using namespace std;
using namespace cv;

vetDescritor descritor[] = {
    f1_asm,					//segundo momento angular 0
    f2_contrast,			//contraste                1 Esse
    f3_corr,				//correlacao              2
    //f4_var,					//variancia
    f5_idm,					//hogeneidade               3
    f6_savg,				//soma das medias           4 Esse
    //f8_sentropy,			//soma da entropia
    f7_svar,				//soma da variancia         5 Esse
    //f9_entropy,				//entropia
    f10_dvar,				//diferen�a da variancia  6
    f11_dentropy			//diferen�a da entropia    7
    //f12_icorr,				//informa��es de correla��o 1
    //f13_icorr				//informa��es de correla��o 2
};

void cruzaTres(string nomeImagem, string pasta1Imagem, string pasta2Imagem, int numAmostras, int controle){
     int inicio, final, tempo=0;
     double tmili[40];
     QTime t;
     t.start();

for(int descr1=0; descr1<8; descr1++){
    for(int descr2=(descr1+1); descr2<8; descr2++){
        for(int descr3=(descr2+1); descr3<8; descr3++){

//            if (descr1==0 && descr2==1 && descr3==2){
//                descr1=7;
//                descr2=10;
//                descr3=11;
//            }
//-------------------------------------------------------------------------------------------
// Bloco 1 >> ABRE UMA NOVA IMAGEM COLORIADA (img) E A CONVERTE PARA TONS DE CINZA (imgCinza)
//-------------------------------------------------------------------------------------------
    descr1=1;
    descr2=4;
    descr3=5;
    QString desc1 = QString::number(descr1);
    QString desc2 = QString::number(descr2);
    QString desc3 = QString::number(descr3);

    string codigo = desc1.toStdString() + desc2.toStdString() + desc3.toStdString();
    string caminho1Imagem = pasta1Imagem+nomeImagem;
    string caminho2Imagem = pasta2Imagem+codigo+nomeImagem;

    Mat imgCinza;

    imgCinza =  imread(caminho1Imagem,0);
    if(imgCinza.empty())
    {
        cout <<  "Imagem nao encontrada" << std::endl ;
        return;
    }
// FIM DE BLOCO 1

//-----------------------------------------------------------------------
// Bloco 2 >> Carrega pontos de amostras a aprtir de um arquivo de texto
//-----------------------------------------------------------------------
    int nAmostras=numAmostras;
    int **pontos;
    pontos = (int**) malloc( nAmostras * sizeof (int*));
        for (int i = 0; i < nAmostras; ++i)
           pontos[i] = (int*) malloc( 2 * sizeof (int));

        FILE *arq;

        if(controle<1){
            arq = fopen("PontosTestes\\Doentes.txt", "r");	// Abrir um arquivo texto para leitura
            cout<< "Abriu os doentes";
        }
        else{
            arq = fopen("PontosTestes\\Normal.txt", "r");	// Abrir um arquivo texto para leitura
            cout<<"Abriu Normais";
             }
        if (arq == NULL)				// Se n�o conseguiu abrir
        {
            printf("Problemas na ABERTURA do arquivo\n");
            return;
        }
    int c;
    char v; //c=valor int e v=virgula
    for(int i=0; i<nAmostras; i++){
        for(int j=0; j<2; j++){
            fscanf(arq,"%d%c",&c,&v);
            pontos[i][j] = c;
        }
    }
    fecharArquivo(arq);
// Fim de Bloco 2

//------------------------------------------------------------------------
// Bloco 3 >> EXTRAI A VINZINHA�A DE CADA PIXEL REFERENCIADO PELO ARQUIVO
//------------------------------------------------------------------------
    int masc = 3; // Tamanho da vizinhan�a: masc x masc
    int** amostras = (int**) malloc( nAmostras * sizeof (int*));
        for (int i = 0; i < nAmostras; ++i)
           amostras[i] = (int*) malloc( masc*masc * sizeof (int));

    float f = (masc/2.0)-0.5;
    int fator = (int)f;
    int x,y, cont;
    for(int i=0; i<nAmostras; i++)
    {
        y = pontos[i][0];
        x = pontos[i][1];
        cont=0;
        for(int a=0; a<masc; a++)
        {
            for(int b=0; b<masc; b++){
                amostras[i][cont] = (int)imgCinza.at<uchar> (y+a-fator, x+b-fator);
                cont++;
            }
        }
    }

    //pontos = Liberar_matriz_real(nAmostras, 2, pontos);
// FIM DE BLOCO 3

//--------------------------------------------------------------------------------------------
// Bloco 4 >> Setup da RNA
//--------------------------------------------------------------------------------------------
    unsigned long inp=3;        // Numero de entradas da RNA
    unsigned long outp=1;       // Numero de saidas
    double** tr_inp = (double**) malloc( nAmostras * sizeof (double*));
        for (int i = 0; i < nAmostras; ++i)
           tr_inp[i] = (double*) malloc( inp * sizeof (double)); // Vetor de entradas para treinamento
																								
    double** tr_out = (double**) malloc( nAmostras * sizeof (double*));
        for (int i = 0; i < nAmostras; ++i)
           tr_out[i] = (double*) malloc( outp * sizeof (double)); // Vetor de saidas desejadas
	
    cout<<"Pressione qualquer tecla para iniciar o registro de saidas desejadas\n";
//	std::system("pause");
    FILE* arquivo2 = fopen("Saidas\\teste2.txt", "r");
    if (arq == NULL)				// Se n�o conseguiu abrir
    {
        printf("Problemas na ABERTURA do arquivo de saidas desejadas\n");
        return;
    }
    for(int i=0; i<nAmostras; i++)
    {
        for(int j=0; j<outp; j++)
        {
            //cout<<"Digite a saida desejada do neuronio "<<j<<" para a "<<i+1<<"a. amostra\n";
            //cin>>tr_out[i][j];
            fscanf(arquivo2,"%d%c",&c,&v);
            tr_out[i][j]=c;
        }
    }
    fecharArquivo(arquivo2);
// Fim de Bloco 4

//---------------------------------------------
// Bloco 5 >> EXTRAI OS DESCRITORES DE TEXTURA
//---------------------------------------------
    int tone_count=255; /* number of tones actually in the img. atleast 1 less than 255 */
    float **P_matrix;

    int **grays;
    grays = (int**) malloc( masc * sizeof (int*));
        for (int i = 0; i < masc; ++i)
           grays[i] = (int*) malloc( masc * sizeof (int));
	
    double desc[3];

    FILE* arquivo = abrirArquivo("desc_teste.txt");
    for(int am=0; am<nAmostras; am++)
    {
        cont=0;
        for(int i=0; i<masc; i++)
        {
            for(int j=0; j<masc; j++)
            {
                grays[i][j]=amostras[am][cont];
                cont++;
            }
        }

//    for(int i=0; i<12; i++){
//        for(int j=(i+1); j<12; j++){

//        }
//    }
    int rows = masc;
    int cols = masc;

    P_matrix = CoOc_simetrH_Mat (grays, rows, cols, 0, tone_count);

    //double correlation = f3_corr(P_matrix, tone_count);
    //double idm = f5_idm(P_matrix, tone_count);
    //double se = f6_savg(P_matrix, tone_count);

    //calculo de descritores com vetor de fun��es (sorteio din�mico 3 a 3):
    double correlation = descritor[descr1](P_matrix, tone_count);
    double idm = descritor[descr2](P_matrix, tone_count);
    double se = descritor[descr3](P_matrix, tone_count);
	

    desc[0]=correlation; desc[1]=idm; desc[2]=se; //desc[3]=cor2;
        for(int j=0; j<3; j++){
            tr_inp[am][j]=desc[j];
        }
        if (gravarDados(3, desc, arquivo)==true)
            cout<<"dados salvos em arquivo!\n";
        P_matrix = Liberar_matriz_float (tone_count, tone_count, P_matrix);
        double **P_matrix;
    }
    fecharArquivo(arquivo);
// FIM DE BLOCO 4

//--------------------------------------
// Bloco 6 >> TREINAMENTO DA RNA MLP
//--------------------------------------
    MLP rna; // Cria objeto tipo MLP (rede neural)

    unsigned long hid=3;       // Numero de neuronios escondidos
    unsigned long layers[3];    // Vetor para defini��o das camadas
    layers[0]=inp;              // Defini��o da primeira camada (de entradas): 2 elementos
    layers[1]=hid;              // Defini��o da segunda camada (de neuronios escondidos): 2 elementos
    layers[2]=outp;             // Defini��o da terceira camada (de neuronios de saida): 1 elemento
    double *outputs;            // Utilizada nos testes
    float taxaAprend = 0.4;   // Taxa de aprendizagem
    unsigned long iter=0;       // Contador de �pocas

    cout<<"Entre com o numero de epocas: ";
    //cin>>iter;
    iter=1000;

    rna.SetData(taxaAprend,layers,3); // Configura rede com: Taxa de aprendizado, vetor de camadas, 3 camadas
    rna.RandomizeWB();  // Gera pesos aleatorios para pesos e bias

    cout<<"\nTreinando rede MLP... \n";

    FILE* arquivo3 = abrirArquivo("erro_hist.txt");

    float perc=0, max=iter-1;
    double erroMedioGlobal=0;
    double* vet_erros;
	
    vet_erros = (double*) malloc( iter * sizeof (double));

    for(int i=0;i<iter;i++){
        perc=(i*100.0)/max;
        system ("cls");
        cout<<perc<<"% concluido.\n";
        //if(i%1000==0)cout<<"\n"<<i+1<<"a. epoca";
        erroMedioGlobal=0;
        for(int j=0;j<nAmostras ;j++){
            rna.Train(tr_inp[j],tr_out[j]); // Treina rede com: Entradas e saidas desejadas
            erroMedioGlobal += rna.ErroMedioIns/nAmostras;
        }
        vet_erros[i]=erroMedioGlobal;
    }
    gravarDados(iter, vet_erros, arquivo3);
    fecharArquivo(arquivo3);

    cout<<"Treinamento Finalizado."<<std::endl;
    rna.salvarPesos("pesos1.txt");
    //rna.carregarPesos("pesos00.txt");
//	system("pause");
// FIM DE BLOCO 6

//------------------------------
// Bloco 7 >> TESTE DA RNA MLP
//------------------------------
    cout<<"\n\nInciando testes da RNA... \n";
    Mat imgCinza2 =  imread("base2\\mdb005ll.png",0);
    if(imgCinza2.empty())
    {
        cout <<  "Imagem nao encontrada" << std::endl ;
        return;
    }
    cout<<"Linhas:"<<imgCinza2.rows<<" Colunas:"<<imgCinza2.cols<<endl;

    //P_matrix = Liberar_matriz_real (tone_count, tone_count, P_matrix);
    Mat testeMLP(imgCinza2.rows, imgCinza2.cols, CV_8UC1);
    //testeMLP.setTo(cv::Scalar::all(0));
    cout<<"Passou aqui"<<endl;
    Vec3b pix;
    perc=0;
    max=imgCinza2.rows-masc;
    //arquivo = abrirArquivo();
    for(int i=0+masc; i<imgCinza2.rows-masc; i++)
    {
        perc=(i*100.0)/max;
        //system ("cls");
        cout<<"Descritor:"<<descr1<<endl;
        cout<<perc<<"% concluido.\n";
        for(int j=0+masc; j<imgCinza2.cols-masc; j++)
        {
            if((int)imgCinza2.at<uchar>(i,j)>=30)
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
               // free(amostras);
                int rows = masc;
                int cols = masc;
                P_matrix = CoOc_simetrH_Mat (grays, rows, cols, 0, tone_count);
                //double correlation = f3_corr(P_matrix, tone_count);
                //double idm = f5_idm(P_matrix, tone_count);
                //double se = f6_savg(P_matrix, tone_count);

                //calculo de descritores com vetor de fun��es (sorteio din�mico 3 a 3):

                double correlation = descritor[descr1](P_matrix, tone_count);
                double idm = descritor[descr2](P_matrix, tone_count);
                double se = descritor[descr3](P_matrix, tone_count);

                desc[0]=correlation; desc[1]=idm; desc[2]=se; //desc[3]=cor2;
                for(int j=0; j<3; j++)
                    tr_inp[0][j]=desc[j];
                //if (gravarDados(3, desc, arquivo)==true)
                //	cout<<"dados salvos em arquivo!\n";
                rna.SetInputs(tr_inp[0]); // Oferece entradas para teste simples

                outputs = rna.GetOutput();
                              int limiar = (int)( outputs[0]*255);
                              //cout<<"Limiar: "<<limiar<<endl;

                if (limiar<0) {
                    limiar = 0;

//                    testeMLP.at<Vec3b>(Point(j,i))[2] = 0;
//                    testeMLP.at<Vec3b>(Point(j,i))[1] = 0;
//                    testeMLP.at<Vec3b>(Point(j,i))[0] = 0;
                }
                if (limiar>255){
                    limiar=255;
//                    testeMLP.at<Vec3b>(Point(j,i))[2] = 255;
//                    testeMLP.at<Vec3b>(Point(j,i))[1] = 255;
//                    testeMLP.at<Vec3b>(Point(j,i))[0] = 255;
                }

                testeMLP.at<Vec3b>(i,j)[2] = limiar;
                testeMLP.at<Vec3b>(i,j)[1] = limiar;
                testeMLP.at<Vec3b>(i,j)[0] = limiar;

                P_matrix = Liberar_matriz_float (tone_count, tone_count, P_matrix);
                double **P_matrix;
                delete outputs;
                double *outputs;
            }
            else {
                testeMLP.at<Vec3b>(i,j)[2] = 0;
                testeMLP.at<Vec3b>(i,j)[1] = 0;
                testeMLP.at<Vec3b>(i,j)[0] = 0;
            }
        }
		
    }
}

