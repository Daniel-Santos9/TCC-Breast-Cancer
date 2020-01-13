#include "treinamento.h"
#include "descritores.h"
#include "gravaDados.h"
#include "mlp.h"
#include "pdi.h"

double*** calc_desc(string pasta1Imagem, int nImagens, int nAmostras, /*double matriz[][40][3],*/ int altura, int largura, int profundidade) {
	string nomeImagem[10] = {"imagem0.jpg", "imagem1.jpg", "imagem2.jpg", "imagem3.jpg", "imagem4.jpg","imagem5.jpg", "imagem6.jpg", "imagem7.jpg", "imagem8.jpg", "imagem9.jpg"};

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

	for(int indiceReferencia=0; indiceReferencia< nImagens; indiceReferencia++){
		cout<<"imagem   "<<indiceReferencia<<"\n";
		// Bloco 1 >> ABRE UMA NOVA IMAGEM COLORIADA (img) E A CONVERTE PARA TONS DE CINZA (imgCinza)
		string caminho1Imagem = pasta1Imagem+nomeImagem[indiceReferencia];	// Pasta de onde serão buscadas as imagens	

		IplImage* imgCinza =  cvLoadImage(caminho1Imagem.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
		if(!imgCinza)
		{
			cout <<  "Imagem nao encontrada" << std::endl ;
			//return 0;
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

		FILE *arq = fopen("pontos.txt", "r");	// Cria um arquivo texto para gravação dos pontos
		if (arq == NULL)				// Se nào conseguiu criar
		{
			printf("Problemas na leitura do arquivo de pontos treino\n");
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
	// FIM DE BLOCO 2

	// Bloco 3 >> EXTRAI A VINZINHAÇA DE CADA PIXEL REFERENCIADO PELO USUÁRIO
		int masc = 9; // Tamanho da vizinhança: masc x masc
		int** amostras = (int**) malloc(nAmostras * sizeof (int*));
			for (int i = 0; i < nAmostras; ++i)
			   amostras[i] = (int*) malloc( masc*masc * sizeof (int));

		float f = (masc/2.0)-0.5;
		int fator = (int)f;
		int x,y, cont;
		for(int i=0; i<nAmostras; i++)
		{
			y = pontos[indiceReferencia][i][0];
			x = pontos[indiceReferencia][i][1];
			//cout<<"x="<<x<<" y="<<y<<"\n";
			//system("pause");
			cont=0;
			for(int a=0; a<masc; a++)
			{
				for(int b=0; b<masc; b++){
					amostras[i][cont] = (int)cvGetReal2D(imgCinza, y+a-fator, x+b-fator);
					cont++;
				}
			}
		}
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
	
		double desc[3];

		FILE* arquivo = abrirArquivo("desc_teste02.txt");
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

			int rows = masc;
			int cols = masc;

			P_matrix = CoOc_simetrH_Mat (grays, rows, cols, 0, tone_count);

			//1ª combinação
			desc[0] = f3_corr(P_matrix, tone_count);
			desc[1] = f5_idm(P_matrix, tone_count);
			desc[2] = f6_savg(P_matrix, tone_count)/100;

			//2ª combinação
			//desc[0] = f1_asm(P_matrix, tone_count);
			//desc[1] = f5_idm(P_matrix, tone_count);
			//desc[2] = f6_savg(P_matrix, tone_count)/100;

			//3ª combinação
			//desc[0] = f1_asm(P_matrix, tone_count);
			//desc[1] = f3_corr(P_matrix, tone_count);
			//desc[2] = f6_savg(P_matrix, tone_count)/100;

			x=indiceReferencia;
			y=am;
			for(z=0; z<3; z++){
				descritores[x][y][z]=desc[z];
					//[x*largura*profundidade+y*largura+z] =desc[z];
			}
			if (gravarDados(3, desc, arquivo)==true)
				cout<<"dados salvos em arquivo!\n";
			else cout<<"erro em arquivo de descritores!\n";
			P_matrix = Liberar_matriz_float (tone_count, tone_count, P_matrix);
			double **P_matrix;
		}
		fecharArquivo(arquivo);

		return descritores;
	// FIM DE BLOCO 4

	}

}

void processamento_treinamento(string nomeImagem2, string pasta1Imagem, string pasta2Imagem, string pasta3Imagem, int nPontos, int nImagens, int indiceReferencia) {
	string nomeImagem[10] = {"imagem0.jpg", "imagem1.jpg", "imagem2.jpg", "imagem3.jpg", "imagem4.jpg","imagem5.jpg", "imagem6.jpg", "imagem7.jpg", "imagem8.jpg", "imagem9.jpg"};
	
	int nAmostras = nPontos;

	//double matriz_desc[10][40][3];
	double ***matriz_desc;
	matriz_desc = (double***) malloc( nImagens * sizeof (double**));
	for (int i = 0; i < nImagens; ++i){
		matriz_desc[i] = (double**) malloc( nAmostras * sizeof (double*));
		for (int j = 0; j < nAmostras; ++j){
			matriz_desc[i][j] = (double*) malloc( 3 * sizeof (double));
		}
	}

	matriz_desc = calc_desc(pasta1Imagem, nImagens, 40, /*matriz_desc,*/ 10, 40, 3);

//--------------------------------------------------------------------------------------------
//	ESTRUTURAS PARA A RNA DO BLOCO 5														  |
//--------------------------------------------------------------------------------------------	
	unsigned long inp=3;        // Numero de entradas da RNA
	unsigned long outp=1;       // Numero de saidas
	double** tr_inp = (double**) malloc( nAmostras * sizeof (double*));									
        for (int i = 0; i < nAmostras; ++i)															
           tr_inp[i] = (double*) malloc( inp * sizeof (double)); // Vetor de entradas para treinamento
																								
	double** tr_out = (double**) malloc( nAmostras * sizeof (double*));										
        for (int i = 0; i < nAmostras; ++i)														
           tr_out[i] = (double*) malloc( outp * sizeof (double)); // Vetor de saidas desejadas	
	
	cout<<"Pressione qualquer tecla para iniciar o refistro de saidas desejadas\n";
	//std::system("pause");
	for(int i=0; i<nAmostras; i++)
    {
		for(int j=0; j<outp; j++)
		{
			//cout<<"Digite a saida desejada do neuronio "<<j<<" para a "<<i+1<<"a. amostra\n";
			//cin>>tr_out[i][j];
			if(i<10)
				tr_out[i][j]=1;
			else
				tr_out[i][j]=0;
		}
	}

	MLP rna; // Cria objeto tipo MLP (rede neural)

    unsigned long hid=3;       // Numero de neuronios escondidos
    unsigned long layers[3];    // Vetor para definição das camadas
    layers[0]=inp;              // Definição da primeira camada (de entradas): 2 elementos
    layers[1]=hid;              // Definição da segunda camada (de neuronios escondidos): 2 elementos
    layers[2]=outp;             // Definição da terceira camada (de neuronios de saida): 1 elemento
    double *outputs;            // Utilizada nos testes
	float taxaAprend = 0.35;   // Taxa de aprendizagem
    unsigned long iter=0;       // Contador de épocas

	//cout<<"Entre com o numero de epocas: ";
    //cin>>iter;
	iter=3000;

	//rna.SetDataRPROP(layers,3);
	rna.SetData(taxaAprend, layers,3);
	rna.RandomizeWB();  // Gera pesos aleatorios para pesos e bias
	rna.carregarPesos("pesos1.txt");
//-----------------------------------------------------------------------------------------


	//if (indiceReferencia<nImagens){	// IF seletor
	
	float perc=0, max=iter-1;
	for(int i=0;i<iter;i++){
		perc=(i*100.0)/max;
		system ("cls"); 
		cout<<perc<<"% concluido (treino).\n";

//// Bloco 1 >> ABRE UMA NOVA IMAGEM COLORIADA (img) E A CONVERTE PARA TONS DE CINZA (imgCinza)	
//	string caminho1Imagem = pasta1Imagem+nomeImagem;	// Pasta de onde serão buscadas as imagens
//	string caminho2Imagem = pasta2Imagem+nomeImagem;	// Pasta onde as images da MLP serao salvas
//	string caminho3Imagem = pasta3Imagem+nomeImagem;	// Pasta onde as images binarizadas serao salvas
//
//	for(int indiceReferencia=0; indiceReferencia< 10 /*nImagens*/; indiceReferencia++){
//	IplImage* imgCinza =  cvLoadImage(caminho1Imagem.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
//    if(!imgCinza)
//    {
//        cout <<  "Imagem nao encontrada" << std::endl ;
//        return;
//    }
//// FIM DE BLOCO 1
//
//// Bloco 2 >> coletas pontos do Arquivo
//	int valor; char espaco;
//	int ***pontos;
//    pontos = (int***) malloc( nImagens * sizeof (int**));
//    for (int i = 0; i < nImagens; ++i){
//		pontos[i] = (int**) malloc( nAmostras * sizeof (int*));
//		for (int j = 0; j < nAmostras; ++j){
//			pontos[i][j] = (int*) malloc( 2 * sizeof (int));
//		}
//	}
//
//	FILE *arq = fopen("pontos.txt", "r");	// Cria um arquivo texto para gravação dos pontos
//	if (arq == NULL)				// Se nào conseguiu criar
//	{
//		printf("Problemas na leitura do arquivo de pontos treino\n");
//		system("pause");
//	} else {
//		for (int i = 0; i < nImagens; i++){
//			for (int j = 0; j < nAmostras; j++){
//				for (int l = 0; l < 2; ++l){
//					fscanf(arq,"%d%c",&valor,&espaco);
//					pontos[i][j][l] = valor;
//				}
//			}
//		}
//		fclose(arq);
//	}
//// FIM DE BLOCO 2
//
//// Bloco 3 >> EXTRAI A VINZINHAÇA DE CADA PIXEL REFERENCIADO PELO USUÁRIO
    
//	for(int i=0; i<nAmostras; i++)
//    {
//		y = pontos[indiceReferencia][i][0];
//		x = pontos[indiceReferencia][i][1];
//		//cout<<"x="<<x<<" y="<<y<<"\n";
//		//system("pause");
//        cont=0;
//        for(int a=0; a<masc; a++)
//        {
//            for(int b=0; b<masc; b++){
//                amostras[i][cont] = (int)cvGetReal2D(imgCinza, y+a-fator, x+b-fator);
//                cont++;
//            }
//        }
//    }
//	//pontos = Liberar_matriz_real(nAmostras, 2, pontos);
//	for (int i=0; i < nImagens; i++){ 
//		for (int j=0; j<nAmostras; j++) {
//			free (pontos[i][j]);  
//		}
//		free (pontos[i]);
//	}
//	free (pontos); 
//// FIM DE BLOCO 3
//
//// Bloco 4 >> EXTRAI OS DESCRITORES DE TEXTURA
    
//
//	FILE* arquivo = abrirArquivo("desc_teste.txt");
//	for(int am=0; am<nAmostras; am++)
//	{
//		cont=0;
//		for(int i=0; i<masc; i++)
//		{
//			for(int j=0; j<masc; j++)
//			{
//				grays[i][j]=amostras[am][cont];
//				cont++;
//			}
//		}
//
//		//grays[0][0]=0; grays[0][1]=0; grays[0][2]=1; grays[0][3]=1;grays[0][4]=1;
//		//grays[1][0]=0; grays[1][1]=0; grays[1][2]=1; grays[1][3]=1;grays[1][4]=2;
//		//grays[2][0]=0; grays[2][1]=2; grays[2][2]=2; grays[2][3]=2;grays[2][4]=1;
//		//grays[3][0]=2; grays[3][1]=2; grays[3][2]=3; grays[3][3]=3;grays[3][4]=3;
//		//grays[4][0]=2; grays[4][1]=2; grays[4][2]=3; grays[4][3]=3;grays[4][4]=3;
//
//		int rows = masc;
//		int cols = masc;
//
//		P_matrix = CoOc_simetrH_Mat (grays, rows, cols, 0, tone_count);
//
//		double correlation = f3_corr(P_matrix, tone_count);
//		//cout<<"correlacao: "<<correlation<<"\n";
//
//		double idm = f5_idm(P_matrix, tone_count);
//		double se = f6_savg(P_matrix, tone_count);
//		//double cor2 = f13_icorr(P_matrix, tone_count);
//
//		//cout<<"homogeneidade: "<<idm<<"\n";
//		//cout<<"soma das medias?: "<<se<<"\n";
//		//cout<<"correl 2?: "<<cor2<<"\n";
//		desc[0]=correlation; desc[1]=idm; desc[2]=se/100; //desc[3]=cor2;
//		for(int j=0; j<3; j++){
//			tr_inp[am][j]=desc[j];
//		}
//		if (gravarDados(3, desc, arquivo)==true)
//			cout<<"dados salvos em arquivo!\n";
//		P_matrix = Liberar_matriz_float (tone_count, tone_count, P_matrix);
//		double **P_matrix;
//	}
//	fecharArquivo(arquivo);
//// FIM DE BLOCO 4

// Bloco 5 >> CLASSIFICAÇÃO COM RNA MLP
	
    //rna.SetData(taxaAprend,layers,3); // Configura rede com: Taxa de aprendizado, vetor de camadas, 3 camadas
	//rna.RandomizeWB();  // Gera pesos aleatorios para pesos e bias
	//rna.carregarPesos("pesos1.txt");
    
	//FILE* arquivo2 = abrirArquivo("erro_hist.txt");

	
	//double erroMedioGlobal=0;
	//double* vet_erros;
	
	//vet_erros = (double*) malloc( iter * sizeof (double));

	//cout<<"\nTreinando rede MLP... \n";
	for(int imRef=0; imRef < nImagens; imRef++){
		for(int am=0; am<nAmostras; am++) {

			for(int j=0; j<3; j++){
				tr_inp[am][j]=matriz_desc[imRef][am][j];
			}
    
			//if(i%1000==0)cout<<"\n"<<i+1<<"a. epoca";
			//erroMedioGlobal=0;
			for(int j=0;j<nAmostras ;j++){

				//rna.TrainRPROP(tr_inp[j],tr_out[j],1);

				rna.Train(tr_inp[j],tr_out[j]); // Treina rede com: Entradas e saidas desejadas
			
				//erroMedioGlobal += rna.ErroMedioIns/nAmostras;
			}
			//vet_erros[i]=erroMedioGlobal;

		
	//gravarDados(iter, vet_erros, arquivo2);
	//fecharArquivo(arquivo2);
		}
	  }
	}
	cout<<"Treinamento Finalizado."<<std::endl;
	rna.salvarPesos("pesos12.txt");

	for (int i = 0; i < nImagens; ++i){
		for (int j = 0; j < nAmostras; ++j){
			free(matriz_desc[i][j]);
		}
		free(matriz_desc[i]);
	}
	free(matriz_desc);

	//rna.carregarPesos("pesos00.txt");
	//system("pause");
// FIM DE BLOCO 5

//// Bloco 6 >> TESTE DA RNA MLP
//	
//	int masc = 9; // Tamanho da vizinhança: masc x masc
//    int** amostras = (int**) malloc(nAmostras * sizeof (int*));
//        for (int i = 0; i < nAmostras; ++i)
//           amostras[i] = (int*) malloc( masc*masc * sizeof (int));
//
//    float f = (masc/2.0)-0.5;
//    int fator = (int)f;
//    int x,y, cont;
//
//	int tone_count=255; /* number of tones actually in the img. atleast 1 less than 255 */
//    float **P_matrix;
//
//    int **grays;
//    grays = (int**) malloc( masc * sizeof (int*));
//        for (int i = 0; i < masc; ++i)
//           grays[i] = (int*) malloc( masc * sizeof (int));
//	
//	double desc[3];
//
//
//	cout<<"\n\nInciando testes da RNA... \n";
//	for(int imRef=0; imRef < nImagens; imRef++){
//		string caminho1Imagem = pasta1Imagem+nomeImagem[imRef];	// Pasta de onde serão buscadas as imagens	
//		string caminho2Imagem = pasta2Imagem+nomeImagem[imRef];
//		string caminho3Imagem = pasta3Imagem+nomeImagem[imRef];
//
//		IplImage* imgCinza =  cvLoadImage(caminho1Imagem.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
//		if(!imgCinza)
//		{
//			cout <<  "Imagem nao encontrada" << std::endl ;
//			return;
//		}
//
//		//P_matrix = Liberar_matriz_real (tone_count, tone_count, P_matrix);
//		IplImage* testeMLP = cvCreateImage(cvGetSize( imgCinza ) , IPL_DEPTH_8U , 1);
//		cvZero(testeMLP);
//
//		CvScalar pix;
//		perc=0;
//
//		max=imgCinza->height-masc;
//		//arquivo = abrirArquivo();
//		for(int i=0+masc; i<imgCinza->height-masc; i++)
//		{
//			perc=(i*100.0)/max;
//			system ("cls"); 
//			cout<<perc<<"% concluido (teste).\n";
//			for(int j=0+masc; j<imgCinza->width-masc; j++)
//			{
//				if(cvGetReal2D(imgCinza, i, j)<=200)
//				{
//					cont=0;
//					for(int a=0; a<masc; a++)
//					{
//						for(int b=0; b<masc; b++){
//							amostras[0][cont] = (int)cvGetReal2D(imgCinza, i+a-fator, j+b-fator);
//							cont++;
//						}
//					}
//					cont=0;
//					for(int i=0; i<masc; i++)
//					{
//						for(int j=0; j<masc; j++)
//						{
//							grays[i][j]=amostras[0][cont];
//							cont++;
//						}
//					}
//			
//					int rows = masc;
//					int cols = masc;
//					P_matrix = CoOc_simetrH_Mat (grays, rows, cols, 0, tone_count);
//
//					double correlation = f3_corr(P_matrix, tone_count);
//					//cout<<"correlacao: "<<correlation<<"\n";
//
//					double idm = f5_idm(P_matrix, tone_count);
//					double se = f6_savg(P_matrix, tone_count);
//					//double cor2 = f13_icorr(P_matrix, tone_count);
//
//					//cout<<"homogeneidade: "<<idm<<"\n";
//					//cout<<"soma das medias?: "<<se<<"\n";
//					//cout<<"correl 2?: "<<cor2<<"\n";
//					desc[0]=correlation; desc[1]=idm; desc[2]=se/100; //desc[3]=cor2;
//					for(int j=0; j<3; j++)
//						tr_inp[0][j]=desc[j];
//					//if (gravarDados(3, desc, arquivo)==true)
//					//	cout<<"dados salvos em arquivo!\n";
//					rna.SetInputs(tr_inp[0]); // Oferece entradas para teste simples
//
//					outputs = rna.GetOutput();
//			
//					pix.val[0] = (int)( outputs[0]*255);
//					if (pix.val[0]<0) pix.val[0]=0;
//					if (pix.val[0]>255) pix.val[0]=255;
//					cvSet2D(testeMLP,i,j,pix);
//					P_matrix = Liberar_matriz_float (tone_count, tone_count, P_matrix);
//					double **P_matrix;
//					delete outputs;
//					double *outputs;
//				}
//				else {
//					pix.val[0] = (int)(0);
//					cvSet2D(testeMLP,i,j,pix);
//				}
//			}
//		
//		}
//		//fecharArquivo(arquivo);
//// FIM DE BLOCO 6
//
//// Bloco 7 >> binarização
//		//cvNamedWindow("saida RNA", WINDOW_AUTOSIZE);
//		//cvShowImage("saida RNA", testeMLP);
//		//cvWaitKey(0);
//		int resp0=1;
//		if (resp0==1){
//			int p[3];
//			p[0] = CV_IMWRITE_JPEG_QUALITY;
//			p[1] = 100;
//			p[2] = 0;
//			cvSaveImage(caminho2Imagem.c_str(), testeMLP, p) ;
//		}
//
//		//system("pause");
//		
//		IplImage* im_bw = cvCreateImage(cvGetSize( testeMLP ),IPL_DEPTH_8U,1);
//		//cvThreshold(testeMLP, im_bw, 200, 250, CV_THRESH_BINARY | CV_THRESH_OTSU); 
//		im_bw = limiarOtsu(testeMLP);
//
//		/*
//		CvTracks tracks;
//		IplImage* im_blob = cvCreateImage(cvGetSize(testeMLP),IPL_DEPTH_8U,1);
//		IplImage* frame = cvCreateImage(cvGetSize(testeMLP),IPL_DEPTH_8U,1);
//		CvBlobs blobs;
//		unsigned int result = cvLabel(im_bw, im_blob, blobs);
//		cvFilterByArea(blobs, 500, 1000000);
//		cvRenderBlobs(im_blob, blobs, frame, frame, CV_BLOB_RENDER_BOUNDING_BOX);
//		cvUpdateTracks(blobs, tracks, 200., 5);
//		cvRenderTracks(tracks, frame, frame, CV_TRACK_RENDER_ID|CV_TRACK_RENDER_BOUNDING_BOX);
//
//		cvNamedWindow("red_object_tracking", WINDOW_AUTOSIZE);
//		cvShowImage("red_object_tracking", frame);
//		*/
//		int resp=0;
//		//cout << "deseja salvar a imagem binarizada? [Digite 1 para SIM e 0 para NAO]" << endl;
//		//cin>> resp;
//		resp=1;
//		if (resp==1){
//			int p[3];
//			p[0] = CV_IMWRITE_JPEG_QUALITY;
//			p[1] = 100;
//			p[2] = 0;
//			cvSaveImage(caminho3Imagem.c_str(), im_bw, p) ;
//		}
	
//// FIM DE BLOCO 7
 // IF seletor
}
