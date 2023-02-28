#include <iostream> 
#include <fstream> 
#include "TAD Conocidos/abin_E-S.hpp" 
#include "TAD Conocidos/abin_enlazada.hpp" 

using namespace std; 
 
typedef char tElto; 

// Ejercicio 1
bool AbinSimilares(const AbinEnla<tElto>& A, const AbinEnla<tElto>& B);
bool AbinSimilares_rec(const typename AbinEnla<tElto>::nodo& nA, const AbinEnla<tElto>& A, const typename AbinEnla<tElto>::nodo& nB, const AbinEnla<tElto>& B);

// Ejercicio 2
AbinEnla<tElto> AbinReflejado(const AbinEnla<tElto>& A);
const AbinEnla<tElto>& AbinReflejado_rec(const typename AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A);

int main () 
{ 
    AbinEnla<tElto> A, B;

    // Lectura del árbol desde el fichero abin.dat y asignación al nodo n de un nodo cualquiera
    ifstream fe("abin.dat");
    rellenarAbin(fe, A);
    fe.close();
    
    cout << "\n*** Mostrar árbol binario A ***\n"; 
    imprimirAbin(A);
    cout << endl;
    
    ifstream f2("abin2.dat");
    rellenarAbin(f2, B);
    f2.close();
    
    cout << "\n*** Mostrar árbol binario B ***\n"; 
    imprimirAbin(B);
    cout << endl;
    
    // PRÁCTICA
    cout << "Arboles similares? ";  // Ejercicio 1
    if (AbinSimilares(A,B))
        cout << "Si" << endl;
    else 
        cout << "No" << endl;
    cout << endl;
    
    cout << "Arbol reflejado: " << endl;    // Ejercicio 2
    imprimirAbin(AbinReflejado(A));

    return 0;
}

// EJERCICIO 1
bool AbinSimilares(const AbinEnla<tElto>& A, const AbinEnla<tElto>& B)
{
    return(AbinSimilares_rec(A.raiz(), A, B.raiz(), B));
}

bool AbinSimilares_rec(const typename AbinEnla<tElto>::nodo& nA, const AbinEnla<tElto>& A, const typename AbinEnla<tElto>::nodo& nB, const AbinEnla<tElto>& B)
{
    // AMBOS IGUALES Y NULOS
    if (A.hijoIzqdo(nA) == AbinEnla<tElto>::NODO_NULO && B.hijoIzqdo(nB) == AbinEnla<tElto>::NODO_NULO &&
    A.hijoDrcho(nA) == AbinEnla<tElto>::NODO_NULO && B.hijoDrcho(nB) == AbinEnla<tElto>::NODO_NULO)
        return true;

    // ALGUNO DISTINTO
    else if ((A.hijoIzqdo(nA) == AbinEnla<tElto>::NODO_NULO && B.hijoIzqdo(nB) != AbinEnla<tElto>::NODO_NULO) ||
    (A.hijoIzqdo(nA) != AbinEnla<tElto>::NODO_NULO && B.hijoIzqdo(nB) == AbinEnla<tElto>::NODO_NULO) ||
    (A.hijoDrcho(nA) == AbinEnla<tElto>::NODO_NULO && B.hijoDrcho(nB) != AbinEnla<tElto>::NODO_NULO) ||
    (A.hijoIzqdo(nA) != AbinEnla<tElto>::NODO_NULO && B.hijoIzqdo(nB) == AbinEnla<tElto>::NODO_NULO))
        return false;
    
    // AMBOS IGUALES IZQ NO NULO / DER NULO
    else if (A.hijoIzqdo(nA) != AbinEnla<tElto>::NODO_NULO && B.hijoIzqdo(nB) != AbinEnla<tElto>::NODO_NULO &&
    A.hijoDrcho(nA) == AbinEnla<tElto>::NODO_NULO && B.hijoDrcho(nB) == AbinEnla<tElto>::NODO_NULO)
        return(AbinSimilares_rec(A.hijoIzqdo(nA),A,A.hijoIzqdo(nB),B));

    // AMBOS IGUALES IZQ NULO / DER NO NULO
    else if (A.hijoIzqdo(nA) == AbinEnla<tElto>::NODO_NULO && B.hijoIzqdo(nB) == AbinEnla<tElto>::NODO_NULO &&
    A.hijoDrcho(nA) != AbinEnla<tElto>::NODO_NULO && B.hijoDrcho(nB) != AbinEnla<tElto>::NODO_NULO)
        return(AbinSimilares_rec(A.hijoDrcho(nA),A,A.hijoDrcho(nB),B));
    
    // AMBOS IGUALES NO NULOS    
    else 
        return(AbinSimilares_rec(A.hijoIzqdo(nA),A,A.hijoIzqdo(nB),B) && AbinSimilares_rec(A.hijoDrcho(nA),A,A.hijoDrcho(nB),B));

}

// EJERCICIO 2
AbinEnla<tElto> AbinReflejado(const AbinEnla<tElto>& A)
{
    AbinEnla<tElto> Reflejado (A);

    AbinReflejado_rec(Reflejado.raiz(), Reflejado);

    return Reflejado;
}

const AbinEnla<tElto>& AbinReflejado_rec(const typename AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A)
{
    if (n != AbinEnla<tElto>::NODO_NULO) {
        AbinEnla<tElto>::nodo nodoAux;

        nodoAux = n->hder;
        n->hder = n->hizq;
        n->hizq = nodoAux;

        AbinReflejado_rec(A.hijoIzqdo(n), A);
        AbinReflejado_rec(A.hijoDrcho(n), A);
    }

    return A;
}