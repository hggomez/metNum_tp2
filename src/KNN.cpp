#include <algorithm>
#include <queue>
#include <complex>

#include "Metodos_de_Resolucion.h"

using namespace std;

double distancia(const Mat<uint>& A, const Mat<uint>& B) {
    double res = 0.0;
    for (int i = 0; i < A.filas(); ++i) {
        for (int j = 0; j < A.columnas(); ++j) {
            auto dif = abs(A(i,j) - B(i,j));
            res += dif*dif;
        }
    }
    return sqrt(res);
}

struct menor {
    bool operator()(const pair<Etiqueta,double>& a,const pair<Etiqueta,double>& b) const{
        return a.second > b.second;
    }
};

void KNN(Dato& A, const vector<Dato>& training, uint k) {

    priority_queue<pair<Etiqueta,double>, vector<pair<Etiqueta,double> >, menor> distancias;

    for (auto B : training) {
        double d = distancia(A.imagen,B.imagen);
        distancias.push(pair<Etiqueta,double>(B.etiqueta, d));
    }

    vector<int> etiquetas(10, 0);
    for (uint i = 0; i < k; ++i) {
        Etiqueta e = distancias.top().first;
        etiquetas[e]++;
        distancias.pop();
    }

    auto max = max_element(etiquetas.begin(), etiquetas.end());

    A.etiqueta = (Etiqueta) (max - etiquetas.begin());
}