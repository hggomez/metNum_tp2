#include <iostream>
#include <map>
#include <fstream>

#include "Measure.h"
#include "Lectura.h"
#include "Metodos_de_Resolucion.h"

template <typename F, typename... Args>
void run_method(ofstream& output, const int repeticiones, F func, vector<Dato>& test_set, const vector<Dato>& training_set, Args&&... args) {
    output << "ImageId,Label,Tiempo,Metodo" << endl;

    for (int id = 1; id <= test_set.size(); ++id) {
        cerr << "id: " << id;
        cerr << " label: " << test_set[id].etiqueta << endl;

        if (test_set[id].etiqueta == 8){
            auto tiempo = measure<chrono::microseconds>::execution(repeticiones, func, test_set[id-1], training_set, args... );

            cerr <<  "Resultado: ";
            output << id << ',' << test_set[id-1].etiqueta << ',' << tiempo << ",KNN" << endl;
            cerr << endl;
        }

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

    int method = stoi(getCmdOption(argv, argc, "-m"));
    string train_set_filepath = getCmdOption(argv, argc, "-i");
    string test_set_filepath = getCmdOption(argv, argc, "-q");
    string output_filepath = getCmdOption(argv, argc, "-o");


    vector<Dato> training_set;
    generar_training(training_set, train_set_filepath);

    vector<Dato> test_set;
    generar_test(test_set, test_set_filepath);

    ofstream output_file;
    output_file.open(output_filepath, fstream::out);


    int k = 15;
    int repeticiones = 1;
    double distancia_max = distancia_maxima(training_set);

    switch(method) {
        case 0:
            run_method(output_file, repeticiones, KNN_distancia, training_set, training_set, k, distancia_max);
            break;
        case 1:
//            func = &pca+knn;
            break;
        default:
            run_method(output_file, repeticiones, KNN, test_set, training_set, k);
            break;
    }

    output_file.close();

    return 0;
}
