#include "descritores.h"
#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
using namespace std;
using namespace cv;


double *allocate_vector (int nl, int nh) {
        double *v;

        v = (double *) calloc (1, (unsigned) (nh - nl + 1) * sizeof (double));
        if (!v) fprintf (stderr, "memory allocation failure (allocate_vector) "), exit (1);
        return v - nl;
}

/* Allocates a double matrix with range [nrl..nrh][ncl..nch] */
double **allocate_matrix (int nrl, int nrh, int ncl, int nch)
{
        int i;
        double **m;

        /* allocate pointers to rows */
        m = (double **) malloc ((unsigned) (nrh - nrl + 1) * sizeof (double *));
        if (!m) fprintf (stderr, "memory allocation failure (allocate_matrix 1) "), exit (1);
        m -= ncl;

        /* allocate rows and set pointers to them */
        for (i = nrl; i <= nrh; i++) {
                m[i] = (double *) malloc ((unsigned) (nch - ncl + 1) * sizeof (double));
                if (!m[i]) fprintf (stderr, "memory allocation failure (allocate_matrix 2) "), exit (2);
                m[i] -= ncl;

        }

        /* return pointer to array of pointers to rows */
        return m;
}

float **allocate_matrix_float (int nrl, int nrh, int ncl, int nch)
{
        int i;
        float **m;

        /* allocate pointers to rows */
        m = (float **) malloc ((unsigned) (nrh - nrl + 1) * sizeof (float *));
        if (!m) fprintf (stderr, "memory allocation failure (allocate_matrix 1) "), exit (1);
        m -= ncl;

        /* allocate rows and set pointers to them */
        for (i = nrl; i <= nrh; i++) {
                m[i] = (float *) malloc ((unsigned) (nch - ncl + 1) * sizeof (float));
                if (!m[i]) fprintf (stderr, "memory allocation failure (allocate_matrix 2) "), exit (2);
                m[i] -= ncl;

        }

        /* return pointer to array of pointers to rows */
        return m;
}

double **Liberar_matriz_double (int m, int n, double **v)
{
  int  i;  /* variavel auxiliar */
  if (v == NULL){
	  printf("Nao foi possível desalocar - Erro 01\n");
	  return (NULL);
  }
  if (m < 1 || n < 1) {  /* verifica parametros recebidos */
     printf ("** Erro: Parametro invalido **\n");
     return (v);
     }
  for (i=0; i<m; i++) free (v[i]); /* libera as linhas da matriz */
  free (v);      /* libera a matriz */
  return (NULL); /* retorna um ponteiro nulo */
}

float **Liberar_matriz_float (int m, int n, float **v)
{
  int  i;  /* variavel auxiliar */
  if (v == NULL){
	  printf("Nao foi possível desalocar - Erro 01\n");
	  return (NULL);
  }
  if (m < 1 || n < 1) {  /* verifica parametros recebidos */
     printf ("** Erro: Parametro invalido **\n");
     return (v);
     }
  for (i=0; i<m; i++) free (v[i]); /* libera as linhas da matriz */
  free (v);      /* libera a matriz */
  return (NULL); /* retorna um ponteiro nulo */
}

int **Liberar_matriz_int (int m, int n, int **v)
{
  int  i;  /* variavel auxiliar */
  if (v == NULL){
	  printf("Nao foi possível desalocar - Erro 01\n");
	  return (NULL);
  }
  if (m < 1 || n < 1) {  /* verifica parametros recebidos */
     printf ("** Erro: Parametro invalido **\n");
     return (v);
     }
  for (i=0; i<m; i++) free (v[i]); /* libera as linhas da matriz */
  free (v);      /* libera a matriz */
  return (NULL); /* retorna um ponteiro nulo */
}

