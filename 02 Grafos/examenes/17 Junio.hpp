#include "../algoritmos/alg_grafoPMC.h"

#include <iostream>

template <typename tCoste>
matriz<typename GrafoP<tCoste>::vertice> SinPasarPorLaCapital (const GrafoP<tCoste>& G, typename GrafoP<tCoste>::vertice capital)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t n = G.numVert();
    GrafoP<tCoste> actual(G);

    for (vertice i = 0 ; i < n ; i++)
        actual[i][capital] = actual[capital][i] = GrafoP<tCoste>::INFINITO;
    
    // Para habitantes de otras ciudades
    matriz<vertice> camino(n);
    Floyd(actual, camino);

    // Para habitantes de la capital
    vector<vertice> origen(n), destino(n);
    Dijkstra(G,capital, origen);
    DijkstraInv(G,capital,destino);

    for (vertice i = 0 ; i < n ; i++)
    {
        camino[capital][i] = origen[i];
        camino[i][capital] = destino[i];
    }

    return camino;
}