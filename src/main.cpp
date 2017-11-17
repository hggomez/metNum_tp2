#include <iostream>
#include <map>
#include <fstream>
#include <thread>

#include "Measure.h"
#include "Lectura.h"
//#include "Metodos_de_Resolucion.h"
#include "Test.h"
//#include "PCA.cpp"

template <typename F, typename... Args>
void run_method(ofstream& output, const int repeticiones, F func, vector<Dato>& test_set, const vector<Dato>& training_set, Args&&... args) {
    output << "ImageId,Label" << endl;

    for (int id = 1; id <= test_set.size(); ++id) {
        cerr << "id: " << id << endl;

        auto tiempo = measure<chrono::microseconds>::execution(repeticiones, func, test_set[id-1], training_set, args... );

        cerr <<  "Resultado: ";
        output << id << ',' << test_set[id-1].etiqueta << endl;
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

template <typename T>
Mat<T> construiryCentrarX1(vector< Mat<T> > &S){ //Tengo la secuencia de datos x(1) ,x(2), ... en T

    int dimdelDato = S[0].columnas(); // S[0] obtenemos una fila que representa una imagen con Mat. Como todas las imagenes
    // tienen el mismo tamanio le pido a una.

    Mat<T> X = Mat<T>( S.size(), dimdelDato);


    int contador = 0;    //podria tener un iterador del vector pero paja, dsps viene Nico el limpiador de codigo
    for (int fila = 0; fila < X.filas(); fila++) { // Recordar que X( Tam de T , Dimension del dato S[i] = columnas S[i]
        Mat<T> vect = S[contador]; // Obtengo la primer imagen
        for (int columna = 0; columna < X.columnas(); columna++) {
            X(fila, columna) = vect(0, columna); // Cada fila de X tendra almacenada una imagen
        }
        contador++; // Incremento el contador para tomar la proxima imagen , notar que  0 <= contador <= X.filas = S.size()
    }

    //Hasta aca tengo la X , ahora hay que centrarla


    double raiz = sqrt(X.filas() - 1 ); // Obtenemos sqrt(n-1) , n es la dimension de la base original S.size = X.filas
    raiz = pow(raiz,-1); // Queremos multiplicar por 1/raiz

    vector<double> medias; // Vamos a crear un vector de medias, media[i] corresponde a la media de la columna i de X.
    // notar que 0 <= medias.size() <= X.columnas()



    for(int columna = 0; columna < X.columnas(); columna++ ){ //Calculo cada media por columna
        double acum = 0;
        for(int i = 0 ; i < X.filas(); i++){
            acum = acum + X(i,columna);
        }
        double media = acum/X.filas();
        medias.push_back(media);
    }

    for(int columna = 0; columna < X.columnas(); columna++){
        for(int fila = 0; fila < X.filas();fila++){
            X(fila,columna) = X(fila,columna) - medias[columna];
        }
    }

    // Ahora la matriz se multiplica por el escalar 1/sqrt(n-1)

    X = X*(raiz);

    return X;
}

void calcular_MatrizVt1(const vector<Dato>& training, int iter, int cant_kfold, int fold_actual){
    vector< Mat<double> > imag;

    for(int i = 0; i < training.size() ; i++){
        imag.push_back(training[i].imagen);
    } //Obtenemos solo las imagenes del training

    Mat<double> X = construiryCentrarX1(imag);

    Mat<double> Xt = X;
    Mat<double>::transpuesta(Xt); // Tomamos la transpuesta de X

    Mat<double> Mcov = (Xt*X);

    vector<double> autovalores;
    cerr<<"calcule la Matriz de covarianza\n";
    Mat<double>::baseAutovectores(Mcov,autovalores,iter, cant_kfold, fold_actual); //Escribe la matriz Vt en el archivo base_autovec.txt
    cerr<<"termine de calcular la baseAutovectores\n";
}


void knntask(int knn) {
    void (* metodo_resolucion)(Dato&, const vector<Dato>&, uint);
    metodo_resolucion = KNN;
    string file_name;

    for (int kfold = 2; kfold <= 10; kfold+=4) {
        for (int alpha = 30; alpha <= 190; alpha += 20) {
            file_name = "k_" + to_string(knn) + "-alpha_" + to_string(alpha) + "-kfold_" + to_string(kfold);
            cerr<<file_name<<"\n";
            //"k_" + to_string(k_nn) + "-alpha_"    + to_string(alpha) + "-kfold_" + to_string(k_kfold) + ".in";
            correr_Cross_Val(metodo_resolucion, file_name, "KNN", true);
        }
    }
}


int main(int argc, char const *argv[]) {
/*
    //hago las bases de verdad.
    for(int i = 2; i<=10; i += 4) {


        string nombre_archivo = "k_2-alpha_10-kfold_"+to_string(i);

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
        //cada fold del kfold = i
        for(int j = 0; j<i; ++j){
            vector<Dato> training, test;
            separador(datos, training, test, k_fold_file);
            //Mat<double> matriz_datos = construir_mat(training);
            //vector<double> autovalores;
            //Mat<double>::baseAutovectores(matriz_datos, autovalores, 100, i, j);
            calcular_MatrizVt1(training, 100, i, j);
        }

    }*/

    std::thread six (knntask, 6);
    std::thread ten (knntask, 10);
    std::thread fourteen (knntask, 14);

    six.join();
    ten.join();
    fourteen.join();


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
