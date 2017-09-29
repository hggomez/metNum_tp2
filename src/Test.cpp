//
// Created by javier on 28/09/17.
//
#include "Test.h"
#include <fstream>
#include "Lectura.h"

using namespace std;
//por ahora vamos a usar recall y f_score de M y no mu son dos formas distintas que no se muy bien como se diferencian
//hacemos esto como primer idea ya que acuraccy tiene una cuenta muy parecida a las M

void correr_Cross_Val(void (* metodo_resolucion)(Dato&, const vector<Dato>&, uint),const string& nombre_archivo, const string& nombre_metodo){
    vector<int> etiquetas_Reales(10, 0);
    ifstream k_fold_file;
    string aux = "../tests/"+nombre_archivo+ ".in";
    k_fold_file.open(aux);

    string data;
    int k_fold, k_nn, alpha;
    k_fold_file >> data;
    k_fold_file>> k_nn >> alpha >> k_fold;
    data += "train.csv";
    vector<Mat<int> > lista_clasificadores(k_fold, Mat<int>(10,10,0));
    vector<int> size_test(k_fold, 0);
    vector<double> accuracy(k_fold, 0);
    vector<double> recall(k_fold, 0);
    vector<double> kappa(k_fold, 0);
    vector<double> f_score(k_fold, 0);
    vector<Dato> datos;
    cerr<<data<<" "<<k_nn<<" "<<alpha<<" "<<k_fold<<endl;
    cargar_training(datos, data);
    if(alpha != 28*28){

    }
    for(int i = 0; i<k_fold; ++i){
        //cada fila habla del valor real de la etiqueta y cada columna acumula cuantos etiquetas seleccionamos mal/bien
        Mat<int> matriz_etiquetas(10, 10, 0);
        vector<Dato> training, test;
        //separo los datos en test y training, creo que tendria que saber las cantidades, no estoy seguro
        for(int j = 0; j<datos.size(); ++j){
            bool train;
            k_fold_file >> train;
            if(train){
                training.push_back(datos[j]);
            }
            else{
                test.push_back(datos[j]);
                etiquetas_Reales[datos[j].etiqueta]++;
            }
        }
        size_test[i] = test.size();
        //corro la resolucion para todo lo que separamos como test.
        for(int j = 0; j< test.size(); ++j){
            Etiqueta real = test[j].etiqueta;
            metodo_resolucion(test[j],training, k_nn);
            matriz_etiquetas(real, test[j].etiqueta)++;
            cerr<<"cantidad_imagenes " <<test.size()<<" kfold "<<i<<" ya salio de la imagen "<<j<<"\n";
        }
        lista_clasificadores[i] = matriz_etiquetas;
    }

    int filas = lista_clasificadores[0].filas();
    int col = lista_clasificadores[0].columnas();
    ofstream output;
    output.open(nombre_metodo+" "+nombre_archivo+".csv", ios_base::out);
    output<<"tamaño_test,";
    for(int i = 0;i < filas; ++i) {
        for (int j = 0; j < col; ++j) {
            output<<"("<<to_string(i)<<"."<<to_string(j)<<")";
            if(i != filas - 1 || j != col-1 ) output<<",";

        }
    }
    output <<"\n";
    for(int i = 0; i< k_fold; ++i){
        cerr<<lista_clasificadores[i];
        output<<size_test[i]<<",";
        Mat<int> aux = lista_clasificadores[i];
        for(int j = 0; j<filas; ++j){
            for(int k = 0; k<col; ++k){
                output<<aux(j,k);
                if(j != filas-1 || k != col-1 ) output<<",";
            }
        }
        output<<"\n";
    }
}
