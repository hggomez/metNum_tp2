//
// Created by javier on 28/09/17.
//
#include <bitset>
#include <deque>
#include <algorithm>
#include "Test.h"

using namespace std;

void separador(const vector<Dato>& datos,vector<Dato>& training, vector<Dato>& test, ifstream& k_fold_file) {
    for(int j = 0; j<datos.size(); ++j){
        bool train;
        k_fold_file >> train;
        if (train) {
            training.push_back(datos[j]);
        } else {
            test.push_back(datos[j]);
        }
    }
}


void generar_Test(int desde_k_nn, int hasta_k_nn, int skip_k_nn, int desde_alpha, int hasta_alpha, int skip_alpha, int k_kfold) {
    //CHEQUEAR QUE K_KFOLD SEA MENOR QUE EL TAMAÑO DE CADA BUCKET
    // for (int i = 0; i < 10; ++i) {
    //        throw std::out_of_range("mat_ con 0 filas o 0 columnas");
    //    }

    const string data_file_name = "../sets/train.csv";
    vector<Dato> data;
    cargar_training(data, data_file_name);

    vector<deque<int> > buckets(10);
    bitset<42000> testing_map;
    vector<int> subset_sizes(10);

    string file_name;
    ofstream file;


    int k_nn = desde_k_nn;
    while(k_nn <= hasta_k_nn) {
        int alpha = desde_alpha;
        while (alpha <= hasta_alpha) {
            file_name = "k_" + to_string(k_nn) + "-alpha_" + to_string(alpha) + "-kfold_" + to_string(k_kfold) + ".in";
            file.open("../tests/" + file_name, ios_base::trunc);
            file << "../sets/ " << k_nn << " " << alpha << " " << k_kfold << endl;
            file.close();
            alpha += skip_alpha;
        }
        k_nn += skip_k_nn;
    }

    for (int i = 0; i < data.size(); ++i) {
        buckets[data[i].etiqueta].push_back(i);
    }

    for (int i = 0; i < buckets.size(); ++i) {
        subset_sizes[i] = (int) round(buckets[i].size() / k_kfold);
        random_shuffle(buckets[i].begin(), buckets[i].end());
    }

    for (int i = 0; i < k_kfold; ++i) {
        for (int j = 0; j < buckets.size(); ++j) {
            if (i < k_kfold) {
                for (int k = 0; k < subset_sizes[j]; ++k) {
                    testing_map[buckets[j].back()] = 1;
                    buckets[j].pop_back();
                }
            } else {
                while (!buckets[j].empty()) {
                    testing_map[buckets[j].back()] = 1;
                    buckets[j].pop_back();
                }
            }
        }

        k_nn = desde_k_nn;
        while(k_nn <= hasta_k_nn) {
            int alpha = desde_alpha;
            while (alpha <= hasta_alpha) {
                file_name =
                        "k_" + to_string(k_nn) + "-alpha_" + to_string(alpha) + "-kfold_" + to_string(k_kfold) + ".in";
                file.open("../tests/" + file_name, ios_base::app);

                for (int k = 0; k < data.size(); ++k) {
                    file << testing_map[k] << " ";
                }

                file << endl;
                file.close();
                alpha += skip_alpha;
            }
            k_nn += skip_k_nn;
        }
        testing_map.reset();
    }
}

//por ahora vamos a usar recall y f_score de M y no mu son dos formas distintas que no se muy bien como se diferencian
//hacemos esto como primer idea ya que acuraccy tiene una cuenta muy parecida a las M

void correr_Cross_Val(void (* metodo_resolucion)(Dato&, const vector<Dato>&, uint),const string& nombre_archivo, const string& nombre_metodo, bool correr_PCA) {
    //Lectura de datos
    ifstream k_fold_file;
    k_fold_file.open("../tests/" + nombre_archivo + ".in");
    string data;
    int k_fold, k_nn, alpha;
    getline(k_fold_file, data, ' ');
    k_fold_file >> k_nn >> alpha >> k_fold;
    data += "train.csv";
    vector<Dato> datos;
    cerr << data << " " << k_fold << " " << alpha << " " << k_nn << "\n";
    cargar_training(datos, data);

    //cambio la dimension de los datos.
    if(alpha < 28*28 && correr_PCA){
        PCA(datos, alpha);
    }

    distancias_maximas(datos);

    //guardo las matrices de confusion
    ofstream output;
    //header
    string archivo = nombre_metodo;
    if(correr_PCA) archivo +="PCA";
    archivo += "_"+nombre_archivo+".csv";
    output.open(archivo, ios_base::app);
    for(int i = 0;i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            output << "(" << to_string(i) << "." << to_string(j) << ")";
            if (i != 9 || j != 9) output << ",";

        }
    }
    output << "\n";


    //corro kfold
    for (int i = 0; i < k_fold; ++i) {
        //cada fila habla del valor real de la etiqueta y cada columna acumula cuantos etiquetas seleccionamos mal/bien
        //matriz de confusion
        Mat<int> matriz_confusion(10, 10, 0);
        //subdivido el conjunto en training y test
        vector<Dato> training, test;


        //separo los datos en test y training, creo que tendria que saber las cantidades, no estoy seguro
        separador(datos, training, test, k_fold_file);


        //corro la resolucion para todo lo que separamos como test.
        for (int j = 0; j < test.size(); ++j) {
            Etiqueta real = test[j].etiqueta;
            metodo_resolucion(test[j], training, k_nn);
            matriz_confusion(real, test[j].etiqueta)++;
            cerr << "cantidad_imagenes " << test.size() << " kfold " << i << " ya salio de la imagen " << j << "\n";
        }

        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 10; ++k) {
                output << matriz_confusion(j, k);
                if (j != 9 || k != 9) output << ",";
            }
        }
        output << "\n";
    }

    k_fold_file.close();
    output.close();
}
