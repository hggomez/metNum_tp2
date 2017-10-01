//
// Created by javier on 28/09/17.
//
#include "Test.h"
#include <bitset>
#include <vecto>
#include <math>
#include <algorithm>


void generar_Test(int k_nn, int desde_alpha, int hasta_alpha, int skip_alpha, int k_kfold){
	//CHEQUEAR QUE K_KFOLD SEA MENOR QUE EL TAMAÑO DE CADA BUCKET
	// for (int i = 0; i < 10; ++i) {
 //        throw std::out_of_range("mat_ con 0 filas o 0 columnas");
 //    }

	vector<Dato> data;

	vector< deque<uint> > buckets(10);
	
	bitset<data.size()> testingMap;
	
	vector<int> subset_sizes(10);
	
	for (int i = 0; i < data.size(); ++i) {
		buckets[data[i].etiqueta].push_back(i);
	}

	for (int i = 0; i < buckets.size(); ++i) {
		subset_sizes[i] = (int) round(buckets[i].size() / k_kfold); 
		random_shuffle(buckets[i].begin(), buckets[i].end());
	}

	for (int i = 0; i < k_kfold; ++i){
		for(int j = 0; j < buckets.size(); ++j) {
			if(i < k_kfold) { 
				for (int k = 0; subset_sizes[j] < ; ++k) {
					testingMap[buckets[j].back()] = 1;
					buckets[j].pop_back();
				}
			} else {
				while (!buckets[j].empty()) {
					testingMap[buckets[j].back()] = 1;
					buckets[j].pop_back();
				}
			}
		}
		for (int k = 0; k < data.size(); ++k) {
			cout << testingMap[k] << " ";
		} cout << endl;
		testingMap.reset();
	}
}


void correr_Test(void (* metodo_resolucion)(Dato&, const vector<Dato>&, uint), int tipo_test);