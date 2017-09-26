//
// Created by javier on 23/09/17.
//

#include<vector>
#include<iostream>
#include<fstream>

#include "Lectura.h"

using namespace std;

void generar_training(vector<Dato>& resultado) {

    cerr << "Generando training..." << endl;

    ifstream data;
    data.open("../data/train.csv");

    string header;
    getline(data, header);
    int linea = 2;

    while(data.good()) {

        string pre_parseo;
        getline(data, pre_parseo);
        auto it = pre_parseo.begin();

        if (*it != '\000' && *it != EOF && *it != '\r') {

            Dato nueva_imagen(Mat<uint>(28, 28), (Etiqueta) (*it - 48));
            advance(it, 2);
            leer_matriz(nueva_imagen.imagen,it);
            resultado.push_back(nueva_imagen);

            linea++;
        }
    }
    data.close();
}

void generar_test(vector<Dato>& resultado) {
    cerr << "Generando casos de test..." << endl;

    ifstream data;
    data.open("../data/test.csv");

    string header;
    getline(data, header);
    int linea = 2;

    while(data.good()) {

        string pre_parseo;
        getline(data, pre_parseo);
        auto it = pre_parseo.begin();

        if (*it != '\000' && *it != EOF && *it != '\r') {

            Dato nueva_imagen(Mat<uint>(28, 28), 10);
            leer_matriz(nueva_imagen.imagen,it);
            resultado.push_back(nueva_imagen);

            linea++;
        }
    }
    data.close();
}

template <typename Iterator>
void leer_matriz(Mat<uint>& resultado, Iterator& it) {

    //leo cada posicion de la matriz
    for (uint i = 0; i < 28; ++i) {
        for (uint j = 0; j < 28; ++j) {
            //como no se cuantos digitos tengo y estoy iterando
            //sobre caracter creo un string donde almacenar el numero
            string numero;
            //si no es ',' entonces es un numero y es el que quiero concatenar

            while (*it != ',' && *it != '\r') {
                //sin esto, tendria que funcionar, pero si se lo sacas me pasaba que le pasaba
                //a stoi un argumento invalido (creo que habia tabs o espacios o algo que no le gusto
                if ('0' <= *it && *it <= '9') numero += *it;
                ++it;
            }

            //despues de debuggear un rato entiendo cada vez menos, a veces numero es un string MUY largo
            //lo cual puede ser la razon del out_of_range... pero no se donde esta el error

            if (!numero.empty())
                resultado(i, j) = (uint) stoi(numero);

            //estoy en la ',' asi que avanzo el iterador al proximo numero.
            ++it;
        }
    }
}