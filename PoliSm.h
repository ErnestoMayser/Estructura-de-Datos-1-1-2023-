// ---------------------------------------------------------------------------

#ifndef UPoliSmH
#define UPoliSmH
// ---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "Funciones.h"
#include "UMemoria.h"

using namespace std;

const string p_data = "coef,exp,sig";
const string at_coef = "->coef";
const string at_exp = "->exp";
const string at_sig = "->sig";

class PoliSm {
private:
	CSMemoria *mem;
	int ptrPoli;
	int nt; // numero de terminos

	// metodos privados
	int existe_exponente(int exp);
	int anterior(int p);
	void suprime(int p);

public:
	PoliSm();
	PoliSm(CSMemoria *m);
	bool es_cero();
	void poner_termino(int coef, int exp);
	int coeficiente(int exp);
	int exponente(int nro);
	int grado();
	int numero_terminos();
	PoliSm *suma(PoliSm* otro);
	PoliSm *resta(PoliSm* otro);
	string toStr();
	void derivar();
};
#endif
