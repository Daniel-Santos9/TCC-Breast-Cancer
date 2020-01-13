#include <stdio.h>

FILE* abrirArquivo(char* arquivo);
FILE* abrirArquivo2(const char* arquivo);
bool gravarDados(int n, double *dados, FILE* arq);
bool gravarDados_float(int n, float *dados, FILE* arq);
bool gravarDados_int(int n, int *dados, FILE* arq);
void fecharArquivo(FILE* arq);