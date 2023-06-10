#include "algoritmos/alg_grafoPMC.h"
#include "algoritmos/alg_grafo_E-S.h"

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Ejercicio 1
template <typename tCoste>
struct viaje {
    typename GrafoP<tCoste>::vertice origen, destino;
    tCoste coste;
};

template <typename tCoste>
viaje<tCoste> viajeMasCaro (const GrafoP<tCoste>& G)
{
    typedef typename GrafoP<tCoste>::vertice vertice;

    matriz<vertice> P;
    matriz<tCoste> f = FloydMax(G,P);

    viaje<tCoste> v;
    v.origen = v.destino = v.coste = 0;

    for (vertice i = 0 ; i < G.numVert() ; i++)
    {
        for (vertice j = 0 ; j < G.numVert() ; j++)
        {
            if (f[i][j] > v.coste && f[i][j] != GrafoP<tCoste>::INFINITO)
            {
                v.origen = i;
                v.destino = j;
                v.coste = f[i][j];
            }
        }
    }

    return v;
}

// Ejercicio 2
struct casilla {
    size_t f, c;
};

struct pared {
    casilla a, b;
};

Lista<casilla> laberinto (size_t N, vector<pared> paredes, casilla entrada, casilla salida)
{
    // Construir el grafo
    const size_t n = N*N;
    GrafoP<size_t> G(n);
    
    typedef typename GrafoP<size_t>::vertice vertice;
    const size_t INFINITO = GrafoP<size_t>::INFINITO;
    
    // Casillas adyacentes
    for(vertice i = 0 ; i < n ; i++)
    {
        for (vertice j = 0 ; j < n ; j++)
        {
            if (adyacentes(vertice_to_casilla(i, N), vertice_to_casilla(j, N)))
                G[i][j] = G[j][i] = 1;
            else 
                G[i][j] = G[j][i] = INFINITO;
        }
    }

    // Paredes
    for (size_t i = 0 ; i < paredes.size() ; i++)
    {
        vertice a = casilla_to_vertice(paredes[i].a, N);
        vertice b = casilla_to_vertice(paredes[i].b, N);
        G[a][b] = INFINITO;
        G[b][a] = INFINITO;
    }

    // Camino más corto
    vertice e = casilla_to_vertice(entrada, N);
    vertice s = casilla_to_vertice(salida, N);
    
    vector<vertice> P(n);
    vector<size_t> d(n);
    d = Dijkstra(G, e, P);

    Lista<casilla> cRuta;
    GrafoP<size_t>::tCamino ruta = camino<vertice>(e, s, P);
    for (Lista<size_t>::posicion v = ruta.primera() ; v != ruta.fin() ; v = ruta.siguiente(v))
        cRuta.insertar(vertice_to_casilla(ruta.elemento(v), N), cRuta.fin());
    
    return cRuta;
}

bool adyacentes (casilla a, casilla b)
{ return ((abs(a.c - b.c) + abs(a.f - b.f)) == 1); }

GrafoP<size_t>::vertice casilla_to_vertice (casilla c, size_t N)
{
    typename GrafoP<size_t>::vertice v = c.f * N + c.c;
    return v;
}

casilla vertice_to_casilla (GrafoP<size_t>::vertice v, size_t N)
{
    casilla c;
    c.c = v % N;
    c.f = v / N;
    return c;
}

// Ejercicio 3
struct distribucion{
    vector<unsigned> udsXciudad;
    double costeMinTotal;
    distribucion(size_t n) : udsXciudad(n), costeMinTotal(0) {}
};

template <typename tCoste>
distribucion distribucionStock (const GrafoP<tCoste>& G, vector<unsigned> capacidad, vector<double> subvencion, typename GrafoP<tCoste>::vertice centro, unsigned cantidad)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
    const size_t n = G.numVert();

    GrafoP<tCoste> SA = G;  // SA == Subvenciones aplicadas

    for (vertice i = 0 ; i < n ; i++)
        for (vertice j = 0 ; j < n ; j++)
            if (SA[i][j] != INFINITO)
                SA[i][j] *= (1 - subvencion[j]/100);
    
    vector<tCoste> dSA(n);  // dSA == disjktra de SA
    vector<vertice> P(n);    
    dSA = Dijkstra(SA, centro, P);
    distribucion d(n);

    while (cantidad > 0)
    {
        unsigned costeMin = INFINITO;
        vertice ciudadMin;
        for(vertice i = 0 ; i < n ; i++)
        {
            if (i != centro && dSA[i] < costeMin)
            {
                costeMin = dSA[i];
                ciudadMin = i;
            }
        }

        unsigned cant;
        if (capacidad[ciudadMin] < cantidad)
        {
            cant = capacidad[ciudadMin];
            dSA[ciudadMin] = INFINITO;
        }
        else
            cant = cantidad;

        cantidad -= cant;
        d.costeMinTotal += costeMin * cant;
        d.udsXciudad[ciudadMin] = cant;
    }

    return d;
}
