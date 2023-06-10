#ifndef AGEN_LIS_H
#define AGEN_LIS_H
#include <cassert>

using namespace std;

template <typename T> class Agen {
    struct celda;
    public:
        typedef celda* nodo;
        static const nodo NODO_NULO;
        Agen();
        void insertarRaiz(const T& e);
        void insertarHijoIzqdo(nodo n, const T& e);
        void insertarHermDrcho(nodo n, const T& e);
        void eliminarHijoIzqdo(nodo n);
        void eliminarHermDrcho(nodo n);
        void eliminarRaiz();
        const T& elemento(nodo n) const;
        T& elemento(nodo n);
        nodo raiz() const;
        nodo padre(nodo n) const;
        nodo hijoIzqdo(nodo n) const;
        nodo hermDrcho(nodo n) const;
        Agen(const Agen<T>& a);
        Agen<T>& operator =(const Agen<T>& a);
        ~Agen();
    private:
        struct celda {
            T elto;
            nodo padre, hizq, heder;
            celda(const T& e, nodo p = NODO_NULO): elto(e),
            padre(p), hizq(NODO_NULO), heder(NODO_NULO) {}
        };
        nodo r;
        void destruirNodos(nodo& n);
        nodo copiar(nodo n);
};

template <typename T>
const typename Agen<T>::nodo Agen<T>::NODO_NULO(nullptr);

template <typename T>
inline Agen<T>::Agen() : r(NODO_NULO) {}

template <typename T>
inline void Agen<T>::insertarRaiz(const T& e)
{
    assert(r == NODO_NULO); 
    r = new celda(e);
}

template <typename T>
inline void Agen<T>::insertarHijoIzqdo(nodo n, const T& e)
{
    assert(n != NODO_NULO);
    nodo hizqdo = n->hizq;
    n->hizq = new celda(e, n);
    n->hizq->heder = hizqdo;
}

template <typename T>
inline void Agen<T>::insertarHermDrcho(nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n != r); 
    nodo hedrcho = n->heder; 
    n->heder = new celda(e, n->padre);
    n->heder->heder = hedrcho; 
}

template <typename T>
inline void Agen<T>::eliminarHijoIzqdo(nodo n)
{
    nodo hizqdo;
    assert(n != NODO_NULO);
    hizqdo = n->hizq;
    assert(hizqdo != NODO_NULO);
    assert(hizqdo->hizq == NODO_NULO);
    n->hizq = hizqdo->heder;
    delete hizqdo;
}

template <typename T>
inline void Agen<T>::eliminarHermDrcho(nodo n)
{
    nodo hedrcho;
    assert(n != NODO_NULO);
    hedrcho = n->heder;
    assert(hedrcho != NODO_NULO);
    assert(hedrcho->hizq == NODO_NULO);
    n->heder = hedrcho->heder;
    delete hedrcho;
}
template <typename T>
inline void Agen<T>::eliminarRaiz()
{
    assert(r != NODO_NULO);
    assert(r->hizq == NODO_NULO);
    delete(r);
    r = NODO_NULO;
}

template <typename T>
inline const T& Agen<T>::elemento(nodo n) const
{
    assert(n != NODO_NULO);
    return n->elto;
}

template <typename T>
inline T& Agen<T>::elemento(nodo n)
{
    assert(n != NODO_NULO);
    return n->elto;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::raiz() const
{
    return r;
}

template <typename T> inline
typename Agen<T>::nodo Agen<T>::padre(nodo n) const
{
    assert(n != NODO_NULO);
    return n->padre;
}

template <typename T> inline
typename Agen<T>::nodo Agen<T>::hijoIzqdo(nodo n) const
{
    assert(n != NODO_NULO);
    return n->hizq;
}

template <typename T> inline
typename Agen<T>::nodo Agen<T>::hermDrcho(nodo n) const
{
    assert(n != NODO_NULO);
    return n->heder;
}

template <typename T>
inline Agen<T>::Agen(const Agen<T>& A)
{
    r = copiar(A.r);
}

template <typename T>
Agen<T>& Agen<T>::operator =(const Agen<T>& A)
{
    if (this != &A)
    {
        destruirNodos(r);
        r = copiar(A.r);
    }
    return *this;
}

template <typename T>
inline Agen<T>::~Agen()
{
    destruirNodos(r);
}

template <typename T>
void Agen<T>::destruirNodos(nodo& n)
{
    if (n != NODO_NULO)
    {
        if (n->hizq != NODO_NULO)
        {
            nodo hedrcho = n->hizq->heder;
            while (hedrcho != NODO_NULO)
            {
                n->hizq->heder = hedrcho->heder;
                destruirNodos(hedrcho);
                hedrcho = n->hizq->heder;
            }
            destruirNodos(n->hizq);
        }
        delete(n);
        n = NODO_NULO;
    }
}

template <typename T>
typename Agen<T>::nodo Agen<T>::copiar(nodo n)
{
    nodo m = NODO_NULO;
    if (n != NODO_NULO) {
        m = new celda(n->elto);
        if (n->hizq != NODO_NULO) {
            m->hizq = copiar(n->hizq);
            m->hizq->padre = m;
            nodo hijo = m->hizq;
            nodo hedrcho = n->hizq->heder;
            while (hedrcho != NODO_NULO) {
                hijo = hijo->heder = copiar(hedrcho);
                hijo->padre = m;
                hedrcho = hedrcho->heder;
            }
        }
    }
    return m;
}

#endif // AGEN_H