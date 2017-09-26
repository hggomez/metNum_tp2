#ifndef METODOS_TP2_LECTURA_H
#define METODOS_TP2_LECTURA_H

#include "Dato.h"

void generar_training(std::vector<Dato>&);
void generar_test(std::vector<Dato>& resultado);

template <typename Iterator>
void leer_matriz(Mat<uint>& resultado, Iterator& it);

#endif //METODOS_TP2_LECTURA_H
