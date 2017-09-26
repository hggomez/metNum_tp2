//
// Created by javier on 23/09/17.
//

#include<vector>
#include<iostream>
#include<fstream>
#include "Mat.h"

typedef unsigned int uint;

using namespace std;

//estructura para juntar imagen con su etiqueta
struct Dato {

    Mat<uint> imagen;
    uint etiqueta;

    Dato(Mat<uint> foto, uint valor): imagen(foto), etiqueta(valor){}

};

//defino las funciones

vector<Dato> datos(){
    vector<Dato> conjunto;
    ifstream data;
    data.open("../data/train.csv");
    string header;
    getline(data, header);
    while(data.good()){
        string pre_parseo;
        getline(data, pre_parseo);
        auto it = pre_parseo.begin();
        //no funciona esto todavia, buscar la funcion...
        uint valor =  (uint) *it;
        advance(it, 2);
        Mat<uint> foto(27,27);
        //leo cada posicion de la matriz
        for(uint i = 0; i<27; ++i){
            for(uint j = 0; j< 27; ++j){
                //como no se cuantos digitos tengo y estoy iterando
                //sobre caracter creo un string donde almacenar el numero
                string numero;
                
                //si no es ',' entonces es un numero y es el que quiero concatenar
                while(*it != ',' && *it != '\n'){
                    //sin esto, tendria que funcionar, pero si se lo sacas me pasaba que le pasaba
                    //a stoi un argumento invalido (creo que habia tabs o espacios o algo que no le gusto
                   char digito = *it;
                    if('0' <= *it && *it <= '9') numero += digito;

                    ++it;
                }
                //despues de debuggear un rato entiendo cada vez menos, a veces numero es un string MUY largo
                //lo cual puede ser la razon del out_of_range... pero no se donde esta el error
                foto(i, j) = (uint) stoi(numero);
                //estoy en la ',' asi que avanzo el iterador al proximo numero.
                ++it;

            }
        }
        Dato aux(foto, valor);
        conjunto.push_back(aux);
    }
    data.close();
    return conjunto;
}

int main(){
    vector<Dato> todos = datos();
    cout<<todos.size();
    uint coma = (uint) ',';
    //cout<<" , "<< coma<<"\n";
    cout<<todos[todos.size()-1].imagen;
}