/* Compute gray-tone spatial dependence matrix */
float** CoOc_simetrH_Mat (int **grays, int rows, int cols, int nivel_min, int nivel_max)
{
        int  itone, jtone;
        int count=0; /* normalizing factor */
        //printf("entrou ");
        float** matrix = allocate_matrix_float (nivel_min, nivel_max, nivel_min, nivel_max);

        /* zero out matrix */
        for (itone = nivel_min; itone < nivel_max; ++itone){
                for (jtone = nivel_min; jtone < nivel_max; ++jtone){
                        matrix[itone][jtone] = 0;
                }
        }

        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<cols; j++)
            {
                if (j>0){
					
                    matrix[grays[i][j]][grays[i][j-1]]++;
                }
            }
        }
        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<cols; j++)
            {
                if (j+1<cols)
                    matrix[grays[i][j]][grays[i][j+1]]++;

            }
        }
        for(int i=nivel_min; i<nivel_max; i++)
        {
            for(int j=nivel_min; j<nivel_max; j++)
            {
                count+=matrix[i][j];
            }
        }
        /* normalize matrix */
        for (itone = nivel_min; itone < nivel_max; ++itone){
            for (jtone = nivel_min; jtone < nivel_max; ++jtone){
                if (count==0)   /* protect from error */
                    matrix[itone][jtone]=0;
                else{

                    //cout<<matrix[itone][jtone]<<" ";
                    matrix[itone][jtone] /= count;
                   // cout<<matrix[itone][jtone]<<" ";
                }
            }
            //cout<<"\n";
        }

        return matrix;
}



// Angular Second Moment 
//  
//   * The angular second-moment feature (ASM) f1 is a measure of homogeneity
//   * of the image. In a homogeneous image, there are very few dominant
//   * gray-tone transitions. Hence the P matrix for such an image will have
//   * fewer entries of large magnitude.

float f1_asm (float **P, int Ng)
{
  int i, j;
  float sum = 0;

  for (i = 0; i < Ng; ++i)
    for (j = 0; j < Ng; ++j)
      sum += P[i][j] * P[i][j];

  return sum;
}

// Contrast 
//  
//   * The contrast feature is a difference moment of the P matrix and is a
//   * measure of the contrast or the amount of local variations present in an
//   * image.
float f2_contrast (float **P, int Ng)
{
  int i, j, n;
  float sum = 0, bigsum = 0;

  for (n = 0; n < Ng; ++n)
  {
    for (i = 0; i < Ng; ++i)
      for (j = 0; j < Ng; ++j)
	if ((i - j) == n || (j - i) == n)
	  sum += P[i][j];
    bigsum += n * n * sum;

    sum = 0;
  }
  return bigsum;
}

// Correlation 
//  
//   * This correlation feature is a measure of gray-tone linear-dependencies
//   * in the image.
float f3_corr (float **P, int Ng)
{
	int i, j;
    double sum_sqrx = 0, sum_sqry = 0, tmp, *px;
    double meanx =0 , meany = 0 , stddevx, stddevy;

    px = allocate_vector (0, Ng);
    for (i = 0; i < Ng; ++i)
            px[i] = 0;

    /*
    * px[i] is the (i-1)th entry in the marginal probability matrix obtained
    * by summing the rows of p[i][j]
    */
    for (i = 0; i < Ng; ++i)
            for (j = 0; j < Ng; ++j)
                    px[i] += P[i][j];


    /* Now calculate the means and standard deviations of px and py */
    /*- fix supplied by J. Michael Christensen, 21 Jun 1991 */
    /*- further modified by James Darrell McCauley, 16 Aug 1991
    *     after realizing that meanx=meany and stddevx=stddevy
    */
    for (i = 0; i < Ng; ++i) {
            meanx += px[i]*i;
            sum_sqrx += px[i]*i*i;
    }

    /* M. Boland meanx = meanx/(sqrt(Ng)); */
    meany = meanx;
    sum_sqry = sum_sqrx;
    stddevx = sqrt (sum_sqrx - (meanx * meanx));
    stddevy = stddevx;

    /* Finally, the correlation ... */
    for (tmp = 0, i = 0; i < Ng; ++i)
            for (j = 0; j < Ng; ++j)
                        tmp += i*j*P[i][j];

    free(px);
    if (stddevx * stddevy==0) return(1);  /* protect from error */
    else return (tmp - meanx * meany) / (stddevx * stddevy);
}

// Sum of Squares: Variance 
float f4_var (float **P, int Ng)
{
  int i, j;
  float mean = 0, var = 0;

  /*- Corrected by James Darrell McCauley, 16 Aug 1991
   *  calculates the mean intensity level instead of the mean of
   *  cooccurrence matrix elements 
   */
  for (i = 0; i < Ng; ++i)
    for (j = 0; j < Ng; ++j)
      mean += i * P[i][j];

  for (i = 0; i < Ng; ++i)
    for (j = 0; j < Ng; ++j)
      /*  M. Boland - var += (i + 1 - mean) * (i + 1 - mean) * P[i][j]; */
      var += (i - mean) * (i - mean) * P[i][j];

  return var;
}

