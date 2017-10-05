#include <iostream>
#include <map>
#include <fstream>

#include "Measure.h"
#include "Lectura.h"
#include "Metodos_de_Resolucion.h"
#include "Test.h"

template <typename F, typename... Args>
void run_method(ofstream& output, const int repeticiones, F func, vector<Dato>& test_set, const vector<Dato>& training_set, Args&&... args) {
    output << "ImageId,Label,Tiempo,Metodo" << endl;

    for (int id = 1; id <= test_set.size(); ++id) {
        cerr << "id: " << id << endl;

        auto tiempo = measure<chrono::microseconds>::execution(repeticiones, func, test_set[id-1], training_set, args... );

        cerr <<  "Resultado: ";
        output << id << ',' << test_set[id-1].etiqueta << ',' << tiempo << ",KNN" << endl;
        cerr << endl;
    }
}

string getCmdOption(const char* argv[], int argc, const std::string & option)  {
    for (int i = 0; i < argc; ++i) {

        auto a = option.compare(argv[i]);

        if (a == 0) return string(argv[i+1]);
    }
    return nullptr;
}

int main(int argc, char const *argv[]) {

    void (* metodo_resolucion)(Dato&, const vector<Dato>&, uint);
    metodo_resolucion = KNN;
    correr_Cross_Val(metodo_resolucion, "test1", "KNN", true);

    /*

    int method = stoi(getCmdOption(argv, argc, "-m"));
    string train_set_filepath = getCmdOption(argv, argc, "-i");
    string test_set_filepath = getCmdOption(argv, argc, "-q");
    string output_filepath = getCmdOption(argv, argc, "-o");


    vector<Dato> training_set;
    cargar_training(training_set, train_set_filepath);

    vector<Dato> test_set;
    cargar_test(test_set, test_set_filepath);

    ofstream output_file;
    output_file.open(output_filepath, fstream::out);


    int k = 99;
    int repeticiones = 1;

//    distancias_maximas(training_set);

    switch(method) {
        case 0:
            run_method(output_file, repeticiones, KNN_distancia, training_set, training_set, k);
            break;
        case 1:
//            func = &pca+knn;
            break;
        default:
            run_method(output_file, repeticiones, KNN, test_set, training_set, k);
            break;
    }

    output_file.close();

     */

    return 0;
}
