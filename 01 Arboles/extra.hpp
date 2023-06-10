#include "TAD Conocidos/abin.hpp"
#include "TAD Conocidos/agen.hpp"

// Ejercicio 2
template <typename T>
double densidad (const Agen<T>& A)
{
    if (A.raiz() == Agen<T>::NODO_NULO)
        return 0;
    else {
        double grado = gradoAgen_rec(A.raiz(), A);
        double numHojas = numHojas_rec(A.raiz(), A);
        return grado/numHojas;
    }
}

template <typename T>
int gradoAgen_rec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if (A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
        return 0;
    else {
        int gradoMax = numHijos(n, A);
        Agen<T>::nodo hijos = A.hijoIzqdo(n);

        while (hijos != Agen<T>::NODO_NULO) {
            gradoMax = std::max(gradoMax, gradoAgen_rec(hijos, A));
            hijos = A.hermDrcho(hijos);
        }
        
        return gradoMax;
    }
}

template <typename T>
int numHijos(typename Agen<T>::nodo n, const Agen<T>& A)
{
    int numHijos = 0;
    Agen<T>::nodo hijos = A.hijoIzqdo(n);

    while (hijos != Agen<T>::NODO_NULO)
    {
        numHijos++;
        hijos = A.hermDrcho(hijos);
    }

    return numHijos;
}

template <typename T>
int numHojas_rec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if (A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
        return 1;
    else {
        int sum = 0;
        Agen<T>::nodo hijos = A.hijoIzqdo(n);
        while (hijos != Agen<T>::NODO_NULO)
        {
            sum += numHojas_rec(hijos, A);
            hijos = A.hermDrcho(hijos);
        }

        return sum;
    }
}

// Ejercicio 3
double porcentajeNodosMultiplos3 (const Agen<int>& A)
{
    if (A.raiz() == Agen<int>::NODO_NULO)
        return 100;
    else {
        double numNodosMultiplos3 = numNodosMultiplos3_rec(A.raiz(), A);
        double numNodosAgen = numNodosAgen_rec(A.raiz(), A);
        return numNodosMultiplos3/numNodosAgen * 100;
    }
}

int numNodosMultiplos3_rec (typename Agen<int>::nodo n, const Agen<int>& A)
{
    int numNodosMultiplos3 = 0;
    if (A.elemento(n) % 3 == 0)
        numNodosMultiplos3 = 1;
    
    Agen<int>::nodo hijos = A.hijoIzqdo(n);
    while (hijos != Agen<int>::NODO_NULO)
    {
        numNodosMultiplos3 += numNodosMultiplos3_rec(hijos, A);
        hijos = A.hermDrcho(hijos);
    }

    return numNodosMultiplos3;
}

int numNodosAgen_rec(typename Agen<int>::nodo n, const Agen<int>& A)
{
    if (n == Agen<int>::NODO_NULO)
        return 0;
    else {
        int numHijos = 0;
        Agen<int>::nodo hijos = A.hijoIzqdo(n);

        while (hijos != Agen<int>::NODO_NULO)
        {
            numHijos += numNodosAgen_rec(hijos, A);
            hijos = A.hermDrcho(hijos);
        }

        return 1 + numHijos;
    }
}

// Ejercicio 6
template <typename T>
int numNodos3nietos(const Abin<T>& A)
{

}

// Ejercicio 9
template <typename T>
inline int numNodosReflejos(const Abin<T>& A)
{ return numNodosReflejos_rec(A.raiz(), A); }

template <typename T>
int numNodosReflejos_rec(typename Abin<T>::nodo n, const Abin<T>& A)
{   
    if (n == Abin<T>::NODO_NULO)
        return 0;
    else {
        int nodoActualReflejo = 0;
        if (A.hijoIzq(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO) {
            if (AbinReflejo_rec(n, A))
                nodoActualReflejo = 1;
        }
        return nodoActualReflejo + numNodosReflejos_rec(A.hijoIzqdo(n), A) + numNodosReflejos_rec(A.hijoDrcho(n), A);
    }
}

template <typename T>
bool AbinReflejo_rec(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if (n == Abin<T>::NODO_NULO)
        return true;
    else if (n == A.raiz())
        return false;
    else {
        if (n == A.hijoIzqdo(A.padre(n))) {
            if (A.elemento(n) == A.elemento(A.hijoDrcho(A.padre(n))))
                return AbinReflejo_rec(A.hijoIzqdo(n), A) && AbinReflejo_rec(A.hijoDrcho(n), A);
            else
                return false;
        }
        else {
            if (A.elemento(n) == A.elemento(A.hijoIzqdo(A.padre(n))))
                return AbinReflejo_rec(A.hijoIzqdo(n), A) && AbinReflejo_rec(A.hijoDrcho(n), A);
            else
                return false;
        }
    }
}


