#ifndef METODOS_TP1_MAT_H
#define METODOS_TP1_MAT_H

#include <stdexcept>
#include <iostream>
#include <cmath>
#include <cmath>
#include <vector>

#define EPS 0//1e-10 //Epsilon para la eliminacion gaussiana

using namespace std;

/*
Lo mas importantes es A[i][j] ahora es A(i, j), abajo explico por que.
la rep interna es un arreglo, no un arreglo de arreglos.
mientras leia como overlodear operadores me encontre con este link:
https://isocpp.org/wiki/faq/operator-overloading#matrix-subscript-op

que basicamente te dice que no seas gil usando [][] y uses (i,j)
la para acceder a A[col][fil] = col_ * fil + col. donde col_ es la cantidad
de columnas...
el pibe habla de que a veces guardar de la fila en espacios contiguos es mejor
y a veces guardar la col en espacios contiguos es mejor... con esto
nos resulta mas facil cambiar quienes son los elementos aledaños

col_ * fil + col guarda los elementos de una fila juntos
fil_*col + fil guarda los elementos de una columna juntos

bueno y un par de cosas mas que el chabon explica.

*/


/***
 * Clase para representacion de Matriz.
 * @tparam T Tipo de los elementos de la matriz.
 */
template<typename T>
class Mat {

public:

    /***
     * Constructor matriz vacia.
     */
    Mat();

    /***
     * Constructor matriz de filas x columnas
     * @param filas Cantidad de filas
     * @param columnas Cantidad de columnas
     */
    Mat(uint filas, uint columnas);

    /***
     * Constructor matriz de filas x columnas, con valorDefault en cada celda
     * @param filas Cantidad de filas
     * @param columnas Cantidad de columnas
     * @param valorDefault Valor default para cada celda
     */
    Mat(uint filas, uint columnas, const T &valorDefault);

    /***
     * Constructor matriz de filas x columnas en base a un array de datos de tipo T
     * @param filas Cantidad de filas
     * @param columnas Cantidad de columnas
     * @param datos Array de datos de tipo T, de longitud = filas x columnas
     */
    Mat(uint filas, uint columnas, T *datos);

    /***
     * Constructor por copia
     * @param copia Matriz a copiar
     */
    Mat(const Mat<T> &copia);

    /***
     * Operador de asignacion
     * @param matriz
     * @return matriz
     */
    Mat &operator=(Mat matriz);

    /***
     * Destructor
     */
    ~Mat();

    /***
     * Devuelve si la matriz es inversible.
     * como voy a hacer eliminacion gaussiana, voy a pedir una copia de la matriz.
     * cuando tengamos un metodo mas piola, genial. por ahora es eso.
     * @param matriz
     * @return
     */
    static bool inversible(Mat<T> matriz);

    /***
     * Modifica la matriz parametro haciendo la transpuesta de esta
     * @param matriz Matriz parametro
     */
    static void transpuesta(Mat<T> &matriz);

    /***
     * Construye una matriz identidad de tamanio size x size
     * @param size Tamanio de la matriz
     * @return Matriz identidad de size x size
     */
    static Mat<T> crearIdentidad(int size);

    /**
     * Potencia de matrices recursiva
     * @param matriz Matriz parametro
     * @param potencia
     * @return matriz ^ potencia
     */
    static Mat<T> potHelper(const Mat<T> &matriz, int potencia);


    /***
     *
     * @param A matriz aumentada
     * @param b columna aumentada
     * @return true si es compatible determinado, false si es compatible indeterminado.
     */
    static bool eliminacionGaussiana(Mat<T> &A, Mat<T> &b);

    /***
     * Pivoteo parcial. Ayuda a reducir errores de redondeo, es menos probable que se haga +/- con numeros muy grandes o chicos.
     * @param A Matriz aumentada
     * @param b Columna aumentada
     */
    static void pivoteoParcial(Mat<T> &A, Mat<T> &b, int k);

    /**
     * Resuelve la ecuacion Ax = b, A es modificada tal que sea la union de L y U.
     * como L tiene unos en las diagonales, no nos interesa guardar esa información.
     * @param A Matriz resuelta
     * @param b Columna de solucion
     * @return Matriz x
     */
    static Mat<T> sustitucionHaciaAtras(const Mat<T> &A,const Mat<T> &b);

