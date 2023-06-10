#include "TAD Conocidos/abb.hpp"
#include <vector>

// Ejercicio 1
template <typename T>
inline void poda(Abb<T>& A, const T& e)
{ A.buscar(e).~Abb(); }

// Ejercicio 2
template <typename T>
void equilibrarAbb(Abb<T>& A)
{
    std::vector<T> elementos;
    rellenarVectorInorden(A, elementos);
    Abb<T> equilibrado;
    crearAbbEquilibrado(equilibrado, elementos, 0, elementos.size() - 1);
    A = equilibrado;
}

template<typename T>
void rellenarVectorInorden(Abb<T>& A, std::vector<T>& elementos)
{
    if (!A.vacio())
    {
        rellenarVectorInorden(A.izqdo(), elementos);
        elementos.push_back(A.elemento());
        rellenarVectorInorden(A.drcho(), elementos);
    }
}

template <typename T>
void crearAbbEquilibrado (Abb<T>& A, std::vector<T>& elementos, int inicio, int fin)
{
    if (inicio <= fin)
    {
        int mediana = (inicio + fin) / 2;
        A.insertar(elementos[mediana]);
        crearAbbEquilibrado(A, elementos, inicio, mediana-1);
        crearAbbEquilibrado(A, elementos, mediana+1, fin);
    }
}

// Ejercicio 3

typedef Abb<int> Conjunto;

Conjunto unionAbb(const Conjunto& A, const Conjunto& B)
{
    Conjunto Union(A);
    if (!B.vacio())
        unionAbb_rec(Union, B);
    equilibrarAbb(Union);
    return Union;
}

void unionAbb_rec (Conjunto& Union, const Conjunto& B)
{
    if (!B.izqdo().vacio())
        unionAbb_rec(Union, B.izqdo());
    if (!B.drcho().vacio())
        unionAbb_rec(Union, B.drcho());
    Union.insertar(B.elemento());
}

// Ejercicio 4
Conjunto interseccionAbb(const Conjunto& A, const Conjunto& B)
{
    Conjunto Interseccion;
    if (!A.vacio() && !B.vacio())
        interseccionAbb_rec(Interseccion, A, B);
    equilibrarAbb(Interseccion);
    return Interseccion;
}

void interseccionAbb_rec (Conjunto& Interseccion, Conjunto A, Conjunto B)
{
    if (!B.buscar(A.elemento()).vacio())
        Interseccion.insertar(A.elemento());
    if (!A.izqdo().vacio())
        interseccionAbb_rec(Interseccion, A.izqdo(), B);
    if (!A.drcho().vacio())
        interseccionAbb_rec(Interseccion, A.drcho(), B);
}

// Ejercicio 5
inline Conjunto operador(const Conjunto& A, const Conjunto& B)
{ return diferenciaAbb(unionAbb(A,B), interseccionAbb(A,B)); }

inline bool pertenece(const Conjunto& A, int elto)
{ return (!A.buscar(elto).vacio()); }

Conjunto diferenciaAbb(const Conjunto& A, const Conjunto& B)
{
    Conjunto Diferencia(A);
    if (!B.vacio())
        diferenciaAbb_rec(Diferencia, B);
    equilibrarAbb(Diferencia);
    return Diferencia;
}

void diferenciaAbb_rec (Conjunto& Diferencia, const Conjunto& B)
{
    if (pertenece(Diferencia, B.elemento()))
        Diferencia.eliminar(B.elemento());
    if (!B.izqdo().vacio()) {
        diferenciaAbb_rec(Diferencia, B.izqdo());
    }
    if (!B.drcho().vacio()) {
        diferenciaAbb_rec(Diferencia, B.drcho());
    }
}