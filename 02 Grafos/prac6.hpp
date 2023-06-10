#include "algoritmos/alg_grafoPMC.h"
#include "algoritmos/alg_grafo_E-S.h"

#include <iostream>
#include <vector>

using namespace std;

// Ejercicio 1 en algoritmos/alg_grafoPMC.h

// Ejercicio 2
template <typename tCoste>
tCoste longitudDiametro(const GrafoP<tCoste>& G)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t n = G.numVert();
    
    matriz<vertice> P;
    matriz<tCoste> f = Floyd(G, P);

    tCoste max = 0;

    for (vertice i = 0 ; i < n ; i++)
        for (vertice j = 0 ; j < n ; j++)
            if (max < f[i][j] && f[i][j] != GrafoP<tCoste>::INFINITO)
                max = f[i][j];
    
    return max;
}

// Ejercicio 3
template <typename tCoste>
matriz<tCoste> FloydAciclico(const GrafoP<tCoste>& G, matriz<typename GrafoP<tCoste>::vertice>& P)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t n = G.numVert();
    matriz<tCoste> A(n);

    P = matriz<vertice>(n);
    for (vertice i = 0; i < n; i++) {
        A[i] = G[i];
        A[i][i] = GrafoP<tCoste>::INFINITO;
        P[i] = vector<vertice>(n, i);
    }

    for (vertice k = 0; k < n; k++)
        for (vertice i = 0; i < n; i++)
            for (vertice j = 0; j < n; j++) {
                tCoste ikj = suma(A[i][k], A[k][j]);
                if (ikj < A[i][j]) {
                    A[i][j] = ikj;
                    P[i][j] = k;
                }
            }

    return A;
}

template <typename tCoste>
bool aciclico (const GrafoP<tCoste>& G)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t n = G.numVert();
    
    matriz<vertice> P;
    matriz<tCoste> f = FloydAciclico(G,P);

    bool aciclico = true;

    for (vertice i = 0 ; i < n && aciclico; i++)
        if (f[i][i] != GrafoP<tCoste>::INFINITO)
            aciclico = false;

    return aciclico;
}

// Ejercicio 4
template <typename tCoste>
struct carretera {
    typename GrafoP<tCoste>::vertice origen, destino;
};

template <typename tCoste>
void Zuelandia (GrafoP<tCoste>& G, vector<typename GrafoP<tCoste>::vertice> ciudades, vector<carretera<tCoste>> carreteras, typename GrafoP<tCoste>::vertice capital)
{
    const size_t n = G.numVert();
    const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
    typedef typename GrafoP<tCoste>::vertice vertice;

    // Ciudades tomadas
    for (size_t it = 0 ; it < ciudades.size() ; it++)
    {
        vertice c = ciudades[it];
        for (vertice i = 0 ; i < n ; i++)
        {
            G[i][c] = INFINITO;
            G[c][i] = INFINITO;
        }
    }

    // Carreteras tomadas
    for (size_t c = 0 ; c < carreteras.size() ; c++)
        G[carreteras[c].origen][carreteras[c].destino] = INFINITO;

    // Sin pasar por la capital
    /*matriz<vertice> P;
    matriz<tCoste> f = Floyd(G,P);
    for (vertice i = 0 ; i < n ; i++)
        for (vertice j = 0 ; j < n ; j++)
            G[i][j] = f[i][j];*/

    // Pasando por la capital
    vector<vertice> P, PInv;
    vector<tCoste> d = Dijkstra(G, capital, P);
    vector<tCoste> dInv = DijkstraInv(G, capital, PInv);
    
    for (vertice i = 0 ; i < n ; i++)
        for (vertice j = 0 ; j < n ; j++)
            G[i][j] = suma(dInv[i], d[j]);

    cout << G << endl;
}