// ---------------------------------------------------------------------------

#pragma hdrstop

#include "ListaSm.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

ListaSm::ListaSm() {
	this->mem = new CSMemoria();
	longi = 0;
	ptrElementos = nulo;
}

ListaSm::ListaSm(CSMemoria *me) {
	this->mem = me;
	longi = 0;
	ptrElementos = nulo;
}

// Funciones de direccion
direccion ListaSm::fin() {
	if (vacia()) {
		cout << "LISTA VACIA\n";
	}
	else {
		direccion ptrFin; // NodoL* ptrFin;
		direccion x = ptrElementos; // NodoL* x = ptrElementos;
		while (x != nulo) { // while (x != NULL) {
			ptrFin = x; // ptrFin = x;
			x = mem->obtener_dato(x, sig); // obte(x,"->sig") //	x = x->sig;
		}
		return ptrFin;
	}
}

direccion ListaSm::primero() {
	if (!this->vacia()) {
		return ptrElementos;
	}
	else {
		cout << "LISTA VACIA\n";
	}
}

direccion ListaSm::siguiente(direccion p) {
	if (this->vacia()) {
		cout << "LISTA VACIA\n";
	}
	else if (mem->obtener_dato(p, sig) == nulo)
	{ // (p,"->sig") | p->sig == NULL)
		cout << "DIRECCION INCORRECTA\n";
	}
	else {
		return mem->obtener_dato(p, sig); // p->sig
	}
}

direccion ListaSm::anterior(direccion p) {
	if (this->vacia()) {
		cout << "LISTA VACIA\n";
	}
	else if (p == primero()) {
		cout << "DIRECCION INCORRECTA\n";
	}
	else {
		direccion x = ptrElementos; // NodoL* x = ptrElementos;
		direccion ant = nulo; // NodoL* ant = NULL;
		while (x != nulo) { // while (x != NULL)
			if (x == p) { // if (x == p)
				return ant;
			}
			ant = x;
			x = mem->obtener_dato(x, sig); // (x,"->sig) | x = x->sig;
		}
	}
}

// Selector
int ListaSm::recupera(direccion p) {
	if (this->vacia()) {
		cout << "LISTA VACIA\n";
	}
	else {
		return mem->obtener_dato(p, elem); // (p,"->elemento")|p->elemento;
	}
}

// modificadores
void ListaSm::inserta(direccion p, int e) {
	int x = mem->new_espacio(data); // ("elemento,sig")|NodoL* x = new NodoL;
	if (x != nulo) {
		mem->poner_dato(x, elem, e); // x->elemento = e;
		mem->poner_dato(x, sig, nulo); // x->sig = NULL;
		if (vacia()) {
			ptrElementos = x;
			longi = 1;
		}
		else {
			longi++;
			if (p == primero()) {
				mem->poner_dato(x, sig, p); // x->sig = p;
				ptrElementos = x;
			}
			else {
				direccion ant = anterior(p); // NodoL* ant = anterior(p);
				mem->poner_dato(ant, sig, x); // ant->sig = x;
				mem->poner_dato(x, sig, p); // x->sig = p;
			}
		}
	}
}

void ListaSm::suprime(direccion p) {
	if (longi == 0) {
		cout << "LISTA VACIA\n";
		return;
	}
	else if (p == ptrElementos) {
		direccion x = ptrElementos; // NodoL*x = ptrElementos;
		ptrElementos = mem->obtener_dato(ptrElementos, sig);
		// ptrElementos = ptrElementos->sig;
		mem->delete_espacio(x); // delete(x);
	}
	else {
		direccion ant = anterior(p); // NodoL* ant = anterior(p);
		int p_sig = mem->obtener_dato(p, sig);
		mem->poner_dato(ant, sig, p_sig);
		// ant->sig = p->sig;
		mem->delete_espacio(p); // delete(p);
	}
	longi--;
}

void ListaSm::modifica(direccion p, int e) {
	if (vacia()) {
		cout << "LISTA VACIA\n";
	}
	else {
		mem->poner_dato(p, elem, e); // p->elemento = e;
	}
}

//
bool ListaSm::vacia() {
	return longi == 0; // ptrElementos == nulo;
}

int ListaSm::longitud() {
	return longi;
}

string ListaSm::toStr() {
	string r = "[";
	direccion x = ptrElementos; // NodoL* x = ptrElementos;
	while (x != nulo) {
		int x_elem = mem->obtener_dato(x, elem); // x->elemento
		r += to_string(x_elem);
		int x_sig = mem->obtener_dato(x, sig);
		if (x_sig != nulo)
			r += ",";
		x = x_sig;
	}
	r = r + "]";
	return r;
}

//
direccion ListaSm::localiza(int e) {
	direccion x = ptrElementos; // NodoL* x = ptrElementos;
	while (x != nulo) {
		int x_elem = mem->obtener_dato(x, elem);
		if (x_elem == e) // if(x->elemento == e)
				return x;
		x = mem->obtener_dato(x, sig); // x = x->sig;
	}
	return nulo;
}

void ListaSm::elimina_dato(int e) {
	direccion x = ptrElementos; // NodoL* x = ptrElementos;
	while (x != nulo) {
		int x_elem = mem->obtener_dato(x, elem);
		int x_sig = mem->obtener_dato(x, sig);
		if (x_elem == e) { // if (x->elemento == e) {
			direccion sup = x; // NodoL* sup = x;
			x = x_sig; // x = x->sig;
			suprime(sup);
		}
		else {
			x = x_sig; // x = x->sig;
		}
	}
}

void ListaSm::anula() {
	longi = 0;
	direccion x = ptrElementos; // NodoL* x = ptrElementos;
	while (x != nulo) {
		direccion aux = x; // NodoL* aux = x;
		x = mem->obtener_dato(x, sig); // x = x->sig;
		mem->delete_espacio(aux); // delete(aux);
	}
	ptrElementos = nulo;
}

void ListaSm::inserta_inicio(int e) {
	inserta(ptrElementos, e);
}

void ListaSm::inserta_fin(int e) {
	direccion x = mem->new_espacio(data); // NodoL* x = new NodoL;
	mem->poner_dato(x, elem, e); // x->elemento = e;
	mem->poner_dato(x, sig, nulo); // x->sig = NULL;
	if (vacia()) {
		ptrElementos = x;
	}
	else {
		direccion final = fin(); // NodoL* final = fin();
		mem->poner_dato(final, sig, x); // final->sig = x;
	}
	longi++;
}
