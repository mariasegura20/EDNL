// En las cabeceras siempre nodo y luego árbol
// En los return siempre el 1 + va al principio
// EN UNA OPERACIÓN DENTRO DE UN TAD NUNCA SE LLAMA A UN MÉTODO DE LA CLASE
// El caso base siempre es nodo nulo (salvo alguna excepción que es con el nodo raiz)
// Dejar el return del caso base para el final

#include <iostream> 
#include <fstream> 
#include "TAD Conocidos/abin_E-S.hpp" 
#include "TAD Conocidos/abin_enlazada.hpp" 

using namespace std; 
 
typedef char tElto; 

// Ejercicio 1
int numNodosAbin(const AbinEnla<tElto>& A);
int numNodosAbin_rec(const typename AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A);

// Ejercicio 2
int alturaAbin(const AbinEnla<tElto>& A);
int alturaNodoAbin(const typename AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A);

// Ejercicio 3
int profundidadNodoAbin_rec(const typename AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A);
int profundidadNodoAbin_iter(typename AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A);

// Ejercicio 6
int desequilibrioAbin(const AbinEnla<tElto>& A);
int desequilibrioAbin_rec(const typename::AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A);
int desequilibrioNodoAbin(const typename::AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A);

// Ejercicio 7
bool pseudocompletoAbin(const AbinEnla<tElto>& A);
bool pseudocompletoAbin_rec(const typename AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A, int nivelProfundidad);
int numHijosNodo(const typename AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A);

int main () 
{ 
    AbinEnla<tElto> A, V;

    // Lectura de los árboles y asignación de un nodo cualquiera
    ifstream fe("abinA.dat");
    rellenarAbin(fe, A);
    fe.close();
    
    cout << "\n*** Mostrar abinA ***\n"; 
    imprimirAbin(A);
    cout << endl;

    ifstream f3("abinVacio.dat");
    rellenarAbin(f3, V);
    f3.close();
    
    cout << "\n*** Mostrar abinVacio ***\n"; 
    imprimirAbin(V);
    cout << endl;

    typename AbinEnla<tElto>::nodo n = A.hijoIzqdo(A.raiz());
    
    // PRÁCTICA
    cout << "Numero de nodos del arbol:" << numNodosAbin(A) << endl;    // Ejercicio 1
    cout << "Altura del arbol: " << alturaAbin(A) << endl;  // Ejercicio 2
    cout << "Profundidad del nodo (forma recursiva): " << profundidadNodoAbin_rec(n, A) << endl; // Ejercicio 3
    cout << "Profundidad del nodo (forma iterativa): " << profundidadNodoAbin_iter(n, A) << endl; // Ejercicio 3
    cout << "Desequilibrio del arbol: " << desequilibrioAbin(A) << endl;    // Ejercicio 6
    cout << "Arbol pseudocompleto? "; // Ejercicio 7
    if (pseudocompletoAbin(A))
        cout << "Si" << endl;
    else 
        cout << "No" << endl;
    cout << endl;
    
    return 0;
}

// EJERCICIO 1
int numNodosAbin(const AbinEnla<tElto>& A)
{
    return numNodosAbin_rec(A.raiz(), A);
}

int numNodosAbin_rec(const typename AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A)
{
    if (n == AbinEnla<tElto>::NODO_NULO)    
        return 0;                       
    else
        return 1 + numNodosAbin_rec(A.hijoIzqdo(n), A) + numNodosAbin_rec(A.hijoDrcho(n), A);
}

// EJERCICIO 2
int alturaAbin(const AbinEnla<tElto>& A)
{
    return alturaNodoAbin(A.raiz(), A);
}

int alturaNodoAbin(const typename AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A)
{
    if (n == AbinEnla<tElto>::NODO_NULO)
        // La altura de una hoja es 0 porque la única rama que tiene el nodo es el que va a si mismo, que tiene longitud 0
        return -1;                  // -1 para que la altura de una hoja sea 0. Consecuentemente el arbol vacío tiene una altura 0
    else
        return 1 + std::max(alturaNodoAbin(A.hijoIzqdo(n), A), alturaNodoAbin(A.hijoDrcho(n), A));
}

// EJERCICIO 3
int profundidadNodoAbin_rec(const typename AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A)
{
    if (n == A.raiz())
        return 0;
    else 
        return 1 + profundidadNodoAbin_rec(A.padre(n), A);
}

int profundidadNodoAbin_iter(typename AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A)
{
    int cont = 0;

    while(n != A.raiz())
    {
        cont++;
        n = A.padre(n);
    }

    return cont;
}

// EJERCICIO 5
// Sería meter alturaNodoAbin y el ejercicio 3 en el TAD

// EJERCICIO 6
int desequilibrioAbin(const AbinEnla<tElto>& A)
{
    return desequilibrioAbin_rec(A.raiz(), A);
}

int desequilibrioAbin_rec(const typename::AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A)
{
    if(n == AbinEnla<tElto>::NODO_NULO)
        return 0;
    else
        return max(max(desequilibrioNodoAbin(n,A), desequilibrioNodoAbin(A.hijoIzqdo(n),A)), desequilibrioNodoAbin(A.hijoDrcho(n),A));
}

int desequilibrioNodoAbin(const typename::AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A)
{
    return abs(alturaNodoAbin(A.hijoIzqdo(n), A) - alturaNodoAbin(A.hijoDrcho(n), A));
}

// EJERCICIO 7
bool pseudocompletoAbin(const AbinEnla<tElto>& A)
{
    int h = alturaAbin(A);
    if (h < 1)
        return true;
    else
        return pseudocompletoAbin_rec(A.raiz(), A, h - 1);
}

bool pseudocompletoAbin_rec(const typename AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A, int nivelProfundidad)
{
    if (profundidadNodoAbin_rec(n, A) == nivelProfundidad) {
        if (numHijosNodo(n,A) == 1)
            return false;
        else
            return true;
    }
    else {
        if (alturaNodoAbin(A.hijoIzqdo(n), A) > alturaNodoAbin(A.hijoDrcho(n), A)) {
            return pseudocompletoAbin_rec(A.hijoIzqdo(n), A, nivelProfundidad);
        }
        else if (alturaNodoAbin(A.hijoIzqdo(n), A) < alturaNodoAbin(A.hijoDrcho(n), A))
            return pseudocompletoAbin_rec(A.hijoDrcho(n), A, nivelProfundidad);
        else
            return pseudocompletoAbin_rec(A.hijoIzqdo(n), A, nivelProfundidad) && pseudocompletoAbin_rec(A.hijoDrcho(n), A, nivelProfundidad);
    }
}

int numHijosNodo(const typename AbinEnla<tElto>::nodo& n, const AbinEnla<tElto>& A)
{ return ((A.hijoIzqdo(n) != AbinEnla<tElto>::NODO_NULO) + (A.hijoDrcho(n) != AbinEnla<tElto>::NODO_NULO)); }