/* Inverse Difference Moment */
float f5_idm (float **P, int Ng)
{
  int i, j;
  float idm = 0;

  for (i = 0; i < Ng; ++i)
    for (j = 0; j < Ng; ++j)
      idm += P[i][j] / (1 + (i - j) * (i - j));

  return idm;
}

/* Sum Average */
float f6_savg (float **P, int Ng)
{
    int i, j;
    double savg = 0;
    double *Pxpy = allocate_vector (0, 2*Ng);

    for (i = 0; i <= 2 * Ng; ++i)
            Pxpy[i] = 0;

    for (i = 0; i < Ng; ++i)
            for (j = 0; j < Ng; ++j)
                /* M. Boland Pxpy[i + j + 2] += P[i][j]; */
                /* Indexing from 2 instead of 0 is inconsistent with rest of code*/
                Pxpy[i + j] += P[i][j];

    /* M. Boland for (i = 2; i <= 2 * Ng; ++i) */
    /* Indexing from 2 instead of 0 is inconsistent with rest of code*/
    for (i = 0; i <= (2 * Ng - 2); ++i)
            savg += i * Pxpy[i];

    free (Pxpy);
    return savg;
}

/* Sum Variance */
float f7_svar (float **P, float S, int Ng)
{
  int i, j;
  double *Pxpy = allocate_vector (0, 2*Ng);
  float var = 0;

  for (i = 0; i <= 2 * Ng; ++i)
    Pxpy[i] = 0;

  for (i = 0; i < Ng; ++i)
    for (j = 0; j < Ng; ++j)
      /* M. Boland Pxpy[i + j + 2] += P[i][j]; */
      /* Indexing from 2 instead of 0 is inconsistent with rest of code*/
      Pxpy[i + j] += P[i][j];

  /*  M. Boland for (i = 2; i <= 2 * Ng; ++i) */
  /* Indexing from 2 instead of 0 is inconsistent with rest of code*/
  for (i = 0; i <= (2 * Ng - 2); ++i)
    var += (i - S) * (i - S) * Pxpy[i];

  free (Pxpy);
  return var;
}

/* Sum Entropy */
float f8_sentropy (float **P, int Ng)
{
  int i, j;
  double *Pxpy = allocate_vector (0, 2*Ng);
  float sentropy = 0;

  for (i = 0; i <= 2 * Ng; ++i)
    Pxpy[i] = 0;

  for (i = 0; i < Ng; ++i)
    for (j = 0; j < Ng; ++j)
      Pxpy[i + j + 2] += P[i][j];

  for (i = 2; i <= 2 * Ng; ++i)
    /*  M. Boland  sentropy -= Pxpy[i] * log10 (Pxpy[i] + EPSILON); */
    sentropy -= Pxpy[i] * log10 (Pxpy[i] + EPSILON)/log10(2.0) ;

  free (Pxpy);
  return sentropy;
}

/* Entropy */
float f9_entropy (float **P, int Ng)
{
  int i, j;
  float entropy = 0;

  for (i = 0; i < Ng; ++i)
    for (j = 0; j < Ng; ++j)
      /*      entropy += P[i][j] * log10 (P[i][j] + EPSILON); */
      entropy += P[i][j] * log10 (P[i][j] + EPSILON)/log10(2.0) ;

  return -entropy; 
}

/* Difference Variance */
float f10_dvar (float **P, int Ng)
{
  int i, j, tmp;
  double *Pxpy = allocate_vector (0, 2*Ng);
  float sum = 0, sum_sqr = 0, var = 0;

  for (i = 0; i <= 2 * Ng; ++i)
    Pxpy[i] = 0;

  for (i = 0; i < Ng; ++i)
    for (j = 0; j < Ng; ++j)
      Pxpy[abs (i - j)] += P[i][j];

  /* Now calculate the variance of Pxpy (Px-y) */
  for (i = 0; i < Ng; ++i)
  {
    sum += i * Pxpy[i] ;
    sum_sqr += i * i * Pxpy[i] ;
    /* M. Boland sum += Pxpy[i];
    sum_sqr += Pxpy[i] * Pxpy[i];*/
  }
  /*tmp = Ng * Ng ;  M. Boland - wrong anyway, should be Ng */
  /*var = ((tmp * sum_sqr) - (sum * sum)) / (tmp * tmp); */
  
  var = sum_sqr - sum*sum ;

  free (Pxpy);
  return var;
}

