#ifndef NORMALIZACAO_H
#define NORMALIZACAO_H


double normaliza(double **val_descritores, double x, int row, int col, int d1, int d2);
double retorna_xmax(double **val_descritores, int row, int col);
double retorna_xmin(double **val_descritores, int row, int col);
class normalizacao
{
public:
    normalizacao();
    ~normalizacao();
};

#endif // NORMALIZACAO_H
