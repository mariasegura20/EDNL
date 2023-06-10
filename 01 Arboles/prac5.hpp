#include "TAD Conocidos/abin.hpp"
#include "TAD Conocidos/agen.hpp"
#include "prac3.hpp"

// Ejercicio 1
void eliminarNodo(Abin<int>& A, int valor)
{
    Abin<int>::nodo nodoValor = buscarNodo(A.raiz(), A, valor);
    if (A.elemento(nodoValor) == valor) {
        borrarNodo(nodoValor, A);
    }
}

Abin<int>::nodo buscarNodo(typename Abin<int>::nodo n, const Abin<int>& A, int valor)
{
    if (n == Abin<int>::NODO_NULO)
        return n;
    else {
        int elementoActual = A.elemento(n);
        if (elementoActual == valor)
            return n;
        else if (elementoActual < valor) {
            Abin<int>::nodo izq = buscarNodo(A.hijoIzqdo(n), A, valor);
            if (izq == Abin<int>::NODO_NULO)
                return buscarNodo(A.hijoDrcho(n), A, valor);
            else
                return izq;
        }
    }
}

void borrarNodo(typename Abin<int>::nodo n, Abin<int>& A)
{
    if (A.hijoIzqdo(A.padre(n)) == n)
        A.eliminarHijoIzqdo(A.padre(n));
    else
        A.eliminarHijoDrcho(A.padre(n));
}

// APO MIN-MAX
template <typename T> class ApoMinMax {
    public:
        explicit ApoMinMax(size_t maxNodos);
        void insertar(const T& e);
        void suprimirMax();
        ~ApoMinMax();
    private:
        typedef size_t nodo; // índice del vector
        T* nodos; // vector de nodos
        size_t maxNodos; // tamaño del vector
        size_t numNodos; // último nodo del árbol
        nodo padre(nodo i) const { return (i - 1) / 2; }
        nodo hIzq(nodo i) const { return 2 * i + 1; }
        nodo hDer(nodo i) const { return 2 * i + 2; }
        void flotar();
        void hundir(nodo i);
};

// Ejercicio 2
template <typename T>
void ApoMinMax<T>::insertar(const T& e)
{
    assert(numNodos < maxNodos);
    nodos[numNodos] = e;
    flotar();
    numNodos++;
}

template <typename T>
void ApoMinMax<T>::flotar()
{
    nodo i = numNodos;
    if (log2(i+1) % 2 == 0) { // NIVEL MIN (log2(i+1) es la profundidad del nodo i)
        if (nodos[i] > nodos[padre(i)]) {// Está mal colocado con respecto a su padre
            T eltoFlote = nodos[i];
            nodo indiceFlote = padre(i);
            nodos[i] = nodos[indiceFlote];

            while (padre(padre(indiceFlote)) > 0 && eltoFlote > nodos[padre(padre(indiceFlote))])
            {
                nodos[indiceFlote] = nodos[padre(padre(indiceFlote))];
                indiceFlote = padre(padre(indiceFlote));
            }

            nodos[indiceFlote] = eltoFlote;
        }
        else if (nodos[i] < nodos[padre(padre(i))]) {   // Está mal colocado con respecto a su abuelo
            T eltoFlote = nodos[i];
            nodo indiceFlote = padre(padre(i));
            nodos[i] = nodos[indiceFlote];

            while (padre(padre(indiceFlote)) > 0 && eltoFlote < nodos[padre(padre(indiceFlote))])
            {
                nodos[indiceFlote] = nodos[padre(padre(indiceFlote))];
                indiceFlote = padre(padre(indiceFlote));
            } 

            nodos[indiceFlote] = eltoFlote;
        }
    }
    else {  // Máximos
       if (nodos[i] < nodos[padre(i)]) {// Está mal colocado con respecto a su padre
            T eltoFlote = nodos[i];
            nodo indiceFlote = padre(i);
            nodos[i] = nodos[indiceFlote];

            while (padre(padre(indiceFlote)) > 0 && eltoFlote < nodos[padre(padre(indiceFlote))])
            {
                nodos[indiceFlote] = nodos[padre(padre(indiceFlote))];
                indiceFlote = padre(padre(indiceFlote));
            }

            nodos[indiceFlote] = eltoFlote;
        }
        else if (nodos[i] > nodos[padre(padre(i))]) {   // Está mal colocado con respecto a su abuelo
            T eltoFlote = nodos[i];
            nodo indiceFlote = padre(padre(i));
            nodos[i] = nodos[indiceFlote];

            while (padre(padre(indiceFlote)) > 0 && eltoFlote > nodos[padre(padre(indiceFlote))])
            {
                nodos[indiceFlote] = nodos[padre(padre(indiceFlote))];
                indiceFlote = padre(padre(indiceFlote));
            } 

            nodos[indiceFlote] = eltoFlote;
        }
    }
}

