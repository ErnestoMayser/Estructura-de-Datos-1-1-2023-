// ---------------------------------------------------------------------------

#ifndef UConjuntoVH
#define UConjuntoVH
// ---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "Funciones.h"

using namespace std;

const int maxC = 10;

class ConjuntoV {
private:
	bool *vector; // bool arreglo[maxC];
	int cant;

public:
	ConjuntoV();
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
	void unir(ConjuntoV *b, ConjuntoV *c); // ConjuntoV* unir(ConjuntoV* B);
	void intersectar(ConjuntoV *b, ConjuntoV *c);

	ConjuntoV* complemento();
	void complementoAnB(ConjuntoV*b, ConjuntoV* c);
};

#endif
