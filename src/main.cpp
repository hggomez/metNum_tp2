#include <iostream>
#include <map>

#include "Measure.h"
#include "Lectura.h"
#include "Metodos_de_Resolucion.h"

int main(int argc, char const *argv[]) {

    vector<Dato> training;
    training.reserve(42000);
    generar_training(training);

    vector<Dato> casos_test;
    casos_test.reserve(28000);
    generar_test(casos_test);

    int k = 99;

    cout << "ImageId,Label,Tiempo,Metodo,K" << endl;

    for (int id = 1; id <= casos_test.size(); ++id) {
        cerr << "id: " << id << endl;
        auto tiempo = measure<chrono::microseconds,2>::execution(KNN, casos_test[id-1], training, k);
        cerr << "Resultado: ";
        cout << id << ',' << casos_test[id-1].etiqueta << ',' << tiempo << "KNN," << k << endl;
        cerr << endl;
    }


    return 0;
}