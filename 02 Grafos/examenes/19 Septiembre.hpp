#include "../algoritmos/alg_grafoMA.h"
#include "../algoritmos/alg_grafoPMC.h"

#include <iostream>
#include <cmath>

struct ciudad {
    double x, y;
};

struct puente {
    ciudad c1, c2;
};

typename GrafoP<double>::vertice buscarCiudad(size_t i, vector<ciudad> costeros, vector<ciudad> ciudades)
{
    typedef typename GrafoP<double>::vertice vertice;

    vertice ciudad = 0;
    bool encontrado = false;

    while (ciudad < ciudades.size() && !encontrado)
    {
        if(ciudades[ciudad].x == costeros[i].x && ciudades[ciudad].y == costeros[i].y)
            encontrado = true;
        else
            ciudad++;
    }

    return ciudad;
}

double costeTotal(matriz<double> m)
{
    double total = 0;
    
    for (size_t i = 0 ; i < m.dimension() ; i++)
        for (size_t j = i ; j < m.dimension() ; j++)
            if (m[i][j] != GrafoP<double>::INFINITO)
                total += m[i][j] + m[j][i];

    return total;
}

puente Grecoland (const Grafo& archipielago, vector<ciudad> ciudades, vector<ciudad> ccF, vector<ciudad> ccD)
{
    const size_t n = archipielago.numVert();
    GrafoP<double> G(n);

    // Creo la matriz de costes del archipiélago
    typedef typename GrafoP<double>::vertice vertice;
    for (vertice i = 0; i < n ; i++)
        for (vertice j = 0 ; j < n ; j++)
            if (archipielago[i][j])
                G[i][j] = sqrt(pow(ciudades[i].x - ciudades[j].x, 2) + pow(ciudades[i].y - ciudades[j].y, 2));

    // Simular posibles puentes para ver cual reduce el coste
    puente p;
    double total = GrafoP<double>::INFINITO;

    for (size_t i = 0 ; i < ccF.size() ; i++)
    {
        for (size_t j = 0 ; j < ccD.size() ; j++)
        {
            // Simular puente
            vertice F = buscarCiudad(i, ccF, ciudades);
            vertice D = buscarCiudad(j, ccD, ciudades);
            G[F][D] = G[D][F] = sqrt(pow(ccF[i].x - ccD[j].x, 2) + pow(ccF[i].y - ccD[j].y, 2));

            // Reduce el coste?
            matriz<vertice> P(n);
            double totalActual = costeTotal(Floyd(G,P));
            if (totalActual < total) {
                p.c1 = ccF[i];
                p.c2 = ccD[j];
                total = totalActual;
            }

            // Destruir puente simulado
            G[F][D] = G[D][F] = GrafoP<double>::INFINITO;
        }
    }

    return p;
}