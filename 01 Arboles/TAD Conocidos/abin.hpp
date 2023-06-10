// TAD Árbol Binario con implementación mediante celdas enlazadas
#ifndef _ABIN_ENLAZADA_H_
#define _ABIN_ENLAZADA_H_
#include <cassert>

template <typename T> class Abin {
    struct celda;
    public:
        typedef celda* nodo;
        static const nodo NODO_NULO;
        Abin();
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
        Abin(const Abin<T>& a);
        Abin<T>& operator =(const Abin<T>& A);
        ~Abin();
    private: 
        struct celda {
            T elto;
            nodo padre, hizq, hder;
            celda(const T& e, nodo p = NODO_NULO): elto(e),
            padre(p), hizq(NODO_NULO), hder(NODO_NULO) {}
        };
        nodo r;
        void destruirNodos(nodo& n);
        nodo copiar(nodo n);
};

template <typename T>
const typename Abin<T>::nodo Abin<T>::NODO_NULO(nullptr);

template <typename T>
inline Abin<T>::Abin() : r(NODO_NULO) {}

template <typename T>
inline void Abin<T>::insertarRaiz(const T& e)
{
    assert(r == NODO_NULO);
    r = new celda(e);
}

template <typename T>
inline void Abin<T>::insertarHijoIzqdo(nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n->hizq == NODO_NULO);
    n->hizq = new celda(e, n);
}

template <typename T>
inline void Abin<T>::insertarHijoDrcho(nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n->hder == NODO_NULO);
    n->hder = new celda(e, n);
}

template <typename T>
inline void Abin<T>::eliminarHijoIzqdo(nodo n)
{
    assert(n != NODO_NULO);
    assert(n->hizq != NODO_NULO);
    assert(n->hizq->hizq == NODO_NULO && n->hizq->hder == NODO_NULO);
    delete n->hizq;
    n->hizq = NODO_NULO;
}

template <typename T>
inline void Abin<T>::eliminarHijoDrcho(nodo n)
{
    assert(n != NODO_NULO);
    assert(n->hder != NODO_NULO);
    assert(n->hder->hizq == NODO_NULO && n->hder->hder == NODO_NULO);
    delete n->hder;
    n->hder = NODO_NULO;
}

template <typename T>
inline void Abin<T>::eliminarRaiz()
{
    assert(r != NODO_NULO);
    assert(r->hizq == NODO_NULO && r->hder == NODO_NULO);
    delete r;
    r = NODO_NULO;
}

template <typename T> inline bool Abin<T>::arbolVacio() const
{ return (r == NODO_NULO); }

template <typename T>
inline const T& Abin<T>::elemento(nodo n) const
{
    assert(n != NODO_NULO);
    return n->elto;
}

template <typename T>
inline T& Abin<T>::elemento(nodo n)
{
    assert(n != NODO_NULO);
    return n->elto;
}

template <typename T>
inline typename Abin<T>::nodo Abin<T>::raiz() const
{ return r; }

template <typename T> inline
typename Abin<T>::nodo Abin<T>::padre(nodo n) const
{
    assert(n != NODO_NULO);
    return n->padre;
}

template <typename T> inline
typename Abin<T>::nodo Abin<T>::hijoIzqdo(nodo n) const
{
    assert(n != NODO_NULO);
    return n->hizq;
}

template <typename T> inline
typename Abin<T>::nodo Abin<T>::hijoDrcho(nodo n) const
{
    assert(n != NODO_NULO);
    return n->hder;
}

template <typename T>
inline Abin<T>::Abin(const Abin<T>& A)
{
    r = copiar(A.r);
}

template <typename T>
Abin<T>& Abin<T>::operator =(const Abin<T>& A)
{
    if (this != &A) {
        this->~Abin();
        r = copiar(A.r);
    }
    return *this;
}
template <typename T>
inline Abin<T>::~Abin()
{
    destruirNodos(r);
}

template <typename T>
void Abin<T>::destruirNodos(nodo& n)
{
    if (n != NODO_NULO) {
        destruirNodos(n->hizq);
        destruirNodos(n->hder);
        delete n;
        n = NODO_NULO;
    }
}

template <typename T>
typename Abin<T>::nodo Abin<T>::copiar(nodo n)
{
    nodo m = NODO_NULO;
    if (n != NODO_NULO) {
        m = new celda(n->elto);
        m->hizq = copiar(n->hizq);
        if (m->hizq != NODO_NULO)
            m->hizq->padre = m;
        m->hder = copiar(n->hder);
        if (m->hder != NODO_NULO)
            m->hder->padre = m;
    }
    return m;
}
#endif // _ABIN_ENLAZADA_H_