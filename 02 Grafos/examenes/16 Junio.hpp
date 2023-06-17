#include "../algoritmos/alg_grafoMA.h"
#include "../algoritmos/alg_GrafoPMC.h"

#include <iostream>
#include <cmath>

struct ciudad {
    double x, y;
};

struct puente {
    ciudad F, D;
    double distancia;
};

double distanciaEuclidea(ciudad c1, ciudad c2)
{ return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2)); }

typename GrafoP<double>::vertice buscarCiudad(size_t i, vector<ciudad> ciudades, vector<ciudad> costeras)
{
    bool encontrado = false;
    size_t iter = 0;
    while (iter < ciudades.size() && !encontrado)
    {
        if (ciudades[iter].x == costeras[i].x && ciudades[iter].y == costeras[i].y)
            encontrado = true;
        else
            iter++;
    }

    return iter;
}

double costeTotal(matriz<double> m)
{
    double total = 0;
    for (size_t i = 0 ; i < m.dimension() ; i++)
        for (size_t j = 0 ; j < m.dimension() ; j++)
            if (m[i][j] != GrafoP<double>::INFINITO)
                total += m[i][j];
    return total;
}

puente Grecolandia(const Grafo& F, const Grafo& D, vector<ciudad> cF, vector<ciudad> cD, vector<ciudad> ccF, vector<ciudad> ccD)
{
    // Construir Grafo
    const size_t nF = F.numVert();
    const size_t nD = D.numVert();
    const size_t n = nF + nD;

    typedef typename GrafoP<double>::vertice vertice;
    GrafoP<double> G(n);

    for (vertice i = 0 ; i < nF ; i++)
        for (vertice j = 0 ; j < nF ; j++)
            if (F[i][j])
                G[i][j] = distanciaEuclidea(cF[i], cF[j]);

    for (vertice i = nF ; i < n ; i++)
        for (vertice j = nF ; j < n ; j++)
            if (D[i-nF][j-nF])
                G[i][j] = distanciaEuclidea(cD[i-nF], cD[j-nF]);
    
    // Simulación de puentes
    puente p;
    p.distancia = GrafoP<double>::INFINITO;

    for (size_t i = 0 ; i < ccF.size() ; i++)
    {
        for (size_t j = 0 ; j < ccD.size() ; j++)
        {
            vertice f = buscarCiudad(i, cF, ccF);
            vertice d = buscarCiudad(j, cD, ccD) + nF;
            
            // Simular puente
            G[f][d] = G[d][f] = distanciaEuclidea(ccF[i], ccD[j]);
            
            // Calcular costes
            matriz<vertice> P;
            double actual = costeTotal(Floyd(G,P));

            if (actual < p.distancia) {
                p.F = ccF[i];
                p.D = ccD[j];
                p.distancia = G[f][d];
            }

            // Destruir puente simulado
            G[f][d] = G[d][f] = GrafoP<double>::INFINITO;
        }
    }

    return p;
}