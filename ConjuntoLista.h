// ---------------------------------------------------------------------------

#ifndef UConjuntoListaH
#define UConjuntoListaH
// ---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "Funciones.h"
#include "ListaSm.h"
#include "ListaVector.h"

using namespace std;

class ConjuntoLista {
private:
	// ListaVector *lista;
	ListaSm *lista;

public:
	ConjuntoLista();
	bool vacio();
	int cardinal();
	int ordinal(int e);
	void inserta(int e);
	void suprime(int e);
	bool pertenece(int e);
	int muestrea();
	int elemento(int pos);
	void reiniciar();
	string toStr();
	void unir(ConjuntoLista *b, ConjuntoLista *c);
	// ConjuntoListaPtr* unir(ConjuntoListaPtr* B);
	void intersectar(ConjuntoLista *b, ConjuntoLista *c);
};
#endif