    /***
     * Resuelve un sistema Ax=b donde A es una matriz triangular inferior (sustitucion hacia adelante)
     * El tercer parametro se agrega para no tener que almacenar L y U en matrices diferentes y poder hacer factorización
     * LU con codigo ya escrito y un poco modificado
     * @param L Matriz triangular inferior
     * @param b columna resupuesta
     * @param unos_diagonal si tiene que considerar la diagonal como algo valido o como valores uno
     * @return
     */
    static Mat<T> sustitucion_HaciaAdelante(const Mat<T>& A,const Mat<T>& b, bool unos_diagonal);

    /***
     * Resuelve la ecuacion Ax = b, con eliminacion gaussiana y pivoteo parcial
     * @param A Matriz aumentada
     * @param b Columna aumentada
     * @return Matriz x
     */
    static Mat<T> resolverPorGaussYPivoteoParcial(Mat<T> &A, Mat<T> &b);

    /***
     * dada una matriz LU y un vector b devuelve su solución
     * @param LU la matriz A escrita de forma LU, se puede combinar y descartar la diagonal de 1 de L
     * @param b el vector b
     * @return devuelve la solucion de hacer Ax = b donde A es L*U
     */
    static Mat<T> resolver_LU(const Mat<T> & LU, Mat<T>& b);

    int MatrixInversion(Mat<T>& AInverse);

//    static Mat<T> factCholesky(MatA<T> &A);

    /**
     * Resuelve el sistema Ax = L(L^t)x=b , que se resuelve con estas dos ecuaciones : (L^tx) = y , Ly = b
     * @param A Matriz
     * @param b Matriz columna respuesta
     * @return x Matriz de incognitas
     */
//    static Mat<T> resolverCholesky(MatA<T> &A, Mat<T> &b);

    /**
     * Calcula la norma vectorial. Funciona con vector fila y vector columna norma2
     * @param A Vector
     * @return norma vectorial
     */
    static double normaVectorial(const Mat<T> &A);

    /**
     * Calcula un autovalor de la matriz A con el metodo de potencia ( Av = lambda*v)
     * @param A matriz
     * @param v vector
     * @param iter numero maximo de iteraciones.
     * @return autovalor
     */
    static double calcularAutovalor(Mat<T> &A , Mat<T> &v, int iter);

    /**
     * Modifica la matriz original con la deflacion para obtener los autovalores 0,a2,a3.. con autovectores asociados v1,v2...
     * @param A matriz
     * @param v1 autovector asociado al autovalor a1
     * @param a1 autovalor.
     */
    static void deflacion(Mat<T> &A , Mat<T> &v1, double a1);

    /**
     * Operador de acceso para clase Mat. Equivalente a Mat[fila][columna]
     * Permite modificar la estructura
     * @param fila
     * @param columna
     * @return Elemento de tipo T modificable
     */
    T &operator()(uint fila, uint columna);

    /**
     * Operador de acceso para clase Mat. Equivalente a Mat[fila][columna]
     * No permite modificar la estructura
     * @param fila
     * @param columna
     * @return Elemento de tipo T no modificable
     */
    const T& operator()(uint fila, uint columna) const;

    /**
     * Cantidad de filas
     * @return Cantidad de filas
     */
    uint filas() const;

    /**
     * Cantidad de columnas
     * @return Cantidad de columnas
     */
    uint columnas() const;

protected:
    /**
     * Array interno de elementos.
     */
    T *mat_;

private:
    uint fil_, col_;

    /**
     * Funcion swap de matrices
     * @param A
     * @param B
     */
    void swap(Mat &A, Mat &B);
};

template<typename T>
Mat<T> operator+(const Mat<T> &a, const Mat<T> &b);

template<typename T>
Mat<T> operator-(const Mat<T> &a, const Mat<T> &b);

template<typename T>
//la version naive, despues si sabemos la polenta podemos implementarla
Mat<T> operator*(const Mat<T> &a, const Mat<T> &b);

template<typename T>
//producto por escalar
Mat<T> operator*(const Mat<T> &a, const T &b);

template<typename T>
Mat<T> operator*(const T &b, const Mat<T> &a);

template<typename T>
//para dividir facil
Mat<T> operator/(const Mat<T> &a, const T &b);

template<typename T>
Mat<T> operator/(const T &b, const Mat<T> &a);

//potencia
template<typename T>
Mat<T> operator^(const Mat<T> &a, int b);

template<typename T>
//imprime la cantidad de filas, la cantidad de columnas y despues la mat_
std::ostream &operator<<(std::ostream &os, const Mat<T> &m);

template<typename T>
Mat<T>::Mat():fil_(0), col_(0), mat_(NULL) {}

