#include <algorithm>
#include <queue>
#include <complex>
#include <iostream>

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


void distancias_maximas(const vector<Dato>& training_set) {

    cerr << "Calculando distancias maximas... ";

    vector<Dato> vacio;
    vacio.reserve(training_set.size() / 10);
    vector<vector<Dato> > imagenes_por_etiquetas(10, vacio);

    for (auto dato : training_set) {
        imagenes_por_etiquetas[dato.etiqueta].push_back(dato);
    }

    vector<double> distancias(10, 0.0);

    for (int k = 0; k < 10; ++k) {
        double maximo = 0.0;
        for (int i = 0; i < imagenes_por_etiquetas[k].size(); ++i) {
            for (int j = i+1; j < imagenes_por_etiquetas[k].size(); ++j) {
                double d = distancia(imagenes_por_etiquetas[k][i].imagen, imagenes_por_etiquetas[k][j].imagen);
                maximo = ((maximo < d) ? d : maximo);
            }
        }
        distancias[k] = maximo;
    }

    string output_filepath = "../data/distancias_maximas.csv";
    ofstream output_file;

    output_file.precision(std::numeric_limits<double>::max_digits10);

    output_file.open(output_filepath, ios_base::trunc);

    output_file << "Label,distancia maxima" << endl;
    for (int i = 0; i < 10; ++i)
        output_file << i << ',' << fixed << distancias[i] << endl;

    output_file.close();

    cerr << "terminado" << endl;
}

vector<double> leer_distancia(string filepath) {
    vector<double> res(10, 0.0);

    ifstream file;
    file.open(filepath);

    string data;
    getline(file, data);
    data = "";
    for (int i = 0; i < 10; ++i) {
        getline(file, data);
        auto it = find(data.begin(), data.end(), ',');
        it++;
        string numero;
        while (*it != '\000' && *it != EOF && *it != '\r') {
            numero.append(1, *it);
            it++;
        }

        res[i] = stod(numero);
    }
    file.close();
    return res;
}

void KNN_distancia(Dato& A, const vector<Dato>& training, uint k) {

    vector<double> distancias_maximas = leer_distancia("../data/distancias_maximas.csv");
    double distancia_max = max_element(distancias_maximas.begin(), distancias_maximas.end()).operator*() / 2;

    priority_queue<pair<Etiqueta,double>, vector<pair<Etiqueta,double> >, menor> distancias;

    for (auto B : training) {
        double d = distancia(A.imagen,B.imagen);
        distancias.push(pair<Etiqueta,double>(B.etiqueta, d));
    }

    vector<int> etiquetas(10, 0);


    while (!distancias.empty() && distancias.top().second <= distancia_max) {
        Etiqueta e = distancias.top().first;
        etiquetas[e]++;
        distancias.pop();
    }


//    for (uint i = 0; i < k; ++i) {
//        Etiqueta e = distancias.top().first;
//        etiquetas[e]++;
//
//        if (distancias.top().second <= distancia_max)
//            distancias.pop();
//    }

    auto max = max_element(etiquetas.begin(), etiquetas.end());

    A.etiqueta = (Etiqueta) (max - etiquetas.begin());
}






