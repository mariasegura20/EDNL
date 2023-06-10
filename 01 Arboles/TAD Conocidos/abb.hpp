#ifndef ABB_H
#define ABB_H
#include <cassert>

template <typename T> class Abb {
    public:
        Abb();
        const Abb& buscar(const T& e) const;
        void insertar(const T& e);
        void eliminar(const T& e);
        bool vacio() const;
        const T& elemento() const;
        const Abb& izqdo() const;
        const Abb& drcho() const;
        Abb(const Abb& A);
        Abb& operator =(const Abb& A);
        ~Abb();
    private:
        struct arbol {
            T elto;
            Abb izq, der;
            arbol(const T& e): elto{e}, izq{}, der{} {}
        };
        arbol* r;
        T borrarMin();
};

template <typename T>
inline Abb<T>::Abb() : r{nullptr} {}

template <typename T>
inline bool Abb<T>::vacio() const
{ return (r == nullptr); }

template <typename T>
const Abb<T>& Abb<T>::buscar(const T& e) const
{
    if (r == nullptr)
        return *this;
    else if (e < r->elto)
        return r->izq.buscar(e);
    else if (r->elto < e)
        return r->der.buscar(e);
    else
        return *this;
}

template <typename T>
void Abb<T>::insertar(const T& e)
{
    if (r == nullptr)
        r = new arbol(e);
    else if (e < r->elto)
        r->izq.insertar(e);
    else if (r->elto < e)
        r->der.insertar(e);
}

template <typename T>
void Abb<T>::eliminar(const T& e)
{
    if (r != nullptr) {
        if (e < r->elto)
            r->izq.eliminar(e);
        else if (r->elto < e)
            r->der.eliminar(e);
        else
            if (!r->izq.r && !r->der.r) { // 1. Raíz es hoja.
                delete r;
                r = nullptr;
            }
            else if (!r->der.r) { // 2. Raíz sólo tiene hijo izqdo.
                arbol* a = r->izq.r;
                r->izq.r = nullptr;
                delete r;
                r = a;
            }
            else if (!r->izq.r) { // 3. Raíz sólo tiene hijo drcho.
                arbol* a = r->der.r;
                r->der.r = nullptr;
                delete r;
                r = a;
            }
            else // 4. Raíz tiene dos hijos
               r->elto = r->der.borrarMin();
    }
}

template <typename T>
T Abb<T>::borrarMin()
{
    if (r->izq.r == nullptr) {
        T e = r->elto;
        arbol* hd = r->der.r;
        r->der.r = nullptr;
        delete r;
        r = hd;
        return e;
    }
    else
        return r->izq.borrarMin();
}

template <typename T>
inline const T& Abb<T>::elemento() const
{
    assert(r != nullptr);
    return r->elto;
}

template <typename T>
inline const Abb<T>& Abb<T>::izqdo() const
{
    assert(r != nullptr);
    return r->izq;
}

template <typename T>
inline const Abb<T>& Abb<T>::drcho() const
{
    assert(r != nullptr);
    return r->der;
}

template <typename T>
inline Abb<T>::Abb(const Abb<T>& A): r{nullptr}
{
    if (A.r != nullptr)
    r = new arbol(*A.r);
}

template <typename T>
Abb<T>& Abb<T>::operator =(const Abb<T>& A)
{
    if (this != &A) {
        this->~Abb();
        if (A.r != nullptr)
        r = new arbol(*A.r);
    }
    return *this;
}

template <typename T>
Abb<T>::~Abb()
{
    if (r != nullptr) {
        delete r;
        r = nullptr;
    }
}
#endif // ABB_H