template<typename T>
Mat<T>::Mat(uint filas, uint columnas):fil_(filas), col_(columnas) {

    if (fil_ == 0 || col_ == 0) {
        throw std::out_of_range("mat_ con 0 filas o 0 columnas");
    }

    mat_ = new T[fil_ * col_];
}

template<typename T>
Mat<T>::Mat(uint filas, uint columnas, const T &valorDefault):fil_(filas), col_(columnas) {
    if (fil_ == 0 || col_ == 0) {
        throw std::out_of_range("mat_ con 0 filas o 0 columnas");
    }
    mat_ = new T[fil_ * col_];

    for (uint i = 0; i < fil_; ++i) {
        for (uint j = 0; j < col_; ++j) {
            mat_[col_ * i + j] = valorDefault;
        }
    }
}

template<typename T>
Mat<T>::Mat(uint filas, uint columnas, T *datos):fil_(filas), col_(columnas) {
    if (fil_ == 0 || col_ == 0) {
        throw std::out_of_range("mat_ con 0 filas o 0 columnas");
    }
    mat_ = new T[fil_ * col_];
    for (uint i = 0; i < fil_ * col_; ++i) {
        mat_[i] = datos[i];
    }

}

template<typename T>
Mat<T>::Mat(const Mat<T> &copia) {
    fil_ = copia.filas();
    col_ = copia.columnas();


    mat_ = new T[fil_ * col_];

    for (uint i = 0; i < fil_; ++i) {
        for (uint j = 0; j < col_; ++j) {
            mat_[col_ * i + j] = copia(i, j);
        }
    }

}

template<typename T>
Mat<T> &Mat<T>::operator=(Mat matriz) {
    swap(*this, matriz);
    return *this;
}

template<typename T>
void Mat<T>::swap(Mat &A, Mat &B) {
    std::swap(A.fil_, B.fil_);
    std::swap(A.col_, B.col_);
    std::swap(A.mat_, B.mat_);
}

template<typename T>
Mat<T>::~Mat() {
    delete[] mat_;
}

/***
 * Devuelve la cantidad de filas de la matriz.
 * @tparam T El tipo de los elementos de la matriz.
 * @return La cantidad de filas de la matriz.
 */

template<typename T>
uint Mat<T>::filas() const {
    return fil_;
}

template<typename T>
uint Mat<T>::columnas() const {
    return col_;
}

template<typename T>
double Mat<T>::normaVectorial(const Mat<T> &A) {
    double norma = 0;

    for (uint fila = 0; fila < A.filas(); ++fila) {
        for (uint columna = 0; columna < A.columnas(); ++columna) {
            norma += pow(A(fila, columna), 2);
        }
    }
    norma = sqrt(norma);
    return norma;
}

template<typename T>
bool Mat<T>::inversible(Mat<T> matriz) {
    Mat<T> vector(matriz.columnas(), 1, (T) 0);
    return eliminacionGaussiana(matriz, vector);
}

template<typename T>
void Mat<T>::transpuesta(Mat<T> &matriz) {
    Mat<T> at(matriz.columnas(), matriz.filas());
    for (int i = 0; i < matriz.filas(); ++i) {
        for (int j = 0; j < matriz.columnas(); ++j) {
            at(j, i) = matriz(i, j);
        }
    }
    matriz = at;

}

template<typename T>
Mat<T> Mat<T>::crearIdentidad(int size) {
    Mat<T> temp = Mat(size, size, 0);
    for (int i = 0; i < temp.filas(); ++i) {
        temp(i, i) = 1;
    }
    return temp;
}

template<typename T>
void Mat<T>::pivoteoParcial(Mat<T> &A, Mat<T> &b, int k) {
   int indice_max = k;
    T valor_max = abs(A(k,k));
    for (int i = k + 1; i < A.filas(); ++i) {
       if (valor_max < abs(A(i, k))) {
            valor_max = abs(A(i,k));
           indice_max = i;
       }
   }
    for (int columna = 0; columna < A.columnas(); columna++) {
        T swap = A(k, columna);
        A(k, columna) = A(indice_max, columna);
        A(indice_max, columna) = swap;
    }
    T swap = b(k, 0);
    b(k, 0) = b(indice_max, 0);
    b(indice_max, 0) = swap;

}

