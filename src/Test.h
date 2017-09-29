//
// Created by javier on 28/09/17.
//

#ifndef METODOS_TP2_TEST_H
#define METODOS_TP2_TEST_H

#include "Metodos_de_Resolucion.h"
#include "Measure.h"

void generar_Test(int k_nn, int desde_alpha, int hasta_alpha, int skip_alpha, int k_kfold);


void correr_Cross_Val(void (* metodo_resolucion)(Dato&, const vector<Dato>&, uint), const string& nombre_archivo, const string& nombre_metodo);




#endif //METODOS_TP2_TEST_H
