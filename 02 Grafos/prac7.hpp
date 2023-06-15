#include "algoritmos/alg_grafoPMC.h"
#include "algoritmos/alg_grafo_E-S.h"

#include <iostream>
#include <cmath>

using namespace std;

// Ejercicio 1
template <typename tCoste>
struct viaje {
    typename GrafoP<tCoste>::vertice origen, destino;
    tCoste coste;
};

template <typename tCoste>
matriz<tCoste> FloydMax(const GrafoP<tCoste>& G, matriz<typename GrafoP<tCoste>::vertice>& P)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t n = G.numVert();
    matriz<tCoste> A(n);

    P = matriz<vertice>(n);
    for (vertice i = 0; i < n; i++) {
        A[i] = G[i];
        A[i][i] = 0;
        P[i] = vector<vertice>(n, i);
    }

    for (vertice k = 0; k < n; k++)
        for (vertice i = 0; i < n; i++)
            for (vertice j = 0; j < n; j++) {
                tCoste ikj = suma(A[i][k], A[k][j]);
                if (ikj > A[i][j] && ikj != GrafoP<tCoste>::INFINITO) {
                    A[i][j] = ikj;
                    P[i][j] = k;
                }
            }
    return A;
}

template <typename tCoste>
viaje<tCoste> viajeMasCaro (const GrafoP<tCoste>& G)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t n = G.numVert();

    matriz<vertice> P(n);
    matriz<tCoste> f = FloydMax(G,P);

    viaje<tCoste> v;
    v.origen = v.destino = v.coste = 0;

    for (vertice i = 0 ; i < n ; i++)
    {
        for (vertice j = 0 ; j < n ; j++)
        {
            if (f[i][j] > v.coste && f[i][j] != GrafoP<tCoste>::INFINITO)
            {
                v.origen = i;
                v.destino = j;
                v.coste = f[i][j];
            }
        }
    }

    return v;
}

// Ejercicio 2
struct casilla {
    size_t f, c;
};

struct pared {
    casilla a, b;
};

bool adyacentes (casilla a, casilla b)
{ return ((abs(a.c - b.c) + abs(a.f - b.f)) == 1); }

GrafoP<size_t>::vertice casilla_to_vertice (casilla c, size_t N)
{
    typename GrafoP<size_t>::vertice v = c.f * N + c.c;
    return v;
}

casilla vertice_to_casilla (GrafoP<size_t>::vertice v, size_t N)
{
    casilla c;
    c.c = v % N;
    c.f = v / N;
    return c;
}

Lista<casilla> laberinto (size_t N, vector<pared> paredes, casilla entrada, casilla salida)
{
    // Construir el grafo
    const size_t n = N*N;
    GrafoP<size_t> G(n);
    
    typedef typename GrafoP<size_t>::vertice vertice;
    const size_t INFINITO = GrafoP<size_t>::INFINITO;
    
    // Casillas adyacentes
    for(vertice i = 0 ; i < n ; i++)
    {
        for (vertice j = 0 ; j < n ; j++)
        {
            if (adyacentes(vertice_to_casilla(i, N), vertice_to_casilla(j, N)))
                G[i][j] = G[j][i] = 1;
            else 
                G[i][j] = G[j][i] = INFINITO;
        }
    }

    // Paredes
    for (size_t i = 0 ; i < paredes.size() ; i++)
    {
        vertice a = casilla_to_vertice(paredes[i].a, N);
        vertice b = casilla_to_vertice(paredes[i].b, N);
        G[a][b] = INFINITO;
        G[b][a] = INFINITO;
    }

    // Camino más corto
    vertice e = casilla_to_vertice(entrada, N);
    vertice s = casilla_to_vertice(salida, N);
    
    vector<vertice> P(n);
    vector<size_t> d(n);
    d = Dijkstra(G, e, P);

    Lista<casilla> cRuta;
    GrafoP<size_t>::tCamino ruta = camino<vertice>(e, s, P);
    for (Lista<size_t>::posicion v = ruta.primera() ; v != ruta.fin() ; v = ruta.siguiente(v))
        cRuta.insertar(vertice_to_casilla(ruta.elemento(v), N), cRuta.fin());
    
    return cRuta;
}

