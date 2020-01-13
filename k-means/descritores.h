#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

#define EPSILON 0.000000001

double *allocate_vector (int nl, int nh);
double **allocate_matrix (int nrl, int nrh, int ncl, int nch);
float **allocate_matrix_float (int nrl, int nrh, int ncl, int nch);
double **Liberar_matriz_double (int m, int n, double **v);
float **Liberar_matriz_float (int m, int n, float **v);
int **Liberar_matriz_int (int m, int n, int **v);

float** CoOc_simetrH_Mat (int **grays, int rows, int cols, int nivel_min, int nivel_max);

float f1_asm (float **P, int Ng);
float f2_contrast (float **P, int Ng);
float f3_corr (float **P, int Ng);
float f4_var (float  **P, int Ng);
float f5_idm (float  **P, int Ng);
float f6_savg (float  **P, int Ng);
float f7_svar (float  **P, int Ng);
float f8_sentropy (float  **P, int Ng);
float f9_entropy (float  **P, int Ng);
float f10_dvar (float  **P, int Ng);
float f11_dentropy (float  **P, int Ng);
float f12_icorr (float  **P, int Ng);
float f13_icorr (float  **P, int Ng);

double correl (float **P, int Ng);
double homogen (float **P, int Ng);
double savg (float **P, int Ng);
