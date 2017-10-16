CC=g++
CFLAGS=-std=c++11 -O3
DEPS = Dato.h Lectura.h Math.h Measure.h Metodos_de_Resolucion.h Test.h
OBJ = KNN.o Lectura.o PCA.o Test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

correrMain: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)