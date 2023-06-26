// ---------------------------------------------------------------------------

#ifndef ListaVectorH
#define ListaVectorH
// ---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "Funciones.h"

using namespace std;

const int maxVect = 100;

typedef int direccion;

class ListaVector {
private:
	int elementos[maxVect]; // int elementos*; elementos = new int[maxVect];
	int longi;

public:
	ListaVector();
	// Funciones de direccion
	direccion fin();
	direccion primero();
	direccion siguiente(direccion);
	direccion anterior(direccion);
	// Selector
	int recupera(direccion);
	// modificadores
	void inserta(direccion, int);
	void inserta_inicio(int);
	void inserta_fin(int);
	void suprime(direccion);
	void modifica(direccion, int);
	//
	bool vacia();
	int longitud();
	string toStr();
	direccion localiza(int);
	void elimina_dato(int);
	void anula();
};

#endif