template<typename T>
Mat<T> Mat<T>::sustitucionHaciaAtras(const Mat<T> &A,const Mat<T> &b) {
    // x es la matriz respuesta
    Mat<T> x = Mat(A.columnas(), 1);

    uint xFilas = x.filas();

    // Despejo en la ultima fila y me queda resuelta 1 incognita
    x(xFilas - 1, 0) = (double) b(xFilas - 1, 0) / (double) A(xFilas - 1, xFilas - 1);

    // Puede que al despejar me de 0
    if (abs(x(xFilas - 1, 0)) < EPS )
        x(xFilas - 1, 0) = 0;

    for (int fila = xFilas - 2; fila >= 0; fila--) {  // Voy haciendo la sustitucion hacia atras

        double sum = 0;
        for (int i = fila + 1; i < xFilas; ++i)
            sum += A(fila, i) * x(i, 0);

        // Ecuacion que queda al despejar la variable de la fila fila
        x(fila, 0) = (double) (b(fila, 0) - sum) / (double) A(fila, fila);

        // Puede dar 0
        if (abs(x(fila, 0)) < EPS)
            x(fila, 0) = 0;
    }
    return x;
}

template<class T>
Mat<T> Mat<T>::sustitucion_HaciaAdelante(const Mat<T>& A,const Mat<T>& b, bool unos_diagonal){ // Resuelve un sistema Ax = b donde A es triangular inferior
    // x es la matriz respuesta
    Mat<T> x = Mat(A.columnas(), 1);

    // Despejo en la ultima fila y me queda resuelta 1 incognita
    x(0, 0) = (double) b(0,0) / (double) A(0,0);

    // Puede que al despejar me de 0
    if (x(0,0) < EPS && x(0, 0) > -1 * EPS)
        x(0,0) = 0;

    for (int i = 1; i < A.filas(); ++i) {  // Voy haciendo la sustitucion hacia adelante

        double sum = 0;
        for (int j = 0; j <= (i-1); ++j)
            sum += A(i,j) * x(j, 0);

        double dividendo = (double) A(i,i);
        if(unos_diagonal) dividendo = 1;
        // Ecuacion que queda al despejar la variable de la fila fila
        x(i,0) = (double) (b(i, 0) - sum) / dividendo;

        // Puede dar 0
        if (x(i, 0) < EPS && x(i, 0) > -1 * EPS)
            x(i, 0) = 0;
    }
    return x;
}

template<typename T>
bool Mat<T>::eliminacionGaussiana(Mat<T> &A, Mat<T> &b) {
    bool inversible = true;
    for (int k = 0; k < A.filas(); ++k) {
        pivoteoParcial(A, b, k);
        for (int fila = k + 1; fila < A.filas(); fila++) {
            double cociente = (double) A(fila, k) / (double) A(k, k);
            A(fila, k) = cociente;

            for (int columna = k + 1; columna < A.columnas(); columna++) {

                A(fila, columna) = A(fila, columna) - cociente * A(k, columna);

                // Si el resultado esta dentro del intervalo, es 0
                if (abs(A(fila, columna)) < EPS)
                    A(fila, columna) = 0;
            }

            // Hacemos la misma operacion en la columna aumentada
            b(fila, 0) = b(fila, 0) - cociente * b(k, 0);

            if (abs(b(fila, 0)) < EPS)
                b(fila, 0) = 0;
        }
    }

    if ((A(A.filas() - 1, A.columnas() - 1) == 0) && (b(b.filas() - 1, 0) != 0)) {
        inversible = false;
        throw domain_error("El sistema es indeterminado - no tiene solucion");
    }

    // Si la matriz es cuadrada me fijo si hay infinitas soluciones
    if (A.filas() == A.columnas()) {
        if ((A(A.filas() - 1, A.columnas() - 1) == 0) && (b(b.filas() - 1, 0) == 0)) {
            inversible = false;
        }
    }
    return inversible;
}

template<typename T>
Mat<T> Mat<T>::resolverPorGaussYPivoteoParcial(Mat<T> &A, Mat<T> &b) {
    bool compatible = eliminacionGaussiana(A, b);
    if(!compatible) throw domain_error("El sistema es compatible indeterminado - tiene infinitas soluciones");
    return sustitucionHaciaAtras(A, b);
}

template<typename T>
Mat<T> Mat<T>::resolver_LU(const Mat<T> & LU, Mat<T>& b){
    Mat<T> sol_parcial = sustitucionHaciaAtras(LU, b);
    Mat<T> solucion = sustitucion_HaciaAdelante(LU, sol_parcial, true);
    return solucion;
}

