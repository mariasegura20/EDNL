#include "TAD Conocidos/agen.hpp"

// Ejercicio 1
template <typename T>
inline int gradoAgen (const Agen<T>& A)
{ return gradoAgen_rec(A.raiz(), A); }

template <typename T>
int gradoAgen_rec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if (n == Agen<T>::NODO_NULO)
        return 0;
    else {
        int grado = numHijos(n, A);
        Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO)
        {
            grado = max(grado, gradoAgen_rec(hijo, A));
            hijo = A.hermDrcho(hijo);
        }

        return grado;
    }
}

template <typename T>
int numHijos(typename Agen<T>::nodo n, const Agen<T>& A)
{
    int numHijos = 0;
    Agen<T>::nodo hijos = A.hijoIzqdo(n);

    while (hijos != Agen<T>::NODO_NULO) {
        numHijos++;
        hijos = A.hermDrcho(hijos);
    }

    return numHijos;
}

// Ejercicio 2
template <typename T>
int profundidadNodo(typename Agen<T>::nodo n, const Agen<T>& A)
{
    int prof = 0;
    Agen<T>::nodo padre = A.padre(n);
    while (padre != Agen<T>::NODO_NULO)
    {
        prof++;
        padre = A.padre(padre);
    }
    return padre;
}

// Ejercicio 3
template <typename T>
inline int desequilibrioAgen(const Agen<T>& A)
{ return alturaNodoAgen(A.raiz(), A) - ramaMasCorta(A.raiz(), A); }

template <typename T>
int alturaNodoAgen(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if (n == Agen<T>::NODO_NULO)
        return -1;
    else if (n == A.raiz() && A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
        return 0;
    else {
        int h = 0;
        Agen<T>::nodo hijos = A.hijoIzqdo(n);
        while (hijos != Agen<T>::NODO_NULO)
        {
            h = max (h, alturaNodoAgen(hijos, A));
            hijos = A.hermDrcho(hijos);
        }
        return 1 + h;
    }
}

template <typename T>
int ramaMasCorta(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if (n == Agen<T>::NODO_NULO)
        return -1;
    else if (n == A.raiz() && A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
        return 0;
    else {
        int minH = 10000;
        Agen<T>::nodo hijos = A.hijoIzqdo(n);
        while (hijos != Agen<T>::NODO_NULO)
        {
            minH = min(minH, ramaMasCorta(hijos, A));
            hijos = A.hermDrcho(hijos);
        }
        return 1 + minH;
    }
}

// Ejercicio 4
void buscarYpodar(Agen<int>& A, int x)
{
    Agen<int>::nodo nodoAPodar = buscar(A.raiz(), A, x);
    if (nodoAPodar != Agen<int>::NODO_NULO)
        podar(nodoAPodar, A);
}

Agen<int>::nodo buscar(typename Agen<int>::nodo n, const Agen<int>& A, int x)
{
    if (n == Agen<int>::NODO_NULO || A.elemento(n) == x)
        return n;
    else {
        Agen<int>::nodo hijos = A.hijoIzqdo(n);
        Agen<int>::nodo devolver = Agen<int>::NODO_NULO;
        while(hijos != Agen<int>::NODO_NULO && devolver == Agen<int>::NODO_NULO)
        {
            devolver = buscar(hijos, A, x);
            hijos = A.hermDrcho(hijos);
        }

        return devolver;
    }
}

void podar(typename Agen<int>::nodo n, Agen<int>& A)
{
    if (n == A.raiz())
        A.eliminarRaiz();
    else if (A.hijoIzqdo(n) == Agen<int>::NODO_NULO)
        A.eliminarHijoIzqdo(A.padre(n));
    else {
        Agen<int>::nodo hijos = A.hijoIzqdo(n);
        while (hijos != Agen<int>::NODO_NULO)
        {
            podar(hijos, A);
            hijos = A.hermDrcho(hijos);
        }
    }
}