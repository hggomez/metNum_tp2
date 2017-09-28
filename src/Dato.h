//
// Created by nluce on 25/09/17.
//

#ifndef METODOS_TP2_DATO_H
#define METODOS_TP2_DATO_H

#include "Mat.h"

typedef unsigned int Etiqueta;

//estructura para juntar imagen con su etiqueta
struct Dato {

    Mat<double> imagen;
    Etiqueta etiqueta;

    Dato(Mat<double> foto, Etiqueta valor): imagen(foto), etiqueta(valor){}

};


#endif //METODOS_TP2_DATO_H
