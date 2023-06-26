// ---------------------------------------------------------------------------

#ifndef UPoliVectorH
#define UPoliVectorH
// ---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "Funciones.h"

using namespace std;

const int maxV = 10;

class PoliVector {
private:
	int *vc; // int vc[max];
	int *ve; // int ve[max];
	int nt; // numero de terminos
	//metodos privados
    int existe_exponente(int exp);
public:
	PoliVector();
	bool es_cero();
	void poner_termino(int coef, int exp);
	int coeficiente(int exp);
	int exponente(int nro);
	int grado();
	int numero_terminos();
	PoliVector *suma(PoliVector *otro);
	PoliVector *resta(PoliVector *otro);
	string toStr();
	void derivar();
};

#endif
