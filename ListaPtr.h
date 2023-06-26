// ---------------------------------------------------------------------------

#ifndef ListaPtrH
#define ListaPtrH

// ---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "Funciones.h"

using namespace std;

struct NodoL {
	int elemento;
	NodoL* sig;
	NodoL* ant;
};

class ListaPtr {
private:
	NodoL* ptrElementos;
	int longi;

	void intercambio(NodoL*, NodoL*);

public:
	ListaPtr();
	// Funciones de direccion
	NodoL* fin();
	NodoL* fin1();
	NodoL* primero();
	NodoL* siguiente(NodoL*);
	NodoL* anterior(NodoL*);
	// Selector
	int recupera(NodoL*);
	// modificadores
	void inserta(NodoL*, int);
	void inserta1(NodoL*, int);
	void inserta_inicio(int);
	void inserta_fin(int);
	void suprime(NodoL*);
	void suprime1(NodoL*);
	void suprimeEx(NodoL*);
	void modifica(NodoL*, int);
	void conectarUltimos();
	//
	bool vacia();
	int longitud();
	string toStr();
	//
	NodoL* localiza(int);
	void elimina_dato(int);
	void anula();
	void muestra_nodos();
	// Ejercicios tipo examen
	bool es_palindroma();
	void inserta(int, int);
	void elimina_nodo_con_mayor_dato();
	ListaPtr *sin_repetidos_ptr();
	ListaPtr sin_repetidos();
	void ordenamiento();
	NodoL* nodoEnPosicion(int k);
	void ordenamientoOp();
	void ordenamientoOp1();

	static void mostrarNodos(ListaPtr* lista);
};
#endif