// Ejercicio 3
template <typename T>
void ApoMinMax<T>::suprimirMax()
{
    assert(numNodos > 0);
    if (numNodos > 2){
        if (nodos[1] > nodos[2])
            nodo i = 1;
        else
            nodo i = 2;
        
        nodos[i] = nodos[numNodos-1];
        hundir(i);
    }
    numNodos--;
}

template <typename T>
void ApoMinMax<T>::hundir(nodo i)
{
    if (nodos[i] < nodos[hIzq(i)] || nodos[i] < nodos[hDer(i)]) {   // Está mal colocado con respecto a su hijo
        T eltoFlote = nodos[i];
        nodo indiceFlote;
        if (nodos[hIzq(i)] > nodos[hDer(i)])
            indiceFlote = hDer(i);
        else
            indiceFlote = hIzq(i);

        // HAY QUE TERMINAR ESTO
    }
}

// Ejercicio 4
template <typename T>
bool agenTernario (const Agen<T>& A)
{
    if (A.raiz() == Agen<T>::NODO_NULO)
        return true;
    else
        return agenTernario_rec (A.raiz(), A);
}

template <typename T>
bool agenTernario_rec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if (A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
        return true;
    else {
        if (comprobarTresHijos(n, A))
            return agenTernario_rec(A.hijoIzqdo(n), A) && agenTernario_rec(A.hermDrcho(A.hijoIzqdo(n)), A) && agenTernario_rec(A.hermDrcho(A.hermDrcho(hijoIzqdo(n))), A)
        else
            return false;
    }
}

template <typename T>
bool comprobarTresHijos(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if (A.hermDrcho(A.hijoIzqdo(n)) != Agen<T>::NODO_NULO && A.hermDrcho(A.hermDrcho(A.hijoIzqdo(n))) != Agen<T>::NODO_NULO && A.hermDrcho(A.hermDrcho(A.hermDrcho(A.hijoIzqdo(n)))) == Agen<T>::NODO_NULO)
        return true;
    else
        return false;
}

// Ejercicio 5
typedef enum Colores {B, N};

typedef struct {
    int x_sup, y_sup;
    int x_inf, y_inf;
    Colores c;
} coordenadas;

int ** figuraAsociada (const Agen<coordenadas>& A)
{
    int h = alturaNodoAgen(A.raiz(), A);
    Colores figura[h][h];
    rellenarMatriz(A.raiz(), A, figura);
    return figura;
}

void rellenarMatriz(typename Agen<coordenadas>::nodo n, const Agen<coordenadas>& A, Colores ** figura)
{
    if (A.hijoIzqdo(n) == Agen<coordenadas>::NODO_NULO) {
        for (int i = A.elemento(n).x_sup ; i <= A.elemento(n).x_inf ; i++)
            for (int j = A.elemento(n).y_sup ; j <= A.elemento(n).y_inf ; j++)
                figura[i][j] = A.elemento(n).c;
    }
    else {
        Agen<coordenadas>::nodo hijos = A.hijoIzqdo(n);
        while (hijos != Agen<coordenadas>::NODO_NULO) {
            rellenarMatriz(hijos, A, figura);
            hijos = A.hermDrcho(hijos);
        }
    }
}

