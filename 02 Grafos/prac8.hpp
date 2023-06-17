#include "algoritmos/particion.h"
#include "algoritmos/alg_grafoMA.h"
#include "algoritmos/alg_grafoPMC.h"
#include "algoritmos/alg_grafo_E-S.h"

#include <iostream>
#include <cmath>
#include <map>

using namespace std;

// Ejercicio 1
struct ciudad {
    unsigned x, y;
};

pair<Particion, matriz<double>> Tombuctu (const Grafo& G, vector<ciudad> ciudades)
{
    const size_t n = G.numVert();
    Particion p(n);
    
    // Creo la matriz de coste
    typedef typename GrafoP<double>::vertice vertice;
    GrafoP<double> MC(n);
    for (vertice i = 0 ; i < n ; i++)
    {
        for (vertice j = 0 ; j < n ; j++)
        {
            if (G[i][j] == true) {
                if (p.encontrar(i) != p.encontrar(j))
                    p.unir(i,j);

                MC[i][j] = sqrt(pow(ciudades[j].x - ciudades[i].x, 2) + pow(ciudades[j].y - ciudades[i].y, 2));
            }
        }
    }

    matriz<vertice> P(n);
    matriz<double> f = Floyd(MC, P);

    return make_pair(p, f);
}

// Ejercicio 2
struct lineaAerea {
    ciudad c1, c2;
    double distancia;
    lineaAerea(ciudad x, ciudad y, double d) : c1(x), c2(y), distancia(d) {}
};

vector<lineaAerea> Tombuctu2 (const Grafo& arch, vector<ciudad> ciudades)
{
    const size_t nCiudades = arch.numVert();
    size_t nIslas = nCiudades;
    Particion p(nCiudades);

    typedef typename Grafo::vertice vertice;

    // Contar el número de islas
    for (vertice i = 0 ; i < nCiudades ; i++)
        for (vertice j = 0 ; j < nCiudades ; j++)
            if (arch[i][j] && p.encontrar(i) != p.encontrar(j)) {
                p.unir(i,j);
                nIslas--;
            }

    // Representantes de cada isla
    map<int, int> repres;
    int islas = 0;
    for (vertice i = 0 ; i < nCiudades ; i++)
        if (repres.insert(make_pair(p.encontrar(i), islas)).second)
            islas++;

    // Buscar los vuelos mínimos
    matriz<lineaAerea> vuelos(nIslas);
    for(int i = 0; i < nCiudades-1; i++)
    {
        for(int j = i+1; j < nCiudades; j++)
        {
            int isla1 = repres[p.encontrar(i)];
            int isla2 = repres[p.encontrar(j)];
            if(isla1 != isla2){
                double d = sqrt(pow(ciudades[i].x- ciudades[j].y, 2) + pow(ciudades[j].x - ciudades[j].y, 2));
                if(d < vuelos[isla1][isla2].distancia)
                    vuelos[isla1][isla2] = vuelos[isla2][isla1] = lineaAerea(ciudades[i], ciudades[j], d);
            }
        }
    }

    // Pasar los vuelos mínimos a un vector
    vector<lineaAerea>lineas(nIslas * (nIslas - 1) / 2);
    for(int i = 0 ; i < nIslas-1 ; i++)
        for(int j = i; j < nIslas; j++)
            lineas.push_back(vuelos[i][j]);

    return lineas;
}