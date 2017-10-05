#include <algorithm>
#include <queue>
#include <complex>

#include "Metodos_de_Resolucion.h"

using namespace std;

double distancia(const Mat<double>& A, const Mat<double>& B) {
    double res = 0.0;
    for (int i = 0; i < A.filas(); ++i) {
        for (int j = 0; j < A.columnas(); ++j) {
            auto dif = abs(A(i,j) - B(i,j));
            res += dif*dif;
        }
    }
    return res;
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


double distancia_maxima(const vector<Dato>& training_set) {

    vector<Dato> vacio;
    vacio.reserve(training_set.size() / 10);
    vector<vector<Dato> > imagenes_por_etiquetas(10, vacio);

    for (auto dato : training_set) {
        imagenes_por_etiquetas[dato.etiqueta].push_back(dato);
    }

    vector<double> distancias(10, 0.0);

    for (int k = 0; k < 10; ++k) {
        double maximo = 0.0;
        double minimo = 0.0;
        for (int i = 0; i < imagenes_por_etiquetas[k].size(); ++i) {
            for (int j = i+1; j < imagenes_por_etiquetas[k].size(); ++j) {
                double d = distancia(imagenes_por_etiquetas[k][i].imagen, imagenes_por_etiquetas[k][j].imagen);
                maximo = ((maximo < d) ? d : maximo);
                minimo = ((maximo > d) ? d : minimo);
            }
        }
        distancias[k] = maximo;
        cout  << "maximo: " << k << ' ' << maximo << endl;
        cout  << "minimo: " << k << ' ' << minimo << endl;
    }

    return min_element(distancias.begin(), distancias.end()).operator*();
}

void KNN_distancia(Dato& A, const vector<Dato>& training, uint k, double distancia_max) {

    priority_queue<pair<Etiqueta,double>, vector<pair<Etiqueta,double> >, menor> distancias;

    for (auto B : training) {
        double d = distancia(A.imagen,B.imagen);
        distancias.push(pair<Etiqueta,double>(B.etiqueta, d));
    }

    vector<int> etiquetas(10, 0);
    for (uint i = 0; i < k; ++i) {
        Etiqueta e = distancias.top().first;
        if (distancias.top().second <= distancia_max) {
            etiquetas[e]++;
            distancias.pop();
        }
    }

    auto max = max_element(etiquetas.begin(), etiquetas.end());

    A.etiqueta = (Etiqueta) (max - etiquetas.begin());
}






