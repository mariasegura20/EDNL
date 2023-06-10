#include "TAD Conocidos/abin.hpp"

// Ejercicio 1
template <typename T>
int contarNodosAbin(const Abin<T>& A)
{
    if (A.arbolVacio())
        return 0;
    else
        return contarDescendientesNodo(A.raiz(), A);
}

template <typename T>
int contarDescendientesNodo(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if (n == Abin<T>::NODO_NULO)
        return 0;
    else
        return 1 + contarDescendientesNodo(A.hijoIzqdo(n), A) + contarDescendientesNodo(A.hijoDrcho(n), A);
}

// Ejercicio 2
template <typename T>
inline int alturaAbin (const Abin<T>& A)
{ return alturaNodo(A.raiz(), A); }

template <typename T>
int alturaNodo (typename Abin<T>::nodo n, const Abin<T>& A)
{
    if (n == Abin<T>::NODO_NULO)
        return -1;
    else 
        return 1 + max(alturaNodo(A.hijoIzqdo(n), A), alturaNodo(A.hijoDrcho(n), A));
}

// Ejercicio 3
template <typename T>
int profundidadNodo (typename Abin<T>::nodo n, const Abin<T>& A)
{
    int profundidad = 0;
    while (A.padre(n) != Abin<T>::NODO_NULO) {
        profundidad++;
        n = A.padre(n);
    }
    return profundidad;
}

// Ejercicio 6
template <typename T>
inline int desequilibrioAbin(const Abin<T>& A)
{ return alturaAbin(A) - ramaMasCorta_rec(A.raiz(), A); }

template <typename T>
int ramaMasCorta_rec(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if (n == Abin<T>::NODO_NULO)
        return -1;
    else 
        return 1 + min(ramaMasCorta_rec(A.hijoIzqdo(n), A), ramaMasCorta_rec(A.hijoDrcho(n), A));
}

// Ejercicio 7
template <typename T>
bool pseudocompletoAbin(const Abin<T>& A)
{
    int h = alturaAbin(A);
    if (h <= 0)
        return true;
    else
        return pseudocompletoAbin_rec(A.raiz(), A, h);
}

template <typename T>
bool pseudocompletoAbin_rec(typename Abin<T>::nodo n, const Abin<T>& A, int alturaAbin)
{
    if (profundidadNodo(n) == alturaAbin - 1) {
        if ((A.hijoIzqdo(n) != Abin<T>::NODO_NULO + A.hijoDrcho(n) != Abin<T>::NODO_NULO) == 1)
            return false;
        else
            return true;
    }
    else {
        bool Izq = true, Der = true;
        if (alturaNodo(A.hijoIzqdo(n), A) + profundidadNodo(A.hijoIzqdo(n), A) == alturaAbin)
            Izq = pseudocompletoAbin_rec(A.hijoIzqdo(n), A, alturaAbin);
        if (alturaNodo(A.hijoIzqdo(n), A) + profundidadNodo(A.hijoIzqdo(n), A) == alturaAbin)
            Der = pseudocompletoAbin_rec(A.hijoDrcho(n), A, alturaAbin);
        return Izq && Der;
    }
}