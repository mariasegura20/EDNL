#include "../algoritmos/alg_GrafoPMC.h"

#include <iostream>
#include <cmath>

struct casilla {
    unsigned f, c, h;
};

typedef typename GrafoP<size_t>::vertice vertice;

vertice casilla_to_vertice (casilla c, unsigned N)
{
    vertice v = c.f * N + c.c + c.h*N*N;
    return v;
}

casilla vertice_to_casilla (vertice v, unsigned N)
{
    casilla c;
    c.f = (v / N) % N;
    c.c = v % N;
    c.h = v / (N*N);

    return c;
}

bool adyacentes (casilla c1, casilla c2)
{ return (abs(c1.f - c2.f) + abs(c1.c - c2.c) + abs(c1.h - c2.h) == 1); }

size_t laberinto (unsigned N, vector<casilla> piedras, casilla entrada, casilla salida)
{
    // Crear grafo
    GrafoP<size_t> G(N*N*N);
    for (vertice i = 0 ; i < N*N*N ; i++)
        for (vertice j = i ; j < N*N*N ; j++)
            if (adyacentes(vertice_to_casilla(i,N), vertice_to_casilla(j, N)))
                G[i][j] = G[j][i] = 1;
    
    // Piedras
    for (size_t i = 0 ; i < piedras.size() ; i++)
    {
        vertice v = casilla_to_vertice(piedras[i], N);
        for (vertice j = 0 ; j < N*N*N ; j++)
            G[j][v] = G[v][j] = GrafoP<size_t>::INFINITO;
    }

    // Calcular coste/longitud del camino más corto
    vector<vertice> P(N*N*N);
    vector<size_t> d(N*N*N);
    d = Dijkstra(G, casilla_to_vertice(entrada, N), P);

    return d[casilla_to_vertice(salida, N)];
}