/* Difference Entropy */
float f11_dentropy (float **P, int Ng)
{
  int i, j, tmp;
  double *Pxpy = allocate_vector (0, 2*Ng);
  float sum = 0, sum_sqr = 0, var = 0;

  for (i = 0; i <= 2 * Ng; ++i)
    Pxpy[i] = 0;

  for (i = 0; i < Ng; ++i)
    for (j = 0; j < Ng; ++j)
      Pxpy[abs (i - j)] += P[i][j];

  for (i = 0; i < Ng; ++i)
    /*    sum += Pxpy[i] * log10 (Pxpy[i] + EPSILON); */
    sum += Pxpy[i] * log10 (Pxpy[i] + EPSILON)/log10(2.0) ;

  free (Pxpy);
  return -sum;
}

/* Information Measures of Correlation */
/* All /log10(2.0) added by M. Boland */
float f12_icorr (float **P, int Ng)
{
	int i, j;
	double *px, *py;
	double hx = 0, hy = 0, hxy = 0, hxy1 = 0, hxy2 = 0;

	px = allocate_vector (0, Ng);
	py = allocate_vector (0, Ng);

	/* All /log10(2.0) added by M. Boland */

	/*
	* px[i] is the (i-1)th entry in the marginal probability matrix obtained
	* by summing the rows of p[i][j]
	*/
	for (i = 0; i < Ng; ++i) {
			for (j = 0; j < Ng; ++j) {
				px[i] += P[i][j];
				py[j] += P[i][j];
			}
	}

	for (i = 0; i < Ng; ++i)
			for (j = 0; j < Ng; ++j) {
					hxy1 -= P[i][j] * log10 (px[i] * py[j] + EPSILON)/log10(2.0);
					hxy2 -= px[i] * py[j] * log10 (px[i] * py[j] + EPSILON)/log10(2.0);
					hxy -= P[i][j] * log10 (P[i][j] + EPSILON)/log10(2.0);
			}

	/* Calculate entropies of px and py */
	for (i = 0; i < Ng; ++i) {
			hx -= px[i] * log10 (px[i] + EPSILON)/log10(2.0);
			hy -= py[i] * log10 (py[i] + EPSILON)/log10(2.0);
	}

	free(px);
	free(py);
	return (sqrt (fabs (1 - exp (-2.0 * (hxy2 - hxy)))));
}

/* Information Measures of Correlation */
/* All /log10(2.0) added by M. Boland */
float f13_icorr ( float **P, int Ng)
{
  int i, j;
  double *px, *py;
  float hx = 0, hy = 0, hxy = 0, hxy1 = 0, hxy2 = 0;

	px = allocate_vector (0, Ng);
	py = allocate_vector (0, Ng);

  /*
   * px[i] is the (i-1)th entry in the marginal probability matrix obtained
   * by summing the rows of p[i][j]
   */
  for (i = 0; i < Ng; ++i)
  {
    for (j = 0; j < Ng; ++j)
    {
      px[i] += P[i][j];
      py[j] += P[i][j];
    }
  }

  for (i = 0; i < Ng; ++i)
    for (j = 0; j < Ng; ++j)
    {
      hxy1 -= P[i][j] * log10 (px[i] * py[j] + EPSILON)/log10(2.0);
      hxy2 -= px[i] * py[j] * log10 (px[i] * py[j] + EPSILON)/log10(2.0);
      hxy -= P[i][j] * log10 (P[i][j] + EPSILON)/log10(2.0);
    }

  /* Calculate entropies of px and py */
  for (i = 0; i < Ng; ++i)
  {
    hx -= px[i] * log10 (px[i] + EPSILON)/log10(2.0);
    hy -= py[i] * log10 (py[i] + EPSILON)/log10(2.0);
  }
/*  fprintf(stderr,"hx=%f\thxy2=%f\n",hx,hxy2); */
  free(px);
  free(py);
  return (sqrt (abs (1 - exp (-2.0 * (hxy2 - hxy)))));
}
//Coeciente de Correla?ão Máximo

