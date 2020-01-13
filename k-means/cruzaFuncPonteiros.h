#include <string>
#include "descritores.h"
#include "gravaDados.h"

using namespace std;

typedef float (*vetDescritor)(float **P, int Ng);

void cruzaQuatro(string nomeImagem, string pasta1Imagem, string pasta2Imagem, int numAmostras, int controle);

void cruzaTres(string nomeImagem, string pasta1Imagem, string pasta2Imagem, int numAmostras, int controle);

void cruzaDois(string nomeImagem, string pasta1Imagem, string pasta2Imagem, int numAmostras, int controle);

void cruzaUm(string nomeImagem, string pasta1Imagem, string pasta2Imagem, int numAmostras, int controle);
