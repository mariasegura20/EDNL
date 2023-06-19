// Supongo que solo puedo poner puentes entre ciudades costeras de distintas islas
#include "alg_grafoPMC.h"

#include <iostream>
#include <cmath>

struct ciudad {
    double x, y;
};

bool operator== (ciudad c1, ciudad c2)
{ return c1.x == c2.x && c1.y == c2.y; }

// Devuelve -1 si no es costera
int buscarCiudad (ciudad c, vector<ciudad> ciudades)
{
    bool encontrado = false;
    int iter = 0;
    while (iter < ciudades.size() && !encontrado)
    {
        if (c == ciudades[iter])
            encontrado = true;
        else
            iter++;
    }
    
    if (encontrado)
        return iter;
    else 
        return -1;
}

double distEuclidea (ciudad c1, ciudad c2)
{ return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2)); }

double Grecoland (vector<ciudad> Fobos, vector<ciudad> Deimos, vector<ciudad> Europa, vector<ciudad> cFobos, vector<ciudad> cDeimos, vector<ciudad> cEuropa, ciudad origen, ciudad destino)
{
    typedef typename GrafoP<double>::vertice vertice;
    const size_t nF = Fobos.size();
    const size_t nD = Deimos.size();
    const size_t nE = Europa.size();
    
    GrafoP<double> G(nF + nD + nE);

    double puenteCaro = 0;

    // Puentes Fobos - Deimos
    for (size_t i = 0 ; i < cFobos.size() ; i++)
    {
        vertice cF = buscarCiudad(cFobos[i], Fobos);
        for (size_t j = 0 ; j < cDeimos.size() ; j++)
        {
            vertice cD = buscarCiudad(cDeimos[j], Deimos);
            double d = distEuclidea(cFobos[i], cDeimos[j]);
            G[cF][cD+nF] = G[cD+nF][cF] = d;

            if (d > puenteCaro)
                puenteCaro = d;
        }
    }

    // Puentes Fobos - Europa
    for (size_t i = 0 ; i < cFobos.size() ; i++)
    {
        vertice cF = buscarCiudad(cFobos[i], Fobos);
        for (size_t j = 0 ; j < cEuropa.size() ; j++)
        {
            vertice cE = buscarCiudad(cEuropa[j], Europa);
            double d = distEuclidea(cFobos[i], cEuropa[j]);
            G[cF][cE+nF+nD] = G[cE+nF+nD][cF] = d;

            if (d > puenteCaro)
                puenteCaro = d;
        }
    }

    // Puentes Deimos - Europa
    for (size_t i = 0 ; i < cDeimos.size() ; i++)
    {
        vertice cD = buscarCiudad(cDeimos[i], Deimos);
        for (size_t j = 0 ; j < cEuropa.size() ; j++)
        {
            vertice cE = buscarCiudad(cEuropa[j], Europa);
            double d = distEuclidea(cDeimos[i], cEuropa[j]);
            G[cD+nF][cE+nF+nD] = G[cE+nF+nD][cD+nF] = d;

            if (d > puenteCaro)
                puenteCaro = d;
        }
    }

    // Carreteras Fobos
    for (vertice i = 0 ; i < nF - 1; i++)
        for (vertice j = i+1 ; j < nF ; j++)
            G[i][j] = G[j][i] = distEuclidea(Fobos[i], Fobos[j]) + puenteCaro;
    
    // Carreteras Deimos
    for (vertice i = nF ; i < nF + nD - 1; i++)
        for (vertice j = i+1 ; j < nF + nD ; j++)
            G[i][j] = G[j][i] = distEuclidea(Deimos[i-nF], Deimos[j-nF]) + puenteCaro;
    
    // Carreteras Europa
    for (vertice i = nF+nD ; i < nF+nD+nE - 1; i++)
        for (vertice j = i+1 ; j < nF+nD+nE ; j++)
            G[i][j] = G[j][i] = distEuclidea(Europa[i-nF-nD], Fobos[j-nF-nD]) + puenteCaro;

    // Diagonal principal a 0
    for (vertice i = 0 ; i < nF+nD+nE ; i++)
        G[i][i] = 0;

    GrafoP<double> K(nF+nD+nE);
    K = Kruskall(G);

    vector<vertice> P(nF+nD+nE);
    vector<double> dij(nF+nD+nE);
    
    vertice o = buscarCiudad(origen, Fobos);
    if (o == -1) {
        o = buscarCiudad(origen, Deimos);
        if (o == -1)
            o = buscarCiudad(origen, Europa);
    }
    
    vertice d = buscarCiudad(destino, Fobos);
    if (d == -1) {
        d = buscarCiudad(destino, Deimos);
        if (d == -1)
            d = buscarCiudad(destino, Europa);
    }

    

    dij = Dijkstra(K, o, P);
    return dij[d];
}