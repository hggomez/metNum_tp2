#ifndef METODOS_TP2_METODOS_DE_RESOLUCION_H
#define METODOS_TP2_METODOS_DE_RESOLUCION_H

#include "Mat.h"
#include "Dato.h"

void KNN(Dato& A, const vector<Dato>& training, uint k);

void KNN_distancia(Dato& A, const vector<Dato>& training, uint k, double distancia_max);
double distancia_maxima(const vector<Dato>& training_set);

void PCA(const vector<Dato>& training, int alpha);



#endif //METODOS_TP2_METODOS_DE_RESOLUCION_H