// Ejercicio 3
template <typename tCoste>
void distribucionStock (const GrafoP<tCoste>& G, vector<unsigned> capacidad, vector<double> subvencion, typename GrafoP<tCoste>::vertice centro, unsigned cantidad)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
    const size_t n = G.numVert();

    GrafoP<tCoste> SA = G;  // SA == Subvenciones aplicadas

    for (vertice i = 0 ; i < n ; i++)
        for (vertice j = 0 ; j < n ; j++)
            if (SA[i][j] != INFINITO)
                SA[i][j] *= (1 - subvencion[j]/100);
    
    vector<tCoste> dSA(n);  // dSA == disjktra de SA
    vector<vertice> P(n);    
    dSA = Dijkstra(SA, centro, P);

    vector<unsigned> udsXciudad(n);
    double costeMinTotal = 0;

    while (cantidad > 0)
    {
        unsigned costeMin = INFINITO;
        vertice ciudadMin;
        for(vertice i = 0 ; i < n ; i++)
        {
            if (i != centro && dSA[i] < costeMin)
            {
                costeMin = dSA[i];
                ciudadMin = i;
            }
        }

        unsigned cant;
        if (capacidad[ciudadMin] < cantidad)
        {
            cant = capacidad[ciudadMin];
            dSA[ciudadMin] = INFINITO;
        }
        else
            cant = cantidad;

        cantidad -= cant;
        costeMinTotal += costeMin * cant;
        udsXciudad[ciudadMin] = cant;
    }

    cout << "Distribucion: " << endl;
    cout << " - Uds x Ciudad: ";
    for (size_t i = 0 ; i < n ; i++)
        cout << udsXciudad[i] << " ";
    cout << endl << " - Coste minimo total: " << costeMinTotal << endl << endl;

}

// Ejercicio 4
template <typename tCoste>
struct trabajo {
    typename GrafoP<tCoste>::vertice ciudad;
    unsigned cargas;
};

template <typename tCoste>
tCoste camionesZuelandia (const GrafoP<tCoste>& G, vector<trabajo<tCoste>> trabajos, typename GrafoP<tCoste>::vertice capital)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t n = G.numVert();

    vector<vertice> P(n);
    vector<tCoste> d(n), dInv(n);
    d = Dijkstra(G,capital,P);
    dInv = DijkstraInv(G,capital,P);

    tCoste dist = 0;

    for (size_t i = 0 ; i < trabajos.size() ; i++)
    {
        dist += d[trabajos[i].ciudad];
        dist += dInv[trabajos[i].ciudad];
    }

    return dist;
}

// Ejercicio 5
template <typename tCoste>
GrafoP<tCoste> grafoMinimo (const GrafoP<tCoste>& G1, const GrafoP<tCoste>& G2)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t n = G1.numVert();

    GrafoP<tCoste> G(n);

    for (vertice i = 0 ; i < n ; i++)
        for (vertice j = 0 ; j < n ; j++)
            G[i][j] = min(f1[i][j], f2[i][j]);
        
    return G;
}

enum transporte {CARRETERA, TREN, AVION};

template <typename tCoste>
Lista<typename GrafoP<tCoste>::vertice> viajeroAlergico (const GrafoP<tCoste>& carretera, const GrafoP<tCoste>& tren, const GrafoP<tCoste>& avion, tCoste dinero, transporte alergia, typename GrafoP<tCoste>::vertice origen)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t n = carretera.numVert();
    GrafoP<tCoste> G(n);

    if (alergia == CARRETERA)
        G = grafoMinimo(tren, avion);
    else if (alergia == TREN)
        G = grafoMinimo(carretera, avion);
    else if (alergia == AVION)
        G = grafoMinimo(carretera, tren);

    vector<vertice> P(n);
    vector<tCoste> d(n);
    d = Dijkstra(G, origen, P);

    Lista<vertice> ciudades;
    for (size_t i = 0 ; i < n ; i++)
        if (d[i] <= dinero)
            ciudades.insertar(ciudades.fin());

    return ciudades;
}

