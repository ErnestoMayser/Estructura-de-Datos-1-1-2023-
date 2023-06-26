// ---------------------------------------------------------------------------

#ifndef UPoliListaPtrH
#define UPoliListaPtrH
// ---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "ListaPtr.h"

using namespace std;

class PoliListaPtr {
private:
	ListaPtr* lista;
	int nt; // numero de terminos

	// metodos privados
	NodoL* exponente_existe(int exp);

public:
	PoliListaPtr();
	bool es_cero();
	void poner_termino(int coef, int exp);
	int coeficiente(int exp);
	int exponente(int nro);
	int grado();
	int numero_terminos();
	PoliListaPtr* suma(PoliListaPtr* otro);
	PoliListaPtr* resta(PoliListaPtr* otro);
	void poner1(int coef, int exp);
	void poner2(int coef, int exp);
	string toStr();
	void derivar();
	void mostrar();
};
#endif
