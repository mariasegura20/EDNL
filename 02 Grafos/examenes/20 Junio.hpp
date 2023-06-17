#include "../algoritmos/alg_grafoPMC.h"

#include <iostream>

template <typename tCoste>
int Pedido(typename GrafoP<tCoste>::vertice i)
{
    vector<int> v(5);
    v[0] = 0;
    v[1] = 6;
    v[2] = 7;
    v[3] = 5;
    v[4] = 6;

    return v[i];
}

template <typename tCoste>
tCoste reparto (const GrafoP<tCoste>& G, unsigned capacidad, typename GrafoP<tCoste>::vertice almacen)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t n = G.numVert();

    size_t contVisitas = 0;
    vector<bool> visitados(n);
    for(size_t i = 0 ; i < n ; i++)
        visitados[i] = false;
    
    vertice actual = almacen;
    unsigned capActual = capacidad;

    visitados[actual] = true;
    tCoste total = 0;

    matriz<vertice> P(n);
    matriz<tCoste> f(n);
    f = Floyd(G,P);
    
    while (contVisitas < n-1)
    {
        // Averiguar visita más cercana
        vertice prox;
        tCoste minDist = GrafoP<tCoste>::INFINITO;
        for (vertice i = 0 ; i < n ; i++)
        {
            if (f[actual][i] < minDist && visitados[i] == false) {
                prox = i;
                minDist = f[actual][i];
            }
        }

        // Realizar la visita
        if (Pedido<tCoste>(prox) <= capActual) {
            total += minDist;
        }
        else {
            total += minDist;
            total += f[prox][almacen];
            capActual = capacidad;
            total += f[almacen][prox];
        }

        capActual -= Pedido<tCoste>(prox);
        actual = prox;
        visitados[actual] = true;
        contVisitas++;
    }

    return total;
}