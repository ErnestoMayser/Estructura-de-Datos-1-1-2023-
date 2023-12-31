// ---------------------------------------------------------------------------

#pragma hdrstop

#include "UConjuntoListaPtr.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

ConjuntoListaPtr::ConjuntoListaPtr() {
	lista = new ListaPtr();
}

bool ConjuntoListaPtr::vacio() {
	return lista->vacia();
}

int ConjuntoListaPtr::cardinal() {
	return lista->longitud();
}

int ConjuntoListaPtr::ordinal(int e) {
	int c = 0;
	NodoL* aux = lista->primero();
	while (aux != NULL) {
		c++; // empieza en 1
		if (lista->recupera(aux) == e) {
			return c;
		}
		aux = lista->siguiente(aux);
	}
	return -1;
}

void ConjuntoListaPtr::inserta(int e) {
	if (!pertenece(e)) {
		lista->inserta(lista->primero(), e);
	}
}

void ConjuntoListaPtr::insertaExamen(int e) {
	NodoL* pertenece = lista->localiza(e);
	if (pertenece == NULL) { // significa que e no está en la lista
		lista->inserta(lista->primero(), e);
	}
	else
		cout << "ELEMENTO YA PERTENECE\n";
}

void ConjuntoListaPtr::insertaExamen1(int e) {
	NodoL* aux = lista->primero();
	bool pertenece = false;
	while (aux != NULL) {
		if (aux->elemento == e) {
			pertenece = true;
			break;
		}
		else
			aux = aux->sig;
	}
	if (pertenece == false) {
		lista->inserta(lista->primero(), e);
	}
	else
		cout << "ELEMENTO YA PERTENECE\n";
}

void ConjuntoListaPtr::suprime(int e) {
	if (pertenece(e)) {
		NodoL* nodo = lista->localiza(e);
		lista->suprime(nodo);
	}
}

bool ConjuntoListaPtr::pertenece(int e) {
	NodoL* existe = lista->localiza(e);
	if (existe == NULL)
		return false;
	else
		return true;

}

int ConjuntoListaPtr::muestrea() {
	if (!vacio()) {
		srand(time(NULL));
		int pos = rand() % cardinal();
		return elemento(pos);
	}
	else
		return 0;
}

int ConjuntoListaPtr::elemento(int pos) {
	int c = 0;
	NodoL* aux = lista->primero();
	while (aux != NULL) {
		if (c == pos) {
			return lista->recupera(aux);
		}
		c++;
		aux = lista->siguiente(aux);
	}
	return 0;
}

void ConjuntoListaPtr::reiniciar() {
	while (vacio() == false) {
		int r = muestrea();
		suprime(r);
	}
}

string ConjuntoListaPtr::toStr() {
	// return lista->toStr();
	string r = "{";
	for (int i = 0; i < cardinal(); i++) {
		r += to_string(elemento(i));
		if (i < cardinal() - 1) {
			r += ",";
		}
	}
	r += "}";
	return r;
}

void ConjuntoListaPtr::unir(ConjuntoListaPtr *b, ConjuntoListaPtr *c) {
	c->reiniciar();
	ConjuntoListaPtr *aux = new ConjuntoListaPtr();
	ConjuntoListaPtr *a = this;
	// Para insertar a en c
	while (a->vacio() == false) {
		int r = a->muestrea();
		c->inserta(r);
		a->suprime(r);
		aux->inserta(r);
	}
	// Para recuperar los datos de a
	while (aux->vacio() == false) {
		int r = aux->muestrea();
		aux->suprime(r);
		a->inserta(r);
	}
	// Para insertar b en c
	while (b->vacio() == false) {
		int r = b->muestrea();
		c->inserta(r);
		b->suprime(r);
		aux->inserta(r);
	}
	// Para recuperar los datos de b
	while (aux->vacio() == false) {
		int r = aux->muestrea();
		aux->suprime(r);
		b->inserta(r);
	}
}

void ConjuntoListaPtr::intersectar(ConjuntoListaPtr *b, ConjuntoListaPtr *c) {
	c->reiniciar();
	ConjuntoListaPtr* a = this;
	ConjuntoListaPtr* aux = new ConjuntoListaPtr();
	// Inserto si el elemento pertenece a A y a B
	while (a->vacio() == false) {
		int r = a->muestrea();
		if (a->pertenece(r) && b->pertenece(r)) {
			c->inserta(r);
		}
		a->suprime(r);
		aux->inserta(r);
	}
	// Recupero los elementos de a
	while (aux->vacio() == false) {
		int r = aux->muestrea();
		aux->suprime(r);
		a->inserta(r);
	}
}