// Ejercicio 6
template <typename tCoste>
GrafoP<tCoste> viajeDosTransportes (const GrafoP<tCoste>& tren, const GrafoP<tCoste>& bus, typename GrafoP<tCoste>::vertice ciudad)
{
    const size_t n = tren.numVert();
    typedef typename GrafoP<tCoste>::vertice vertice;

    matriz<vertice> P(n);
    matriz<tCoste> fTren(n), fBus(n);

    fTren = Floyd(tren, P);
    fBus = Floyd(bus, P);

    GrafoP<tCoste> Gmin(n);
    for (vertice i = 0 ; i < n ; i++)
        for (vertice j = 0 ; j < n ; j++)
            Gmin[i][j] = min(min(fTren[i][j], fBus[i][j]), min(fTren[i][ciudad]+fBus[ciudad][j], fBus[i][ciudad] + fTren[ciudad][j]));
    
    return Gmin;
}

// Ejercicio 7
template <typename tCoste>
void viajeDosCiudades (const GrafoP<tCoste>& tren, const GrafoP<tCoste>& bus, typename GrafoP<tCoste>::vertice origen, typename GrafoP<tCoste>::vertice destino, typename GrafoP<tCoste>::vertice cambio1, typename GrafoP<tCoste>::vertice cambio2)
{
    const size_t n = tren.numVert();
    typedef typename GrafoP<tCoste>::vertice vertice;
    vector<tCoste> d(n), dInv(n);
    vector<vertice> P(n);

    d = Dijkstra(tren, origen, P);
    dInv = DijkstraInv(bus, destino, P);
    tCoste c1 = Dijkstra[cambio1] + DijkstraInv[cambio1];
    tCoste c2 = Dijkstra[cambio2] + DijkstraInv[cambio2];
    
    if (c1 < c2) {
        cout << "Ruta: " << origen << ", " << cambio1 << ", " << destino << endl;
        cout << "Coste mínimo: " << c1 << endl << endl;
    } else {
        cout << "Ruta: " << origen << ", " << cambio2 << ", " << destino << endl;
        cout << "Coste mínimo: " << c2 << endl << endl;
    }
}

// Ejercicio 8
template <typename tCoste>
tCoste unSoloTransbordo (const GrafoP<tCoste>& tren, const GrafoP<tCoste>& bus, typename GrafoP<tCoste>::vertice origen, typename GrafoP<tCoste>::vertice destino)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t n = tren.numVert();
    vector<vertice> P(n);
    vector<tCoste> dTren(n), dBus(n), dInvTren(n), dInvBus(n);

    dTren = Dijkstra(tren, origen, P);
    dInvTren = DijkstraInv(tren, destino, P);
    dBus = Dijkstra(bus, origen, P);
    dInvBus = DijkstraInv(bus, destino, P);

    // Precio minimo haciendo 1 transbordo (tren -> bus)
    tCoste minTrenBus = GrafoP<tCoste>::INFINITO;
    for (size_t i = 0 ; i < n ; i++)
        if (i != origen && i != destino && dTren[i]+dInvBus[i] < minTrenBus)
            minTrenBus = dTren[i] + dInvBus[i];

    // Precio minimo haciendo 1 transbordo (bus -> tren)
    tCoste minBusTren = GrafoP<tCoste>::INFINITO;
    for (size_t i = 0 ; i < n ; i++)
        if (i != origen && i != destino && dBus[i]+dInvTren[i] < minTrenBus)
            minBusTren = dBus[i] + dInvTren[i];

    return min(min(dTren[destino], dBus[destino]), min(minTrenBus, minBusTren));
}

