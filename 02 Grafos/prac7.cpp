#include "algoritmos/alg_grafoPMC.h"
#include "algoritmos/alg_grafo_E-S.h"
#include "prac7.hpp"

#include <iostream>

using namespace std;

int main() {
    GrafoP<unsigned> G("grafo.dat");
    cout << endl << G << endl << endl;
    const size_t n = G.numVert();

    // Ejercicio 1
    viaje<unsigned> viaje = viajeMasCaro(G);

    cout << "Viaje mas caro:" << endl;
    cout << " - Origen: " << viaje.origen << endl;
    cout << " - Destino: " << viaje.destino << endl;
    cout << " - Coste: " << viaje.coste << endl << endl;

    // Ejercicio 3
    vector<unsigned> almacenamiento(n);
    almacenamiento = {1,3,4,6,7,6};
    vector<double> porcentajes(n);
    porcentajes = {0,100,25,50,20,70};
    distribucion d(n);
    d = distribucionStock(G,almacenamiento,porcentajes,0,23);
    
    cout << "Distribucion: " << endl;
    cout << " - Uds x Ciudad: ";
    for (size_t i = 0 ; i < n ; i++)
        cout << d.udsXciudad[i] << " ";
    cout << endl << " - Coste minimo total: " << d.costeMinTotal << endl << endl;

    return 0;
}