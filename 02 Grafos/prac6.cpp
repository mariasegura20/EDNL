#include "algoritmos/alg_grafoPMC.h"
#include "algoritmos/alg_grafo_E-S.h"
#include "prac6.hpp"

#include <iostream>

using namespace std;

int main()
{
    GrafoP<unsigned> G("grafo.dat");
    cout << endl << G << endl << endl;

    cout << "Longitud del diametro: " << longitudDiametro(G) << endl << endl;

    cout << "Ciclico? ";
    if(aciclico(G))
        cout << "No" << endl << endl;
    else
        cout << "Si" << endl << endl;

    vector<GrafoP<size_t>::vertice> ciudades = {0, 3};
    vector<carretera<size_t>> carreteras;
    carretera<size_t> c; c.origen = 2; c.destino = 1;
    carreteras.insert(carreteras.begin(), c);

    cout << "Zuelandia: " << endl;
    Zuelandia(G, ciudades, carreteras, 4);

    return 0;
} 