double f14_ccm(float **P, int Ng){

    int i, j;
    double *px, *py;
    float sum=0;
    double **Q;
    Mat Q2;
      px = allocate_vector (0, Ng);
      py = allocate_vector (0, Ng);
      //EigenValues = allocate_vector(0,Ng);

    for (i = 0; i < Ng; ++i){
      for (j = 0; j < Ng; ++j){
        px[i] += P[i][j];
        py[j] += P[i][j];
      }
    }
    for(i=0; i<Ng;++i){
        for(j=0; j<Ng;j++){
          if (P[i][j] != 0 && px[i] != 0) { // would result in 0
                for(int k =0; k<Ng; ++k){
                   if (py[k] != 0 && P[j][k] != 0) { // would result in NaN
                       sum += (P[i][k] * P[j][k])/(px[i] * py[k]);
                        cout<<sum<<endl;

                   }
                }
          }
        }
    }
   // Mat M;


   // M.convertTo(Q,CV_64FC1);
    //Mat v,e;
   // eigen(Q,e,v);
    //while(e.at<uchar>(i,j)=! NULL)
    //        cout<<e.at<uchar>(i,j);

//    for(int z =0;z<255; z++)
//        e.at<uchar>(i,j) = e.at<uchar>(i,j)*(-1);
}


double correl (double **P, int Ng) {
        int i, j;
        double sum_sqrx = 0, sum_sqry = 0, tmp, *px;
        double meanx =0 , meany = 0 , stddevx, stddevy;

        px = allocate_vector (0, Ng);
        for (i = 0; i < Ng; ++i)
                px[i] = 0;

        //
        //* px[i] is the (i-1)th entry in the marginal probability matrix obtained
        //* by summing the rows of p[i][j]
        //
        for (i = 0; i < Ng; ++i)
                for (j = 0; j < Ng; ++j)
                        px[i] += P[i][j];


        //* Now calculate the means and standard deviations of px and py 
        //*- fix supplied by J. Michael Christensen, 21 Jun 1991 
        //*- further modified by James Darrell McCauley, 16 Aug 1991
        //*     after realizing that meanx=meany and stddevx=stddevy
        //
        for (i = 0; i < Ng; ++i) {
                meanx += px[i]*i;
                sum_sqrx += px[i]*i*i;
        }

        //* M. Boland meanx = meanx/(sqrt(Ng)); 
        meany = meanx;
        sum_sqry = sum_sqrx;
        stddevx = sqrt (sum_sqrx - (meanx * meanx));
        stddevy = stddevx;

        //* Finally, the correlation ... 
        for (tmp = 0, i = 0; i < Ng; ++i)
                for (j = 0; j < Ng; ++j)
                          tmp += i*j*P[i][j];

        free(px);
        if (stddevx * stddevy==0) return(1);  //* protect from error 
        else return (tmp - meanx * meany) / (stddevx * stddevy);
}
double homogen (double **P, int Ng) {
        int i, j;
        double idm = 0;

        for (i = 0; i < Ng; ++i)
                for (j = 0; j < Ng; ++j)
                        idm += P[i][j] / (1 + (i - j) * (i - j));

        return idm;
}
double savg (double **P, int Ng) {
        int i, j;
        double savg = 0;
        double *Pxpy = allocate_vector (0, 2*Ng);

        for (i = 0; i <= 2 * Ng; ++i)
                Pxpy[i] = 0;

        for (i = 0; i < Ng; ++i)
                for (j = 0; j < Ng; ++j)
                  //* M. Boland Pxpy[i + j + 2] += P[i][j]; 
                  //* Indexing from 2 instead of 0 is inconsistent with rest of code
                  Pxpy[i + j] += P[i][j];

        // M. Boland for (i = 2; i <= 2 * Ng; ++i) 
        // Indexing from 2 instead of 0 is inconsistent with rest of code
        for (i = 0; i <= (2 * Ng - 2); ++i)
                savg += i * Pxpy[i];

        free (Pxpy);
        return savg;
}

void bubble_sort (int vetor[], int n) {
    int k, j, aux;

    for (k = 1; k < n; k++) {
        printf("\n[%d] ", k);

        for (j = 0; j < n - 1; j++) {
            printf("%d, ", j);

            if (vetor[j] > vetor[j + 1]) {
                aux          = vetor[j];
                vetor[j]     = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

