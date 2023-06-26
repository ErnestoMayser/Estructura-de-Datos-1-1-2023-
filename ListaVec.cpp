// ---------------------------------------------------------------------------

#pragma hdrstop

#include "ListaVector.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

ListaVector::ListaVector() {
	this->longi = 0;
}

direccion ListaVector::fin() {
	if (this->vacia()) {
		cout << "LISTA VACIA\n";
	}
	else {
		return this->longi - 1;
	}
}

direccion ListaVector::primero() {
	if (!this->vacia()) {
		return 0;
	}
	else {
		cout << "LISTA VACIA\n";
	}
}

direccion ListaVector::siguiente(direccion p) {
	if (this->vacia()) {
		cout << "LISTA VACIA\n";
	}
	else {
		if (p + 1 == longi)
			cout << "POSICION INCORRECTA\n";
		else
			return p + 1;

	}
}

direccion ListaVector::anterior(direccion p) {
	if (this->vacia()) {
		cout << "LISTA VACIA\n";
	}
	else {
		if (p == 0)
			// p == 1 dependiende de como lo tomen las casillas del vector
				cout << "POSICION INCORRECTA\n";
		else
			return p - 1;

	}
}

int ListaVector::recupera(direccion p) {
	// max = 100;  p >= 0 && p <= 10
	if (this->vacia()) {
		cout << "LISTA VACIA\n";
	}
	else {
		if (p >= 0 && p < longi)
			return this->elementos[p];
		else
			cout << "POSICION INCORRECTA\n";
	}
}

void ListaVector::inserta(direccion p, int elem) {
	if (longi == maxVect) {
		cout << "LISTA LLENA\n";
	}
	else if (this->vacia()) {
		elementos[0] = elem;
		longi++;
	}
	else if (p >= 0 && p <= longi) { // p >= 0 && p <= -1
		for (int i = longi; i > p; i--) {
			this->elementos[i] = this->elementos[i - 1];
		}
		this->elementos[p] = elem;
		this->longi++;
	}
	else {
		cout << "POSICION INCORRECTA\n";
	}
}

void ListaVector::suprime(direccion p) {
	if (longi == 0) {
		cout << "LISTA VACIA\n";
	}
	else if (p >= 0 && p <= longi - 1) {
		for (int i = p; i < longi - 1; i++) {
			this->elementos[i] = this->elementos[i + 1];
		}
		longi--;
	}
	else {
		cout << "POSICION INCORRECTA\n";
	}
}

void ListaVector::modifica(direccion p, int elem) {
	if (longi == 0) {
		cout << "LISTA VACIA\n";
	}
	else if (p >= 0 && p <= longi - 1) {
		elementos[p] = elem;
	}
	else {
		cout << "POSICION INCORRECTA\n";
	}

}

bool ListaVector::vacia() {
	return longi == 0;
}

int ListaVector::longitud() {
	return this->longi;
}

string ListaVector::toStr() {
	// [4,3,5,5,3]
	string r = "[";
	for (int i = 0; i < longi; i++) {
		int e = elementos[i];
		r = r + to_string(e);
		if (i < longi - 1)
			r = r + ",";
	}
	r = r + "]";
	return r;
}

direccion ListaVector::localiza(int e) {
	for (int i = 0; i < longi; i++) {
		if (elementos[i] == e)
			return i;
	}
	return -1;
}

void ListaVector::elimina_dato(int e) {
	int i = 0;
	while (i < longi) {
		if (e == elementos[i]) {
			for (int j = i; j < longi - 1; j++) {
				this->elementos[j] = this->elementos[j + 1];
			}
			longi--;
		}
		else {
			i++;
		}

	}
}

void ListaVector::anula() {
	longi = 0;
}

void ListaVector::inserta_inicio(int e) {
	inserta(0, e);
}

void ListaVector::inserta_fin(int e) {
	inserta(longi, e);
}
