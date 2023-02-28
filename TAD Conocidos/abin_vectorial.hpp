// TAD Árbol Binario con implementación vectorial
#ifndef _ABIN_VECTORIAL_H_
#define _ABIN_VECTORIAL_H_
#include <cassert>
#include <iostream>

template <typename T> class AbinVec {
    public:
        typedef size_t nodo;
        static const nodo NODO_NULO;
        explicit AbinVec(size_t maxNodos);
        void insertarRaiz(const T& e);
        void insertarHijoIzqdo(nodo n, const T& e);
        void insertarHijoDrcho(nodo n, const T& e);
        void eliminarHijoIzqdo(nodo n);
        void eliminarHijoDrcho(nodo n);
        void eliminarRaiz();
        bool arbolVacio() const;
        const T& elemento(nodo n) const;
        T& elemento(nodo n);
        nodo raiz() const;
        nodo padre(nodo n) const;
        nodo hijoIzqdo(nodo n) const;
        nodo hijoDrcho(nodo n) const;
        AbinVec(const AbinVec<T>& A);
        AbinVec<T>& operator =(const AbinVec<T>& A);
        ~AbinVec();
    private:
        struct celda {
            T elto;
            nodo padre, hizq, hder;
        };
        celda *nodos;
        size_t maxNodos;
        size_t numNodos;
};

template <typename T>
const typename AbinVec<T>::nodo AbinVec<T>::NODO_NULO(SIZE_MAX);

template <typename T>
inline AbinVec<T>::AbinVec(size_t maxNodos) :
    nodos(new celda[maxNodos]), maxNodos(maxNodos), numNodos(0)
{}

template <typename T>
inline void AbinVec<T>::insertarRaiz(const T& e)
{
    assert(numNodos == 0);
    numNodos = 1;
    nodos[0].elto = e;
    nodos[0].padre = NODO_NULO;
    nodos[0].hizq = NODO_NULO;
    nodos[0].hder = NODO_NULO;
}

template <typename T>
inline void AbinVec<T>::insertarHijoIzqdo(nodo n, const T& e)
{
    assert(n >= 0 && n < numNodos);
    assert(nodos[n].hizq == NODO_NULO);
    assert(numNodos < maxNodos);
    nodos[n].hizq = numNodos;
    nodos[numNodos].elto = e;
    nodos[numNodos].padre = n;
    nodos[numNodos].hizq = NODO_NULO;
    nodos[numNodos].hder = NODO_NULO;
    ++numNodos;
}

template <typename T>
inline void AbinVec<T>::insertarHijoDrcho(nodo n, const T& e)
{
    assert(n >= 0 && n < numNodos);
    assert(nodos[n].hder == NODO_NULO);
    assert(numNodos < maxNodos);
    nodos[n].hder = numNodos;
    nodos[numNodos].elto = e;
    nodos[numNodos].padre = n;
    nodos[numNodos].hizq = NODO_NULO;
    nodos[numNodos].hder = NODO_NULO;
    ++numNodos;
}

template <typename T>
void AbinVec<T>::eliminarHijoIzqdo(nodo n)
{
    nodo hizqdo ;
    assert(n >= 0 && n < numNodos);
    hizqdo = nodos[n].hizq;
    assert(hizqdo != NODO_NULO);
    assert(nodos[hizqdo].hizq == NODO_NULO && nodos[hizqdo].hder == NODO_NULO);
    if (hizqdo != numNodos-1)
    {
        nodos[hizqdo] = nodos[numNodos-1];
        if (nodos[nodos[hizqdo].padre].hizq == numNodos-1)
            nodos[nodos[hizqdo].padre].hizq = hizqdo;
        else
            nodos[nodos[hizqdo].padre].hder = hizqdo;
        if (nodos[hizqdo].hizq != NODO_NULO)
            nodos[nodos[hizqdo].hizq].padre = hizqdo;
        if (nodos[hizqdo].hder != NODO_NULO)
            nodos[nodos[hizqdo].hder].padre = hizqdo;
    }
    nodos[n].hizq = NODO_NULO;
    --numNodos;
}

template <typename T>
void AbinVec<T>::eliminarHijoDrcho(nodo n)
{
    nodo hdrcho;
    assert(n >= 0 && n < numNodos);
    hdrcho = nodos[n].hder;
    assert(hdrcho != NODO_NULO);
    assert(nodos[hdrcho].hizq == NODO_NULO && nodos[hdrcho].hder == NODO_NULO);
    if (hdrcho != numNodos-1)
    {
        nodos[hdrcho] = nodos[numNodos-1];
        if (nodos[nodos[hdrcho].padre].hizq == numNodos-1)
            nodos[nodos[hdrcho].padre].hizq = hdrcho;
        else
            nodos[nodos[hdrcho].padre].hder = hdrcho;
        if (nodos[hdrcho].hizq != NODO_NULO)
            nodos[nodos[hdrcho].hizq].padre = hdrcho;
        if (nodos[hdrcho].hder != NODO_NULO)
            nodos[nodos[hdrcho].hder].padre = hdrcho;
    }
    nodos[n].hder = NODO_NULO;
    --numNodos;
}

template <typename T>
inline void AbinVec<T>::eliminarRaiz()
{
    assert(numNodos == 1);
    numNodos = 0;
}

template <typename T>
inline bool AbinVec<T>::arbolVacio() const
{ return (numNodos == 0); }

template <typename T>
inline const T& AbinVec<T>::elemento(nodo n) const
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].elto;
}

template <typename T>
inline T& AbinVec<T>::elemento(nodo n)
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].elto;
}

template <typename T>
inline typename AbinVec<T>::nodo AbinVec<T>::raiz() const
{ return (numNodos > 0) ? 0 : NODO_NULO; }

template <typename T> inline
typename AbinVec<T>::nodo AbinVec<T>::padre(nodo n) const
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].padre;
}

template <typename T> inline
typename AbinVec<T>::nodo AbinVec<T>::hijoIzqdo(nodo n) const
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].hizq;
}

template <typename T> inline
typename AbinVec<T>::nodo AbinVec<T>::hijoDrcho(nodo n) const
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].hder;
}

template <typename T>
AbinVec<T>::AbinVec(const AbinVec<T>& A) :
    nodos(new celda[A.maxNodos]), maxNodos(A.maxNodos), numNodos(A.numNodos)
{
    for (nodo n = 0; n <= numNodos-1; n++)
        nodos[n] = a.nodos[n];
}

template <typename T>
inline AbinVec<T>::~AbinVec()
{ delete[] nodos; }

template <typename T>
AbinVec<T>& AbinVec<T>::operator =(const AbinVec<T>& A)
{
    if (this != &A) {
        if (maxNodos != A.maxNodos) {
            delete[] nodos;
            maxNodos = A.maxNodos;
            nodos = new celda[maxNodos];
        }
        numNodos = A.numNodos;
        for (nodo n = 0; n <= numNodos-1; n++)
            nodos[n] = A.nodos[n];
    }
    return *this;
}
#endif // _ABIN_VECTORIAL_H_