template<typename T>
Mat<T> Mat<T>::potHelper(const Mat<T> &matriz, int potencia) {
    Mat<T> aux(matriz);

    if (potencia == 0) {
        return crearIdentidad(aux.filas());
    } else if (potencia == 1) {
        return aux;
    } else if (potencia % 2 == 0) { // si potencia es par
        return potHelper(aux * aux, potencia / 2);
    } else { // si potencia es impar
        return aux * potHelper(aux * aux, (potencia - 1) / 2);
    }
}

template<typename T>
T &Mat<T>::operator()(uint fila, uint columna) {

    if (fila >= fil_ || columna >= col_ || fila < 0 || columna < 0) {
        throw std::out_of_range("Matriz fuera de rango");
    }
    return mat_[col_ * fila + columna];
}

template<typename T>
const T& Mat<T>::operator()(uint fila, uint columna) const {
    if (fila >= fil_ || columna >= col_ || fila < 0 || columna < 0) {
        throw std::out_of_range("Matriz fuera de rango");
    }
    return mat_[col_ * fila + columna];
}

template<typename T>
Mat<T> operator+(const Mat<T> &a, const Mat<T> &b) {
    if (a.filas() != b.filas() || a.columnas() != b.columnas()) {
        throw std::out_of_range("Sumando dos matrices de distinta dimension");
    }
    Mat<T> aux(a);

    for (uint i = 0; i < a.filas(); ++i) {
        for (uint j = 0; j < a.columnas(); ++j) {
            aux(i, j) = aux(i, j) + b(i, j);
        }
    }
    return aux;
}

template<typename T>
Mat<T> operator-(const Mat<T> &a, const Mat<T> &b) {
    if (a.filas() != b.filas() || a.columnas() != b.columnas()) {
        throw std::out_of_range("Restando dos matrices de distinta dimension");
    }
    Mat<T> aux(a);

    for (uint i = 0; i < a.filas(); ++i) {
        for (uint j = 0; j < a.columnas(); ++j) {
            aux(i, j) = aux(i, j) - b(i, j);
        }
    }
    return aux;
}

//producto por escalar
template<typename T>
Mat<T> operator*(const Mat<T> &a, const T &b) {
    Mat<T> aux(a);

    for (uint i = 0; i < a.filas(); ++i) {
        for (uint j = 0; j < a.columnas(); ++j) {
            aux(i, j) = aux(i, j) * b;
        }
    }
    return aux;
}

template<typename T>
Mat<T> operator*(const T &b, const Mat<T> &a) {
    return a*b;
}

//para dividir facil
template<typename T>
Mat<T> operator/(const Mat<T> &a, const T &b) {
    if (b == 0) {
        throw std::domain_error("dividiendo una matriz por 0");
    }
    Mat<T> aux(a);

    for (uint i = 0; i < a.filas(); ++i) {
        for (uint j = 0; j < a.columnas(); ++j) {
            aux(i, j) = aux(i, j) / b;
        }
    }
    return aux;
}

template<typename T>
Mat<T> operator/(const T &b, const Mat<T> &a) {
    if (b == 0) {
        throw std::domain_error("dividiendo una matriz por 0");
    }
    Mat<T> aux(a);

    for (uint i = 0; i < a.filas(); ++i) {
        for (uint j = 0; j < a.columnas(); ++j) {
            aux(i, j) = aux(i, j) / b;
        }
    }
    return aux;
}

//la version naive, despues si sabemos la polenta podemos implementarla
template<typename T>
Mat<T> operator*(const Mat<T> &a, const Mat<T> &b) {
    if ( a.columnas() != b.filas() ) {
        throw std::range_error("Multiplicando matriz con dimensiones erroneas");
    }

    Mat<T> aux(a.filas(), b.columnas());

    for (uint i = 0; i < aux.filas(); ++i) {
        for (uint j = 0; j < aux.columnas(); ++j) {
            T acum = 0;
            for (uint k = 0; k < b.filas(); ++k) {
                acum += a(i, k) * b(k, j);
            }
            aux(i, j) = acum;
        }
    }
    return aux;
}

template<typename T>
Mat<T> operator^(const Mat<T> &a, int b) {
    return Mat<T>::potHelper(a, b);
}


template<typename T>
std::ostream &operator<<(std::ostream &os, const Mat<T> &m) {
    for (uint i = 0; i < m.filas(); ++i) {
        for (uint j = 0; j < m.columnas(); ++j) {
            os << m(i, j) << " ";
        }
        os << "\n";
    }
    os << endl;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Mat<std::vector<T> > &m) {
    for (uint i = 0; i < m.filas(); ++i) {
        for (uint j = 0; j < m.columnas(); ++j) {
            for (uint k = 0; k < m(0,0).size(); ++k)
            os << m(i, j)[k] << " ";
        }
        os << "\n";
    }
}

