#ifndef METODOS_TP2_LECTURA_H
#define METODOS_TP2_LECTURA_H

#include "Dato.h"

void cargar_training(std::vector<Dato>&, const string&);
void cargar_test(std::vector<Dato>&, const string&);

template <typename Iterator>
void leer_matriz(Mat<double>& resultado, Iterator& it);

#endif //METODOS_TP2_LECTURA_H