// Ejercicio 9
void dosTransportesConTransbordo (const GrafoP<double>& tren, const GrafoP<double>& bus, typename GrafoP<double>::vertice origen, typename GrafoP<double>::vertice destino, double taxi)
{
    typedef typename GrafoP<double>::vertice vertice;
    const size_t nTren = tren.numVert();
    const size_t nBus = bus.numVert();

    GrafoP<double> G(nTren+nBus);

    // Añadir costes del tren
    for (vertice i = 0 ; i < nTren ; i++)
        for (vertice j = 0 ; j < nTren ; j++)
            G[i][j] = tren[i][j];
    
    // Añadir costes del bus
    for (vertice i = nTren ; i < nTren + nBus ; i++)
        for (vertice j = nTren ; j < nTren + nBus ; j++)
            G[i][j] = bus[i-nTren][j-nTren];
    
    // Añadir costes del taxi
    for (vertice i = 0 ; i < nTren ; i++)
        for (vertice j = nTren ; j < nTren + nBus ; j++)
            if (i == j-nTren)
                G[i][j] = taxi;

    for (vertice i = nTren ; i < nTren + nBus ; i++)
        for (vertice j = 0 ; j < nTren ; j++)
            if (i-nTren == j)
                G[i][j] = taxi;

    // Calcular costes mínimos y camino
    vector<vertice> PTren(nTren+nBus), PBus(nTren+nBus);
    vector<double> dTren(nTren+nBus), dBus(nTren+nBus);
    dTren = Dijkstra(G,origen, PTren);
    dBus = Dijkstra(G, origen+nTren, PBus);

    double minimo = min(min(dTren[destino], dTren[destino+nTren]), min (dBus[destino], dBus[destino+nTren]));

    if (minimo == dTren[destino]) {
        cout << "Camino: " << camino<double>(origen, destino, PTren);
        cout << endl << "Coste: " << dTren[destino] << endl << endl;
    } else if (minimo == dBus[destino]) {
        cout << "Camino: " << camino<double>(origen+nTren, destino, PBus);
        cout << endl << "Coste: " << dBus[destino] << endl << endl;
    } else if (minimo == dTren[destino+nTren]) {
        cout << "Camino: " << camino<double>(origen, destino+nTren, PTren);
        cout << endl << "Coste: " << dTren[destino+nTren] << endl << endl;
    } else if (minimo == dBus[destino+nTren]) {
        cout << "Camino: " << camino<double>(origen+nTren, destino+nTren, PBus);
        cout << endl << "Coste: " << dBus[destino+nTren] << endl << endl;
    }
}

