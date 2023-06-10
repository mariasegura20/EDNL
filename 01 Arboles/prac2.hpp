#include "TAD Conocidos/abin.hpp"

// Ejercicio 1
template <typename T>
bool AbinSimilares(const Abin<T>& A, const Abin<T>& B)
{
    if (A.arbolVacio() || B.arbolVacio()) {
        if (A.arbolVacio() && B.arbolVacio())
            return true;
        else
            return false;
    }
    else
        return AbinSimilares_rec (A.raiz(), A, B.raiz(), B);
}

template <typename T>
bool AbinSimilares_rec (typename Abin<T>::nodo nA, const Abin<T>& A, typename Abin<T>::nodo nB, const Abin<T>& B)
{
    int numHijosA = A.hijoIzqdo(n) != Abin<T>::NODO_NULO + A.hijoDrcho(n) != Abin<T>::NODO_NULO;
    int numHijosB = B.hijoIzqdo(n) != Abin<T>::NODO_NULO + B.hijoDrcho(n) != Abin<T>::NODO_NULO;
    
    if (numHijosA != numHijosB)
        return false;
    else if (numHijosA == 0)
        return true;
    else if (numHijosA == 2)
        return AbinSimilares_rec(A.hijoIzqdo(nA), A, B.hijoIzqdo(nB), B) && AbinSimilares_rec(A.hijoDrcho(nA), A, B.hijoDrcho(nB), B);
    // Caso ambos tienen 1 hijo
    else if (A.hijoIzqdo(nA) == Abin<T>::NODO_NULO && B.hijoIzqdo(nB) == Abin<T>::NODO_NULO)
        return AbinSimilares_rec(A.hijoDrcho(nA), A, B.hijoDrcho(nB), B);
    else if (A.hijoDrcho(nA) == Abin<T>::NODO_NULO && B.hijoDrcho(nB) == Abin<T>::NODO_NULO)
        return AbinSimilares_rec(A.hijoIzqdo(nA), A, B.hijoIzqdo(nB), B);
    else
        return false;
}

// Ejercicio 2
template <typename T>
Abin<T> abinReflejado (const Abin<T>& A)
{
    Abin<T> Reflejado;
    if (!A.arbolVacio())
        Reflejado.insertarRaiz(A.elemento(A.raiz()));
        abinReflejado_rec(Reflejado.raiz(), Reflejado, A.raiz(), A);
    return Reflejado;
}

template <typename T>
void abinReflejado_rec(typename Abin<T>::nodo nReflejado, Abin<T>& Reflejado, typename Abin<T>::nodo nA, const Abin<T>& A)
{
    if (A.hijoIzq() != Abin<T>::NODO_NULO) {
        Reflejado.insertarHijoDrcho(nReflejado, A.elemento(A.hijoIzqdo(nA)));
        abinReflejado_rec(Reflejado.hijoDrcho(nReflejado), Reflejado, A.hijoIzqdo(nA), A);
    }
    if (A.hijoDrcho() != Abin<T>::NODO_NULO) {
        Reflejado.insertarHijoIzqdo(nReflejado, A.elemento(A.hijoDrcho(nA)));
        abinReflejado_rec(Reflejado.hijoIzqdo(nReflejado), Reflejado, A.hijoDrcho(nA), A);
    }
}

// Ejercicio 3
enum operadores {SUMA, RESTA, MULT, DIV};

template <typename T>
inline double AbinAritmetico (const Abin<T>& A)
{
    return AbinAritmetico_rec(A.raiz(), A);
}

template <typename T>
double AbinAritmetico_rec (typename Abin<T>::nodo n, const Abin<T>& A)
{
    if (A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO)
        return A.elemento(n);
    else {
        double op1 = AbinAritmetico_rec(A.hijoIzqdo(n), A);
        double op2 = AbinAritmetico_rec(A.hijoDrcho(n), A);

        switch (A.elemento(n))
        {
            case SUMA: return op1 + op2; break;
            case RESTA: return op1 - op2; break;
            case MULT: return op1 * op2; break;
            case DIV: return op1 / op2; break;
            default: return 0; break;
        }
    }
}