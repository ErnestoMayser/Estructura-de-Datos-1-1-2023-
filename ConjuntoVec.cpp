// ---------------------------------------------------------------------------

#pragma hdrstop

#include "UConjuntoV.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

ConjuntoV::ConjuntoV() {
	vector = new bool[maxC];
	for (int i = 0; i < maxC; i++) {
		vector[i] = false; // v[i] = 0
	}
	cant = 0;
}

bool ConjuntoV::vacio() {
	return cant == 0;
}

int ConjuntoV::cardinal() {
	return cant;
}

int ConjuntoV::ordinal(int e) {
	if (e > 0 && e <= maxC) {
		int resp = 0;
		for (int i = 0; i < maxC; i++) {
			if (vector[i] != false) {
				resp++;
				if (e == (i + 1)) {
					return resp;
				}
			}
		}
		return resp;
	}
	return -1;
}

void ConjuntoV::inserta(int e) {
	if (e > 0 && e <= maxC) {
		if (!pertenece(e)) {
			vector[e - 1] = true; // vector[e] = 1
			cant++;
		}
	}
}

void ConjuntoV::suprime(int e) {
	if (e > 0 && e <= maxC) {
		if (pertenece(e)) {
			vector[e - 1] = false; // vector[e] = 0;
			cant--;
		}
	}
}

bool ConjuntoV::pertenece(int e) {
	if (e > 0 && e <= maxC) {
		return vector[e - 1];
	}
	return false;
}

int ConjuntoV::elemento(int pos) {
	int c = 0;
	for (int i = 0; i < maxC; i++) {
		if (vector[i] == true) { // v[i] == 1
			if (c == pos) {
				return i + 1;
			}
			c++;
		}
	}
	return 0;
}

int ConjuntoV::muestrea() {
	if (!vacio()) {
		srand(time(NULL));
		int pos = rand() % cant;
		return elemento(pos);
	}
	else
		return 0;
}

string ConjuntoV::toStr() {
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

// Metodo unir optimizado
// void ConjuntoV::unir(ConjuntoV *b, ConjuntoV *c) {
// c = new ConjuntoV();
// for (int i = 0; i < this->cardinal(); i++) {
// c->inserta(this->elemento(i));
// }
// for (int i = 0; i < b->cardinal(); i++) {
// c->inserta(b->elemento(i));
// }
// }

void ConjuntoV::unir(ConjuntoV *b, ConjuntoV *c) {
	c->reiniciar();
	ConjuntoV *aux = new ConjuntoV();
	ConjuntoV *a = this;
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

void ConjuntoV::reiniciar() {
	while (vacio() == false) {
		int r = muestrea();
		suprime(r);
	}
}
// Metodo intersectar optimizado
// void ConjuntoV::insersectar(ConjuntoV *b, ConjuntoV *c) {
// c = new ConjuntoV();
// ConjuntoV* a = this;
// for (int i = 0; i < a->cardinal(); i++) {
// int elem = a->elemento(i);
// if (a->pertenece(elem) && b->pertenece(elem)) {
// c->inserta(elem);
// }
// }
// }

void ConjuntoV::intersectar(ConjuntoV *b, ConjuntoV *c) {
	c->reiniciar();
	ConjuntoV* a = this;
	ConjuntoV* aux = new ConjuntoV();
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

ConjuntoV* ConjuntoV::complemento() {
	ConjuntoV* c = new ConjuntoV();
	for (int i = 0; i < maxC; i++) {
		if (!pertenece(i + 1)) {
			c->inserta(i + 1);
		}
	}
	return c;
}

void ConjuntoV::complementoAnB(ConjuntoV*b, ConjuntoV* c) {
	c->reiniciar();
	ConjuntoV* a = this;
	for (int i = 0; i < maxC; i++) {
		if (!(a->pertenece(i + 1) && b->pertenece(i + 1))) {
			c->inserta(i + 1);
		}
	}
}