// Ejercicio 10
void tresTransportesConTransbordo (const GrafoP<double>& tren, const GrafoP<double>& bus, const GrafoP<double>& avion, typename GrafoP<double>::vertice origen, typename GrafoP<double>::vertice destino, double taxiEstacion, double taxiAeropuerto)
{
    typedef typename GrafoP<double>::vertice vertice;
    const size_t nTren = tren.numVert();
    const size_t nBus = bus.numVert();
    const size_t nAvion = avion.numVert();
    
    GrafoP<double> G(nTren + nBus + nAvion);

    // Tren
    for (vertice i = 0 ; i < nTren ; i++)
        for (vertice j = 0 ; j < nTren ; j++)
            G[i][j] = tren[i][j];
    
    // Bus
    for (vertice i = nTren ; i < nTren + nBus ; i++)
        for (vertice j = nTren ; j < nTren + nBus ; j++)
            G[i][j] = bus[i-nTren][j-nBus];
    
    // Avión
    for (vertice i = nTren + nBus ; i < nTren + nBus + nAvion ; i++)
        for (vertice j = nTren + nBus ; j < nTren + nBus + nAvion ; j++)
            G[i][j] = avion[i-nTren-nBus][j-nTren - nBus];
        
    // Tren - Bus
    for (vertice i = 0 ; i < nTren ; i++)
        for (vertice j = nTren ; j < nTren + nBus ; j++)
            if (i == j-nTren)
                G[i][j] = taxiEstacion;
    
    // Bus - Tren
    for (vertice i = nTren ; i < nTren + nBus ; i++)
        for (vertice j = 0 ; j < nTren ; j++)
            if (i-nTren == j)
                G[i][j] = taxiEstacion;

    // Tren - Avión 
    for (vertice i = 0 ; i < nTren ; i++)
        for (vertice j = nTren + nBus ; j < nTren + nBus + nAvion; j++)
            if (i == j-nTren-nAvion)
                G[i][j] = taxiAeropuerto;
    
    // Avión - Tren
    for (vertice i = nTren + nBus ; i < nTren + nBus + nAvion; i++)
        for (vertice j = 0 ; j < nTren ; j++)
            if (i-nTren-nAvion == j)
                G[i][j] = taxiAeropuerto;

    // Bus - Avión
    for (vertice i = nTren ; i < nTren + nBus ; i++)
        for (vertice j = nTren + nBus ; j < nTren + nBus + nAvion ; j++)
            if (i == j-nBus)
                G[i][j] = taxiAeropuerto;
    
    // Avión - Bus
    for (vertice i = nTren + nBus ; i < nTren + nBus + nAvion ; i++)
        for (vertice j = nTren ; j < nTren + nBus ; j++)
            if (i-nBus == j)
                G[i][j] = taxiAeropuerto;

    const size_t N = nTren +nBus + nAvion;
    vector<vertice> PTren(N), PBus(N), PAvion(N);
    vector<double> dTren(N), dBus(N), dAvion(N);

    dTren = Dijkstra(G, origen, PTren);
    dBus = Dijkstra(G, origen+nTren, PBus);
    dAvion = Dijkstra(G, origen+nTren+nBus, PAvion);
    
    double minTren = min(dTren[destino], min(dTren[destino+nTren], dTren[destino+nTren+nBus]));
    double minBus = min(dBus[destino], min(dBus[destino+nTren], dBus[destino+nTren+nBus]));
    double minAvion = min(dAvion[destino], min(dAvion[destino+nTren], dAvion[destino+nTren+nBus]));

    double minimo = min(minTren, min(minBus, minAvion));

    if (minimo == dTren[destino]) {
        cout << "Camino: " << camino<double>(origen, destino, PTren);
        cout << endl << "Coste: " << dTren[destino] << endl << endl;
    } else if (minimo == dTren[destino+nTren]) {
        cout << "Camino: " << camino<double>(origen, destino+nTren, PTren);
        cout << endl << "Coste: " << dTren[destino+nTren] << endl << endl;
    } else if (minimo == dTren[destino+nTren+nBus]) {
        cout << "Camino: " << camino<double>(origen, destino+nTren+nBus, PTren);
        cout << endl << "Coste: " << dTren[destino+nTren+nBus] << endl << endl;
    } else if (minimo == dBus[destino]) {
        cout << "Camino: " << camino<double>(origen, destino, PBus);
        cout << endl << "Coste: " << dBus[destino] << endl << endl;
    } else if (minimo == dBus[destino+nTren]) {
        cout << "Camino: " << camino<double>(origen, destino+nTren, PBus);
        cout << endl << "Coste: " << dBus[destino+nTren] << endl << endl;
    } else if (minimo == dBus[destino+nTren+nBus]) {
        cout << "Camino: " << camino<double>(origen, destino+nTren+nBus, PBus);
        cout << endl << "Coste: " << dBus[destino+nTren+nBus] << endl << endl;
    } else if (minimo == dAvion[destino]) {
        cout << "Camino: " << camino<double>(origen, destino, PAvion);
        cout << endl << "Coste: " << dAvion[destino] << endl << endl;
    } else if (minimo == dAvion[destino+nTren]) {
        cout << "Camino: " << camino<double>(origen, destino+nTren, PAvion);
        cout << endl << "Coste: " << dAvion[destino+nTren] << endl << endl;
    } else if (minimo == dAvion[destino+nTren+nBus]) {
        cout << "Camino: " << camino<double>(origen, destino+nTren+nBus, PAvion);
        cout << endl << "Coste: " << dAvion[destino+nTren+nBus] << endl << endl;
    }
}

// Ejercicio 11
// Asumo que el puente es en un sentido
template <typename tCoste>
struct puente {
    typename GrafoP<tCoste>::vertice ciudad1, ciudad2;
};

