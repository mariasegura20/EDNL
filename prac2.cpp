#include <iostream> 
#include <fstream> 
#include "TAD Conocidos/abin_E-S.hpp" 
#include "TAD Conocidos/abin_enlazada.hpp" 

using namespace std; 
 
typedef char tElto; 

// Ejercicio 1
bool AbinSimilares(const AbinEnla<tElto>& A, const AbinEnla<tElto>& B);
bool AbinSimilares_rec(const typename AbinEnla<tElto>::nodo& nA, const AbinEnla<tElto>& A, const typename AbinEnla<tElto>::nodo& nB, const AbinEnla<tElto>& B);
int numHijosNodo(const typename AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A);

// Ejercicio 2
AbinEnla<tElto> AbinReflejado(const AbinEnla<tElto>& A);
const AbinEnla<tElto>& AbinReflejado_rec(const typename AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A);

int main () 
{ 
    AbinEnla<tElto> A, B;

    // Lectura de los árboles y asignación de un nodo cualquiera
    ifstream fe("abinA.dat");
    rellenarAbin(fe, A);
    fe.close();
    
    cout << "\n*** Mostrar abinA ***\n"; 
    imprimirAbin(A);
    cout << endl;
    
    ifstream f2("abinB.dat");
    rellenarAbin(f2, B);
    f2.close();
    
    cout << "\n*** Mostrar abinB ***\n"; 
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
{ return(AbinSimilares_rec(A.raiz(), A, B.raiz(), B)); }

bool AbinSimilares_rec(const typename AbinEnla<tElto>::nodo& nA, const AbinEnla<tElto>& A, const typename AbinEnla<tElto>::nodo& nB, const AbinEnla<tElto>& B)
{
    if (numHijosNodo(nA, A) == numHijosNodo(nB, B)) {
        if (numHijosNodo(nA, A) == 0)
            return true;
        else if (numHijosNodo(nA, A) == 2)
            return(AbinSimilares_rec(A.hijoIzqdo(nA),A,A.hijoIzqdo(nB),B) && AbinSimilares_rec(A.hijoDrcho(nA),A,A.hijoDrcho(nB),B));
        else {
            if (A.hijoIzqdo(nA) != AbinEnla<tElto>::NODO_NULO && B.hijoIzqdo(nB) != AbinEnla<tElto>::NODO_NULO)
                return(AbinSimilares_rec(A.hijoIzqdo(nA),A,A.hijoIzqdo(nB),B));
            else if (A.hijoDrcho(nA) != AbinEnla<tElto>::NODO_NULO && B.hijoDrcho(nB) != AbinEnla<tElto>::NODO_NULO)
                return(AbinSimilares_rec(A.hijoDrcho(nA),A,A.hijoDrcho(nB),B));
            else
                return false;
        }
    }
    else
        return false;
}

int numHijosNodo(const typename AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A)
{ return ((A.hijoIzqdo(n) != AbinEnla<tElto>::NODO_NULO) + (A.hijoDrcho(n) != AbinEnla<tElto>::NODO_NULO)); }

// EJERCICIO 2
AbinEnla<tElto> AbinReflejado(const AbinEnla<tElto>& A)
{
    AbinEnla<tElto> Reflejado (A);
    if (!A.arbolVacio())
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

// EJERCICIO 3
typedef struct
{
    double operando;
    char operador;
} expresion;

double expresionAbin(const AbinEnla<expresion>& A)
{
    return expresionAbin_rec(A.raiz(), A);
}

double expresionAbin_rec(const typename AbinEnla<expresion>::nodo& n, const AbinEnla<expresion>& A)
{
    if (A.hijoIzqdo(n) == AbinEnla<expresion>::NODO_NULO)
        return A.elemento(n).operando;
    else {
        switch (A.elemento(n).operador)
        {
            case '+': return expresionAbin_rec(A.hijoIzqdo(n), A) + expresionAbin_rec(A.hijoDrcho(n), A); break;
            case '-': return expresionAbin_rec(A.hijoIzqdo(n), A) - expresionAbin_rec(A.hijoDrcho(n), A); break;
            case '*': return expresionAbin_rec(A.hijoIzqdo(n), A) * expresionAbin_rec(A.hijoDrcho(n), A); break;
            case '/': return expresionAbin_rec(A.hijoIzqdo(n), A) / expresionAbin_rec(A.hijoDrcho(n), A); break;
            default: assert(false);
        }
    }
}