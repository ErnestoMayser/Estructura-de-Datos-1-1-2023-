// ---------------------------------------------------------------------------

#ifndef UPoliPtrH
#define UPoliPtrH
// ---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "Funciones.h"

using namespace std;

struct NodoPoli {
	int coef;
	int exp;
	NodoPoli* sig;
};

class PoliPtr{
private:
	NodoPoli* ptrPoli;
	int nt; // numero de terminos
	// metodos privados
	NodoPoli* existe_exponente(int exp);
	NodoPoli* anterior(NodoPoli* p);
	void suprime(NodoPoli* p);

public:
	PoliPtr();
	bool es_cero();
	void poner_termino(int coef, int exp);
	int coeficiente(int exp);
	int exponente(int nro);
	int grado();
	int numero_terminos();
	PoliPtr *suma(PoliPtr *otro);
	PoliPtr *resta(PoliPtr *otro);
	PoliPtr* multiplicar(PoliPtr* otro);
	string toStr();
	void derivar();
};
#endif