template <typename tCoste>
GrafoP<tCoste> Huries (const GrafoP<tCoste>& isla1, const GrafoP<tCoste>& isla2, const GrafoP<tCoste>& isla3, Lista<puente<tCoste>> puentes)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t n1 = isla1.numVert();
    const size_t n2 = isla2.numVert();
    const size_t n3 = isla3.numVert();

    GrafoP<tCoste> G(n1+n2+n3);

    // Isla 1
    for (vertice i = 0 ; i < n1 ; i++)
        for (vertice j = 0 ; j < n1 ; j++)
            G[i][j] = isla1[i][j];

    // Isla 2
    for (vertice i = n1 ; i < n1+n2 ; i++)
        for (vertice j = n1 ; j < n1+n2 ; j++)
            G[i][j] = isla2[i-n1][j-n1];
    
    // Isla 3
    for (vertice i = n1+n2 ; i < n1+n2+n3 ; i++)
        for (vertice j = n1+n2 ; j < n1+n2+n3 ; j++)
            G[i][j] = isla3[i-n1-n2][j-n1-n2];

    // Puentes
    for (typename Lista<puente<tCoste>>::posicion p = puentes.primera() ; p != puentes.fin() ; p = puentes.siguiente(p))
        G[puentes.elemento(p).ciudad1][puentes.elemento(p).ciudad2] = 0;
    
    // Calcular costes mínimos
    matriz<tCoste> f(n1+n2+n3);
    matriz<vertice> P(n1+n2+n3);
    f = Floyd(G,P);

    for(size_t i = 0 ; i < n1+n2+n3 ; i++)
        for (size_t j = 0 ; j < n1+n2+n3 ; j++)
            G[i][j] = f[i][j];
    
    return G;
}

// Ejercicio 12
// Asumo que al construir un puente es en ambos sentidos
template<typename tCoste>
tCoste costeTotal (matriz<tCoste> m)
{
    tCoste total = 0;
    for (size_t i = 0 ; i < m.dimension() ; i++)
        for (size_t j = 0 ; j < m.dimension() ; j++)
            if (m[i][j] != GrafoP<tCoste>::INFINITO)
                total += m[i][j];
        
    return total;
}

template <typename tCoste>
puente<tCoste> Grecoland (const GrafoP<tCoste>& Fobos, const GrafoP<tCoste>& Deimos, Lista<typename GrafoP<tCoste>::vertice> cCostFobos, Lista<typename GrafoP<tCoste>::vertice> cCostDeimos)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t n1 = Fobos.numVert();
    const size_t n2 = Deimos.numVert();

    GrafoP<tCoste> G(n1+n2);
    
    // Fobos
    for (vertice i = 0 ; i < n1 ; i++)
        for (vertice j = 0 ; j < n1 ; j++)
            G[i][j] = Fobos[i][j];

    // Deimos
    for (vertice i = n1 ; i < n1 + n2 ; i++)
        for (vertice j = n1 ; j < n1 + n2 ; j++)
            G[i][j] = Deimos[i-n1][j-n1];

    // Simular puentes
    tCoste minimo = GrafoP<tCoste>::INFINITO;
    vertice cFobos, cDeimos;

    typedef typename Lista<vertice>::posicion posicion;
    for (posicion f = cCostFobos.primera() ; f != cCostFobos.fin() ; f = cCostFobos.siguiente(f))
    {
        for (posicion d = cCostDeimos.primera() ; d != cCostDeimos.fin() ; d = cCostDeimos.siguiente(d))
        {
            vertice cFobosAct = cCostFobos.elemento(f);
            vertice cDeimosAct = cCostDeimos.elemento(d);

            // Crear puente
            G[cFobosAct][cDeimosAct] = 0;
            G[cDeimosAct][cFobosAct] = 0;

            // Reduce el coste?
            matriz<vertice> P;
            tCoste act = costeTotal(Floyd(G,P));
            if (act < minimo)
            {
                minimo = act;
                cFobos = cFobosAct;
                cDeimos = cDeimosAct;
            }

            // Destruir puente
            G[cFobosAct][cDeimosAct] = GrafoP<tCoste>::INFINITO;
        }
    }

    puente<tCoste> p;
    p.ciudad1 = cFobos;
    p.ciudad2 = cDeimos;

    return p;
}

