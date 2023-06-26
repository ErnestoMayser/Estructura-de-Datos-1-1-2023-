// ---------------------------------------------------------------------------

#ifndef UConjuntoSmH
#define UConjuntoSmH
// ---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "Funciones.h"
#include "UMemoria.h"

using namespace std;

const string datos = "dato,sig";
const string dato = "->dato";
const string c_sig = "->sig";

class ConjuntoSm {
private:
	CSMemoria* mem;
	int ptrConj;
	int cant;

	int localiza(int e);
	int anterior(int p);

public:
	ConjuntoSm();
	ConjuntoSm(CSMemoria* m);
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
	void unir(ConjuntoSm *b, ConjuntoSm *c);
	// ConjuntoPtr* unir(ConjuntoPtr* B);
	void intersectar(ConjuntoSm *b, ConjuntoSm *c);

};
#endif
