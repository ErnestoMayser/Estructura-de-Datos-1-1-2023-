// ---------------------------------------------------------------------------

#ifndef ListaSmH
#define ListaSmH
// ---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "UMemoria.h"

using namespace std;

typedef int direccion;

const string data = "elemento,sig";
const string elem = "->elemento";
const string sig = "->sig";

class ListaSm {
private:
	CSMemoria *mem;
	direccion ptrElementos;
	int longi;

public:
	ListaSm();
	ListaSm(CSMemoria*);
	// Funciones de direccion
	direccion fin();
	direccion primero();
	direccion siguiente(direccion);
	direccion anterior(direccion);
	// Selector
	int recupera(direccion);
	// modificadores
	void inserta(direccion, int);
	void suprime(direccion);
	void modifica(direccion, int);
	//
	bool vacia();
	int longitud();
	string toStr();
	//
	direccion localiza(int);
	void elimina_dato(int);
	void anula();
	void inserta_inicio(int);
	void inserta_fin(int);
};

#endif