// Ejercicio 13
// Asumo que al construir un puente es en ambos sentidos
template <typename tCoste>
tCoste mejorPuente(GrafoP<tCoste>& G, Lista<typename GrafoP<tCoste>::vertice> costeras1, Lista<typename GrafoP<tCoste>::vertice> costeras2, typename GrafoP<tCoste>::vertice& c1, typename GrafoP<tCoste>::vertice& c2)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    typedef typename Lista<vertice>::posicion posicion;

    tCoste minimo = GrafoP<tCoste>::INFINITO;
    for (posicion i = costeras1.primera() ; i != costeras1.fin() ; i = costeras1.siguiente(i))
    {
        for (posicion j = costeras2.primera() ; j != costeras2.fin() ; j = costeras2.siguiente(j))
        {
            // Simular puente
            G[i][j] = G[j][i] = 0;

            // Calcular coste
            matriz<vertice> P(G.numVert());
            tCoste act = costeTotal(Floyd(G,P));
            if (act < minimo) {
                minimo = act;
                c1 = i;
                c2 = j;
            }

            // Destruir puente
            G[i][j] = G[j][i] = GrafoP<tCoste>::INFINITO;
        }
    }

    return minimo;
}

template <typename tCoste>
vector<puente<tCoste>> puentesMinimos (const GrafoP<tCoste>& isla1, const GrafoP<tCoste>& isla2, const GrafoP<tCoste>& isla3, Lista<typename GrafoP<tCoste>::vertice> costeras1, Lista<typename GrafoP<tCoste>::vertice> costeras2, Lista<typename GrafoP<tCoste>::vertice> costeras3)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t n1 = isla1.numVert();
    const size_t n2 = isla2.numVert();
    const size_t n3 = isla3.numVert();

    GrafoP<tCoste> G(n1+n2+n3);

    for (vertice i = 0 ; i < n1 ; i++)
        for (vertice j = 0 ; j < n1 ; j++)
            G[i][j] = isla1[i][j];
    
    for (vertice i = n1 ; i < n1+n2 ; i++)
        for (vertice j = n1 ; j < n1+n2 ; j++)
            G[i][j] = isla2[i-n1][j-n1];
    
    for (vertice i = n1+n2 ; i < n1+n2+n3 ; i++)
        for (vertice j = n1+n2 ; j < n1+n2+n3 ; j++)
            G[i][j] = isla2[i-n1-n2][j-n1-n2];

    vertice c1_12, c2_12, c2_23, c3_23, c1_13, c3_13;

    tCoste puente12 = mejorPuente(G, costeras1, costeras2, c1_12, c2_12);
    tCoste puente23 = mejorPuente(G, costeras2, costeras3, c2_23, c3_23);
    tCoste puente13 = mejorPuente(G, costeras1, costeras3, c1_13, c3_13);

    vector<puente<tCoste>> v(2);
    puente<tCoste> p1, p2;

    if (puente12 > puente23 && puente12 > puente13) {
        p1.ciudad1 = c2_23;
        p1.ciudad2 = c3_23;
        p2.ciudad1 = c1_13;
        p2.ciudad2 = c3_13; 
    } else if (puente23 > puente12 && puente23 > puente13) {
        p1.ciudad1 = c1_12;
        p1.ciudad2 = c2_12;
        p2.ciudad1 = c1_13;
        p2.ciudad2 = c3_13; 
    } else if (puente13 > puente12 && puente13 > puente23) {
        p1.ciudad1 = c1_12;
        p1.ciudad2 = c2_12;
        p2.ciudad1 = c2_23;
        p2.ciudad2 = c3_23;
    }

    v[0] = p1;
    v[1] = p2;

    return v;
}