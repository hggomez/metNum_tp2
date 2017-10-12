//
// Created by javier on 28/09/17.
//

#ifndef METODOS_TP2_TEST_H
#define METODOS_TP2_TEST_H

#include "Metodos_de_Resolucion.h"
#include "Measure.h"
#include <fstream>
#include "Lectura.h"
#include <bitset>
#include <deque>
#include <algorithm>

void generar_Test(int desde_k_nn, int hasta_k_nn, int skip_k_nn, int desde_alpha, int hasta_alpha, int skip_alpha, int k_kfold);

void separador(const vector<Dato>& datos,vector<Dato>& training, vector<Dato>& test, ifstream& k_fold_file);

void correr_Cross_Val(void (* metodo_resolucion)(Dato&, const vector<Dato>&, uint), const string& nombre_archivo, const string& nombre_metodo, bool correr_PCA);





#endif //METODOS_TP2_TEST_H
