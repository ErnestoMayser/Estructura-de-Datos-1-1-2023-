// ---------------------------------------------------------------------------

#ifndef UPoliListaSmH
#define UPoliListaSmH

// ---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "Funciones.h"
#include "ListaSm.h"

class PoliListaSm {
private:
	ListaSm* lista;
	int nt; // numero de terminos

	// metodos privados
	int exponente_existe(int exp);

public:
	PoliListaSm();
	bool es_cero();
	void poner_termino(int coef, int exp);
	int coeficiente(int exp);
	int exponente(int nro);
	int grado();
	int numero_terminos();
	PoliListaSm* suma(PoliListaSm* otro);
	PoliListaSm* resta(PoliListaSm* otro);
	string toStr();
	void derivar();
};
#endif