template<typename T>
//crea una matriz formato "n \n, m\n a11 a12 a 13 a14 ... a1m a21 .. anm"
std::istream &operator>>(std::istream &is, Mat<T> &mat) {
    uint n, m;
    is >> n >> m;
    Mat<T> aux(n, m);
    for (uint i = 0; i < n; ++i) {
        for (uint j = 0; j < m; ++j) {
            is >> aux(i, j);
        }
    }
    mat = aux;
}

template <typename T>
int Mat<T>::MatrixInversion(Mat<T>& AInverse) {
    // A = input matrix (n x n)
    // n = dimension of A
    // AInverse = inverted matrix (n x n)
    // This function inverts a matrix based on the Gauss Jordan method.
    // The function returns 1 on success, 0 on failure.
    int i, j, iPass, imx, icol, irow, n;
    double det, temp, pivot, factor;
    n = this->filas();
    det = 1;

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            AInverse(j,i) = 0;
//            ac(j,i) = (*this)(j,i);
        }
        AInverse(i,i) = 1;
    }

    // The current pivot row is iPass.
    // For each pass, first find the maximum element in the pivot column.
    for (iPass = 0; iPass < n; iPass++) {
        imx = iPass;
        for (irow = iPass; irow < n; irow++) {
            if (fabs((*this)(irow, iPass)) > fabs((*this)(imx, iPass))) imx = irow;
        }
        // Interchange the elements of row iPass and row imx in both A and AInverse.
        if (imx != iPass) {
            for (icol = 0; icol < n; icol++) {
                temp = AInverse(iPass, icol);
                AInverse(iPass, icol) = AInverse(imx, icol);
                AInverse(imx, icol) = temp;

                if (icol >= iPass) {
                    temp = (*this)(imx, icol);
                    (*this)(iPass, icol) = (*this)(imx, icol);
                    (*this)(imx, icol) = temp;
                }
            }
        }

        // The current pivot is now A[iPass][iPass].
        // The determinant is the product of the pivot elements.
        pivot = (*this)(iPass, iPass);
        det = det * pivot;
        if (det == 0) {
//            free(ac);
            return 0;
        }

        for (icol = 0; icol < n; icol++) {
            // Normalize the pivot row by dividing by the pivot element.
            AInverse(iPass, icol) = AInverse(iPass, icol) / pivot;
            if (icol >= iPass) (*this)(iPass, icol) = (*this)(iPass, icol) / pivot;
        }

        for (irow = 0; irow < n; irow++)
            // Add a multiple of the pivot row to each row.  The multiple factor
            // is chosen so that the element of A on the pivot column is 0.
        {
            if (irow != iPass) factor = (*this)(irow, iPass);
            for (icol = 0; icol < n; icol++) {
                if (irow != iPass) {
                    AInverse(irow, icol) -= factor * AInverse(iPass, icol);
                    (*this)(irow, icol) -= factor * (*this)(iPass, icol);
                }
            }
        }
    }

//    free(ac);
    return 1;
}

template <typename T>
double Mat<T>::calcularAutovalor(Mat<T> &A , Mat<T> &v, int iter){ // Algoritmo basado en la diapo de la clase.

    double autoval;
    for(int i = 0 ; i < iter; i++){
        v = A*v;
        double norma = Mat<double>::normaVectorial(v);
        v = v*(1/norma);
    }
    Mat<double> vt = v;
    vt.transpuesta(vt);
    Mat<double> denominador = vt*v; //Es una matriz de 1x1 , en realidad es el producto interno de dos vectores
    Mat<double> numerador = vt*(A*v); // Es una matriz de 1x1 , es el producto interno de dos vectores;

    autoval = numerador(0,0)/denominador(0,0);

    return autoval;  // en v queda guardado el autovector asociado al autovalor
}


template <typename T>
void Mat<T>::deflacion(Mat<T> &A , Mat<T> &v1, double a1){
// Sacado de la diapo de clase : (A - a1*v1*v1^(t))v_i = A*v_i - a1v1(v1^t *v_i) = a_i*v_i
// Esta funcion calcula (A-a1*v1*v1^(t))
    Mat<T> v1t = v1;
    v1t.transpuesta(v1t);
    A = A - (a1* (v1*v1t));
}


#endif //METODOS_TP1_MAT_H
