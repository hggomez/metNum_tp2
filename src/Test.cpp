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
    //Lectura de datos
    ifstream k_fold_file;
    string aux = "../tests/"+nombre_archivo+ ".in";
    k_fold_file.open(aux);

    string data;
    int k_fold, k_nn, alpha;

    k_fold_file >> data;
    k_fold_file>> k_nn >> alpha >> k_fold;
    data += "train.csv";
    vector<Dato> datos;
    cerr<<data<<" "<<k_nn<<" "<<alpha<<" "<<k_fold<<endl;
    cargar_training(datos, data);
    if(alpha != 28*28){

    }
    //guardo cuantas etiquetas hay de cada una en el set de test
    ofstream etiquetas_kfold;
    etiquetas_kfold.open(nombre_metodo+"_"+nombre_archivo+"_etiquetas.csv", ios_base::out);
    //guardo las matrices de confusion
    ofstream output;
    output.open(nombre_metodo+"_"+nombre_archivo+".csv", ios_base::out);
    output<<"tamaño_test,";
    for(int i = 0;i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            output<<"("<<to_string(i)<<"."<<to_string(j)<<")";
            if(i != 9 || j != 9 ) output<<",";

        }
    }
    output <<"\n";

    //me va a decir cuantas etiquetas de cada categoria hay en el set de test.
    vector<int> etiquetas_Reales(10, 0);

    //corro kfold
    for(int i = 0; i<k_fold; ++i){
        //cada fila habla del valor real de la etiqueta y cada columna acumula cuantos etiquetas seleccionamos mal/bien
        //matriz de confusion
        Mat<int> matriz_etiquetas(10, 10, 0);
        //subdivido el conjunto en training y test
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

        //corro la resolucion para todo lo que separamos como test.
        for(int j = 0; j< test.size(); ++j){
            Etiqueta real = test[j].etiqueta;
            metodo_resolucion(test[j],training, k_nn);
            matriz_etiquetas(real, test[j].etiqueta)++;
            cerr<<"cantidad_imagenes " <<test.size()<<" kfold "<<i<<" ya salio de la imagen "<<j<<"\n";
        }

        for(int j = 0; j<10; ++j){
            for(int k = 0; k<10; ++k){
                output<< matriz_etiquetas(j,k);
                if(j != 9 || k != 9 ) output<<",";
            }
        }
        output<<"\n";
    }

}
