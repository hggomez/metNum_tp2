#include <algorithm>
#include <queue>
#include <complex>
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>

#include "Metodos_de_Resolucion.h"
//#include "Mat.h"
//#include "Dato.h"
using namespace std;

template <typename T>
Mat<T> construiryCentrarX(vector< Mat<T> > &S){ //Tengo la secuencia de datos x(1) ,x(2), ... en T

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

void calcular_MatrizVt(const vector<Dato>& training, int iter, int cant_kfold, int fold_actual){
    vector< Mat<double> > imag;

    for(int i = 0; i < training.size() ; i++){
        imag.push_back(training[i].imagen);
    } //Obtenemos solo las imagenes del training

    Mat<double> X = construiryCentrarX(imag);

    Mat<double> Xt = X;
    Mat<double>::transpuesta(Xt); // Tomamos la transpuesta de X

    Mat<double> Mcov = (Xt*X);

    vector<double> autovalores;
    cerr<<"calcule la Matriz de covarianza\n";
    Mat<double>::baseAutovectores(Mcov,autovalores,iter, cant_kfold, fold_actual); //Escribe la matriz Vt en el archivo base_autovec.txt
    cerr<<"termine de calcular la baseAutovectores\n";
}


void PCA(vector<Dato>& training, int alpha, int cant_kfold, int fold_actual) {

    string line;
    ifstream autovec_archivo ("../src/base_autovec("+to_string(cant_kfold)+")("+to_string(fold_actual)+".txt");

    int filaVt;
    int columVt;
    if(!autovec_archivo.is_open()){
        cerr<<"calculo la matriz por primera vez\n";
        cerr<<"../src/base_autovec"+to_string(cant_kfold)+")("+to_string(fold_actual)+".txt\n";
        calcular_MatrizVt(training, 100, cant_kfold, fold_actual);
        autovec_archivo.open("../src/base_autovec"+to_string(cant_kfold)+")("+to_string(fold_actual)+".txt", ios_base::in);
        cerr<<"termine de calcular la matriz\n";
    }
    autovec_archivo >> filaVt;
    autovec_archivo.ignore(numeric_limits<streamsize>::max(),',');
    autovec_archivo >> columVt;
    autovec_archivo.ignore(numeric_limits<streamsize>::max(),'\n'); //Salteo la primer linea de dimension
    autovec_archivo.ignore(numeric_limits<streamsize>::max(),'\n'); // Salteo la 2da linea de autovalores
    autovec_archivo.ignore(numeric_limits<streamsize>::max(),'\n'); // Salteo la declaracion de la matriz

    Mat<double> Vt = Mat<double>(alpha,columVt);

    if (autovec_archivo.is_open()) {
       int i = 0;
        while(i< alpha && i < filaVt) {
            getline (autovec_archivo,line);
            istringstream s(line);
            double val;
            int j = 0;
            while (s >> val) {
                Vt(i, j) = val;
                j++;
            }
            i++;
        }
        autovec_archivo.close();
    }

    else cout << "Unable to open file";


    // Procedemos a realizar el cambio de base del training que es igual a Vt*Xt
    // Construimos la X
    vector< Mat<double> > imag;

    for(int i = 0; i < training.size() ; i++){
        imag.push_back(training[i].imagen);
    } //Obtenemos solo las imagenes del training

    Mat<double> X = construiryCentrarX(imag); // X(#imagen,dimImagen)

    Mat<double> Xt = X;
    Mat<double>::transpuesta(Xt); // Tomamos la transpuesta de X
    cerr<<"Traspuse X\n";
    // Notar que Vt(alpha,dimImagen) Xt(dimImagen,#imagenes) -> nuevaBase(alpha,#imagenes) , es decir, la columnas de nuevaBase
    // son las imagenes de la nueva base. #imagenes = training.size()
    Mat<double> nuevaBase = Vt*Xt;
    cerr<<"cambie la base\n";

        for (int columna = 0; columna < nuevaBase.columnas(); columna++) {
            Mat<double> colj = Mat<double>(nuevaBase.filas(), 1);
            for (int fila = 0; fila < nuevaBase.filas(); fila++) {
                colj(fila, 0) = nuevaBase(fila,columna);
            }
            training[columna].imagen = colj;
        }

}
