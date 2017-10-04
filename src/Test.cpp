//
// Created by javier on 28/09/17.
//
#include "Test.h"

using namespace std;

void separador(const vector<Dato>& datos,vector<Dato>& training, vector<Dato>& test, ifstream& k_fold_file,vector<int>& etiquetas_Reales){
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
}


void correr_Cross_Val(void (* metodo_resolucion)(Dato&, const vector<Dato>&, uint),const string& nombre_archivo, const string& nombre_metodo){
    //Lectura de datos
    ifstream k_fold_file;
    k_fold_file.open("../tests/"+nombre_archivo+ ".in");

    string data;
    int k_fold, k_nn, alpha;

    k_fold_file >> data;
    k_fold_file>> k_nn >> alpha >> k_fold;

    data += "train.csv";
    vector<Dato> datos;
    cerr<< data<<" "<<k_fold<<" "<<alpha<<" "<<k_nn<<"\n";
    cargar_training(datos, data);
    //cambio la dimension de los datos.
    if(alpha < 28*28){
        PCA(datos, alpha);
    }

    //guardo cuantas etiquetas hay de cada una en el set de test por cada kfold
    ofstream etiquetas_kfold;
    //header
    etiquetas_kfold.open(nombre_metodo+"_"+nombre_archivo+"_etiquetas.csv", ios_base::app);
    for(int i = 0;i < 10; ++i) {
        etiquetas_kfold<<"etiqueta_"<<to_string(i);
        if(i != 9) etiquetas_kfold<<",";
    }
    etiquetas_kfold <<"\n";


    //guardo las matrices de confusion
    ofstream output;
    //header
    output.open(nombre_metodo+"_"+nombre_archivo+".csv", ios_base::app);
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
        Mat<int> matriz_confusion(10, 10, 0);
        //subdivido el conjunto en training y test
        vector<Dato> training, test;


        //separo los datos en test y training, creo que tendria que saber las cantidades, no estoy seguro
        separador(datos, training, test, k_fold_file, etiquetas_Reales);


        //corro la resolucion para todo lo que separamos como test.
        for(int j = 0; j< test.size(); ++j){
            Etiqueta real = test[j].etiqueta;
            metodo_resolucion(test[j],training, k_nn);
            matriz_confusion(real, test[j].etiqueta)++;
            cerr<<"cantidad_imagenes " <<test.size()<<" kfold "<<i<<" ya salio de la imagen "<<j<<"\n";
        }

        for(int j = 0; j<10; ++j){
            for(int k = 0; k<10; ++k){
                output<< matriz_confusion(j,k);
                if(j != 9 || k != 9 ) output<<",";
            }
        }
        output<<"\n";

        for(int j = 0;j < etiquetas_Reales.size(); ++j) {
            etiquetas_kfold << etiquetas_Reales[j];
            if(j != 9) etiquetas_kfold<<",";
        }
        etiquetas_kfold <<"\n";

    }

}
