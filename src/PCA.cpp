#include <algorithm>
#include <queue>
#include <complex>

#include "Metodos_de_Resolucion.h"

using namespace std;

void PCA(const vector<Dato>& training, int alpha){

    vector< Mat<double> > imag;

    for(int i = 0; i < training.size() ; i++){
        imag.push_back(training[i].imagen);
    } //Obtenemos solo las imagenes del training

    Mat<double> X = Mat<double>::construiryCentrarX(imag);

    Mat<double> Xt = X;
    Mat<double>::transpuesta(Xt); // Tomamos la transpuesta de X

    Mat<double> Mcov = (Xt*X);

    //Mcov es la matriz de coviarianza que es simetrica. Diagonalizamos Mcov y obtenemos Vt (ortogonal) que tiene los autovectores de Mcov

   // Mat<T> Vt = Mat<T>()

   // vector< Mat<T> > Mat<T>::baseAutovectores(Mat<T> &A , vector<double> &autovalores, int iter,int alpha)

    // Finalmente el cambio de base del training es igual a Vt*Xt


}