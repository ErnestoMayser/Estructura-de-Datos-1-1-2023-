// ---------------------------------------------------------------------------

#pragma hdrstop

#include "UConjuntoSm.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

ConjuntoSm::ConjuntoSm() {
	mem = new CSMemoria();
	ptrConj = nulo;
	cant = 0;
}

ConjuntoSm::ConjuntoSm(CSMemoria* m) {
	mem = m;
	ptrConj = nulo;
	cant = 0;
}

bool ConjuntoSm::vacio() {
	return cant == 0;
}

int ConjuntoSm::cardinal() {
	return cant;
}

int ConjuntoSm::ordinal(int e) {
	int c = 0;
	int aux = ptrConj;
	while (aux != nulo) {
		c++; // empieza en 1
		int aux_dato = mem->obtener_dato(aux, dato); // (aux,"->dato")
		if (aux_dato == e) {
			return c;
		}
		aux = mem->obtener_dato(aux, c_sig); // (aux,"->sig")
	}
	return -1;
}

void ConjuntoSm::inserta(int e) {
	if (!pertenece(e)) {
		int dir = mem->new_espacio(datos); // (dato,sig)
		if (dir != nulo) {
			mem->poner_dato(dir, dato, e); // dir->dato = e;
			mem->poner_dato(dir, c_sig, ptrConj); // dir->sig = ptrConj;
			ptrConj = dir;
			cant++;
		}
		else
			cout << "ERROR NO EXISTE ESPACIO EN LA MEMORIA\n";
	}
	else
		cout << "ERROR ELEMENTO YA EXISTE\n";
}

int ConjuntoSm::localiza(int e) {
	int x = ptrConj;
	while (x != nulo) {
		int x_dato = mem->obtener_dato(x, dato);
		if (x_dato == e)
			return x;
		x = mem->obtener_dato(x, c_sig); // (x,"->sig"  x->sig;
	}
	return nulo;
}

int ConjuntoSm::anterior(int p) {
	if (this->vacio()) {
	}
	else if (p == ptrConj) {
	}
	else {
		int x = ptrConj;
		int ant = nulo;
		while (x != nulo) {
			if (x == p) {
				return ant;
			}
			ant = x;
			x = mem->obtener_dato(x, c_sig); // (x,"->sig"  x->sig;
		}
	}
}

void ConjuntoSm::suprime(int e) {
	int p = localiza(e);
	if (cant == 0) {
		return;
	}
	else if (p == ptrConj) {
		int x = ptrConj;
		ptrConj = mem->obtener_dato(ptrConj, c_sig); // ptrConj->sig;
		mem->delete_espacio(x); // delete(x);
	}
	else {
		int ant = anterior(p);
		int p_sig = mem->obtener_dato(p, c_sig); // p->sig;
		mem->poner_dato(ant, c_sig, p_sig); // ant->sig = p->sig;
		mem->delete_espacio(p); // delete(p);
	}
	cant--;
}

bool ConjuntoSm::pertenece(int e) {
	int x = ptrConj;
	while (x != nulo) {
		int x_dato = mem->obtener_dato(x, dato);
		if (x_dato == e)
			return true;
		x = mem->obtener_dato(x, c_sig); // x->sig;
	}
	return false;
}

int ConjuntoSm::muestrea() {
	if (!vacio()) {
		srand(time(NULL));
		int pos = rand() % cant;
		return elemento(pos);
	}
	else
		return 0;
}

int ConjuntoSm::elemento(int pos) {
	int c = 0;
	int aux = ptrConj;
	while (aux != nulo) {
		if (c == pos)
			return mem->obtener_dato(aux, dato); // aux->dato;
		c++;
		aux = mem->obtener_dato(aux, c_sig); // aux->sig;
	}
	return 0;
}

void ConjuntoSm::reiniciar() {
	while (vacio() == false) {
		int r = muestrea();
		suprime(r);
	}
}

string ConjuntoSm::toStr() {
	string r = "{";
	for (int i = 0; i < cant; i++) {
		r += to_string(elemento(i));
		if (i < cant - 1) {
			r += ",";
		}
	}
	r += "}";
	return r;
}

void ConjuntoSm::unir(ConjuntoSm *b, ConjuntoSm *c) {
	c->reiniciar();
	ConjuntoSm *aux = new ConjuntoSm();
	ConjuntoSm *a = this;
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

void ConjuntoSm::intersectar(ConjuntoSm *b, ConjuntoSm *c) {
	c->reiniciar();
	ConjuntoSm* a = this;
	ConjuntoSm* aux = new ConjuntoSm();
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
