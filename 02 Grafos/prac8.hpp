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
    double x, y;
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

double distEuclidea(ciudad c1, ciudad c2)
{ return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2)); }

size_t ciudad_to_isla(ciudad c, vector<ciudad> ciudades, vector<int> repres, Particion p)
{
    // Busco la ciudad
    bool encontrado = false;
    size_t iter = 0;
    while (iter < ciudades.size() && !encontrado)
    {
        if(ciudades[iter].x == c.x && ciudades[iter].y == c.y)
            encontrado = true;
        else
            iter++;
    }

    // Busco representante
    int rep = p.encontrar(iter);
    encontrado = false;
    iter = 0;
    while(iter < repres.size() && !encontrado)
    {
        if(repres[iter] == rep)
            return iter;
        else
            iter++;
    }
}

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
    vector<int> repres(nIslas);
    int numRepres = 0;
    for(size_t i = 0 ; i < ciudades.size() && numRepres < nIslas ; i++)
    {
        int repreActual = p.encontrar(i);
        size_t iter = 0;
        bool encontrado = false;
        while (iter < numRepres && !encontrado)
        {
            if (repres[iter] == repreActual)
                encontrado = true;
            else
                iter++;
        }

        if (!encontrado)
        {
            repres[numRepres] = repreActual;
            numRepres++;
        }
    }

    // Insertar todas las lineas aéreas en un APO
    Apo<lineaAerea> APO(nCiudades * (nCiudades - 1) / 2);
    
    for(int i = 0; i < nCiudades-1; i++)
        for(int j = i+1; j < nCiudades; j++)
            APO.insertar(lineaAerea(ciudades[i], ciudades[j], distEuclidea(ciudades[i], ciudades[j])));

    // Vuelos mínimos
    matriz<bool> minimos(nIslas);
    for (size_t i = 0 ; i < nIslas ; i++)
        for (size_t j = i ; j < nIslas ; j++)
            minimos[i][j] = minimos[j][i] = false;

    vector<lineaAerea> vuelos(nIslas * (nIslas - 1) / 2);
    int cont = 0;
    while(cont < nIslas * (nIslas - 1) / 2)
    {
        lineaAerea la = APO.cima();
        APO.suprimir();
        size_t isla1 = ciudad_to_isla(la.c1, ciudades, repres, p);
        size_t isla2 = ciudad_to_isla(la.c2, ciudades, repres, p);
        if (minimos[isla1][isla2] == false) {
            minimos[isla1][isla2] = minimos[isla2][isla1] = true;
            vuelos.push_back(la);
        }
    }

    return vuelos;
}