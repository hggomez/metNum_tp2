#ifndef METODOS_TP2_METODOS_DE_RESOLUCION_H
#define METODOS_TP2_METODOS_DE_RESOLUCION_H

#include "Mat.h"
#include "Dato.h"

void KNN(Dato& A, const vector<Dato>& training, uint k);

void PCA(const vector<Dato>& training, int alpha);



#endif //METODOS_TP2_METODOS_DE_RESOLUCION_H
