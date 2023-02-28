// TAD Árbol Binario con implementación mediante un vector de posiciones relativas
#ifndef _ABIN_POSICIONES_H_
#define _ABIN_POSICIONES_H_
#include <cassert>
#include <iostream>

template <typename T> class AbinPos {
    public:
        typedef size_t nodo;
        static const nodo NODO_NULO;
        explicit AbinPos(size_t maxNodos, const T& e_nulo = T());
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
        AbinPos(const AbinPos<T>& a);
        AbinPos<T>& operator =(const AbinPos<T>& a);
        ~AbinPos();
    private:
        T* nodos;
        size_t maxNodos;
        T ELTO_NULO;
};

template <typename T>
const typename AbinPos<T>::nodo AbinPos<T>::NODO_NULO(SIZE_MAX);

template <typename T>
AbinPos<T>::AbinPos(size_t maxNodos, const T& e_nulo) :
    nodos(new T[maxNodos]), maxNodos(maxNodos), ELTO_NULO(e_nulo)
{
    for (nodo n = 0; n <= maxNodos-1; n++)
        nodos[n] = ELTO_NULO;
}

template <typename T>
inline void AbinPos<T>::insertarRaiz(const T& e)
{
    assert(nodos[0] == ELTO_NULO);
    nodos[0] = e;
}

template <typename T> inline
void AbinPos<T>::insertarHijoIzqdo(nodo n,const T& e)
{
    assert(n >= 0 && n <= maxNodos-1);
    assert(nodos[n] != ELTO_NULO);
    assert(2*n+1 < maxNodos);
    assert(nodos[2*n+1] == ELTO_NULO);
    nodos[2*n+1] = e;
}

template <typename T> inline
void AbinPos<T>::insertarHijoDrcho(nodo n,const T& e)
{
    assert(n >= 0 && n < maxNodos-1);
    assert(nodos[n] != ELTO_NULO);
    assert(2*n+2 < maxNodos);
    assert(nodos[2*n+2] == ELTO_NULO);
    nodos[2*n+2] = e;
}

template <typename T> inline
void AbinPos<T>::eliminarHijoIzqdo(nodo n)
{
    assert(n >= 0 && n <= maxNodos-1);
    assert(nodos[n] != ELTO_NULO);
    assert(2*n+1 < maxNodos);
    assert(nodos[2*n+1] != ELTO_NULO);
    if (4*n+4 < maxNodos)
        assert(nodos[4*n+3] == ELTO_NULO && nodos[4*n+4] == ELTO_NULO);
    else if (4*n+3 < maxNodos)
        assert(nodos[4*n+3] == ELTO_NULO);
    nodos[2*n+1] = ELTO_NULO;
}

template <typename T> inline
void AbinPos<T>::eliminarHijoDrcho(nodo n)
{
    assert(n >= 0 && n <= maxNodos-1);
    assert(nodos[n] != ELTO_NULO);
    assert(2*n+2 < maxNodos);
    assert(nodos[2*n+2] != ELTO_NULO); 
    if (4*n+6 < maxNodos)
        assert(nodos[4*n+5] == ELTO_NULO && nodos[4*n+6] == ELTO_NULO);
    else if (4*n+5 < maxNodos)
        assert(nodos[4*n+5] == ELTO_NULO);
    nodos[2*n+2] = ELTO_NULO;
}

template <typename T>
inline void AbinPos<T>::eliminarRaiz()
{
    assert(nodos[0] != ELTO_NULO);
    assert(nodos[1] == ELTO_NULO && nodos[2] == ELTO_NULO);
    nodos[0] = ELTO_NULO;
}

template <typename T>
inline bool AbinPos<T>::arbolVacio() const
{ return (nodos[0] == ELTO_NULO); }

template <typename T>
inline const T& AbinPos<T>::elemento(nodo n) const
{
    assert(n >= 0 && n <= maxNodos-1);
    assert(nodos[n] != ELTO_NULO);
    return nodos[n];
}

template <typename T>
inline T& AbinPos<T>::elemento(nodo n)
{
    assert(n >= 0 && n <= maxNodos-1);
    assert(nodos[n] != ELTO_NULO);
    return nodos[n];
}

template <typename T>
inline typename AbinPos<T>::nodo AbinPos<T>::raiz() const
{ return (nodos[0] == ELTO_NULO) ? NODO_NULO : 0; }

template <typename T> inline
typename AbinPos<T>::nodo AbinPos<T>::padre(nodo n) const
{
    assert(n >= 0 && n <= maxNodos-1);
    assert(nodos[n] != ELTO_NULO);
    return (n == 0) ? NODO_NULO : (n-1)/2;
}

template <typename T> inline
typename AbinPos<T>::nodo AbinPos<T>::hijoIzqdo(nodo n) const
{
    assert(n >= 0 && n <= maxNodos-1);
    assert(nodos[n] != ELTO_NULO); 
    return (2*n+1 >= maxNodos || nodos[2*n+1] == ELTO_NULO) ?
    NODO_NULO : 2*n+1;
}

template <typename T> inline
typename AbinPos<T>::nodo AbinPos<T>::hijoDrcho(nodo n) const
{
    assert(n >= 0 && n <= maxNodos-1);
    assert(nodos[n] != ELTO_NULO);
    return (2*n+2 >= maxNodos || nodos[2*n+2] == ELTO_NULO) ? 
    NODO_NULO : 2*n+2;
}

template <typename T>
AbinPos<T>::AbinPos(const AbinPos<T>& A) :
    nodos(new T[A.maxNodos]), maxNodos(A.maxNodos), ELTO_NULO(A.ELTO_NULO)
{
    for (nodo n = 0; n <= maxNodos-1; n++)
        nodos[n] = A.nodos[n];
}

template <typename T>
inline AbinPos<T>::~AbinPos()
{ delete[] nodos; }

template <typename T>
AbinPos<T>& AbinPos<T>::operator =(const AbinPos<T>& A)
{
    if (this != &A) {
        if (maxNodos != A.maxNodos) {
            delete[] nodos;
            maxNodos = A.maxNodos;
            nodos = new T[maxNodos];
        }
        ELTO_NULO = A.ELTO_NULO;
        for (nodo n = 0; n <= maxNodos-1; n++)
            nodos[n] = A.nodos[n];
    }
    return *this;
}

#endif // _ABIN_POSICIONES_H_