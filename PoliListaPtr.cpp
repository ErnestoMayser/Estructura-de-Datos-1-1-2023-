// ---------------------------------------------------------------------------

#pragma hdrstop

#include "UPoliListaPtr.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

PoliListaPtr::PoliListaPtr() {
	lista = new ListaPtr();
	nt = 0;
}

bool PoliListaPtr::es_cero() {
	return nt == 0;
}

NodoL* PoliListaPtr::exponente_existe(int exp) {
	NodoL* aux = lista->primero();
	while (aux != NULL) {
		NodoL* aux_sig = lista->siguiente(aux);
		int elemento = lista->recupera(aux_sig);
		if (elemento == exp) {
			return aux;
		}
		aux = lista->siguiente(aux_sig);
	}
	return NULL;
}

void PoliListaPtr::poner_termino(int coef, int exp) {
	if (coef != 0) {
		NodoL* existe = exponente_existe(exp);
		if (existe == NULL) {
			lista->inserta_fin(coef);
			lista->inserta_fin(exp);
			nt++;
		}
		else {
			int elemento = lista->recupera(existe);
			// existe->e = 4 ; coef = 3 ; existe->e = 7
			lista->modifica(existe, elemento + coef);
			if (lista->recupera(existe) == 0) {
				NodoL* exp_elim = lista->siguiente(existe);
				lista->suprime(existe);
				lista->suprime(exp_elim);
				nt--;
			}
		}
	}
}

int PoliListaPtr::coeficiente(int exp) {
	if (exp >= 0 && exp <= grado()) {
		NodoL* aux = lista->primero();
		while (aux != NULL) {
			NodoL* aux_sig = lista->siguiente(aux);
			int elemento = lista->recupera(aux_sig);
			if (elemento == exp)
				return lista->recupera(aux); // aux->elemento;
			aux = lista->siguiente(aux_sig); // aux->sig->sig;
		}
	}
	cout << "ERROR NO EXISTE EXPONENTE CON ESE TERMINO\n";
}

int PoliListaPtr::exponente(int nro) {
	int c = 0;
	NodoL* aux = lista->primero();
	NodoL* aux_sig = lista->siguiente(aux);
	int elemento = lista->recupera(aux_sig);
	int res = elemento;
	while (c < nro) {
		aux = lista->siguiente(lista->siguiente(aux)); // aux->sig->sig;
		res = lista->recupera(lista->siguiente(aux)); // aux->sig->elemento;
		c++;
	}
	return res;
}

int PoliListaPtr::grado() {
	NodoL* aux = lista->primero();
	NodoL* aux_sig = lista->siguiente(aux);
	int elemento = lista->recupera(aux_sig);
	int may = elemento;
	while (aux != NULL) {
		aux_sig = lista->siguiente(aux);
		elemento = lista->recupera(aux_sig);
		if (elemento > may)
			may = elemento;
		aux = lista->siguiente(lista->siguiente(aux));
	}
	return may;
}

int PoliListaPtr::numero_terminos() {
	return nt;
}

PoliListaPtr* PoliListaPtr::suma(PoliListaPtr* otro) {
	PoliListaPtr *pr = new PoliListaPtr();
	for (int i = 0; i < nt; i++) {
		int exp1 = this->exponente(i);
		int coef1 = this->coeficiente(exp1);
		pr->poner_termino(coef1, exp1);
	}
	for (int i = 0; i < otro->nt; i++) {
		// poner_termino(p1.coeficiente(p2.exponente(i)), p2.exponente(i))
		int exp2 = otro->exponente(i);
		int coef2 = otro->coeficiente(exp2);
		pr->poner_termino(coef2, exp2);
	}
	return pr;
}

PoliListaPtr* PoliListaPtr::resta(PoliListaPtr* otro) {
	PoliListaPtr *pr = new PoliListaPtr();
	for (int i = 0; i < nt; i++) {
		int exp1 = this->exponente(i);
		int coef1 = this->coeficiente(exp1);
		pr->poner_termino(coef1, exp1);
	}
	for (int i = 0; i < otro->nt; i++) {
		// poner_termino(p1.coeficiente(p2.exponente(i)), p2.exponente(i))
		int exp2 = otro->exponente(i);
		int coef2 = -otro->coeficiente(exp2);
		pr->poner_termino(coef2, exp2);
	}
	return pr;
}

string PoliListaPtr::toStr() {
	if (nt == 0)
		return "0";
	string ret = "";
	for (int i = 0; i < nt; i++) {
		int exp = this->exponente(i);
		int coef = this->coeficiente(exp);
		string signo;
		if (coef > 0)
			signo = "+";
		else {
			signo = "-";
			coef = coef*-1;
		}
		ret = ret + signo + to_string(coef) + "x^" + to_string(exp);
	}
	return ret;
}

void PoliListaPtr::derivar() {
	for (int i = 0; i < numero_terminos(); i++) {
		int exp = exponente(i);
		int coef = coeficiente(exp);
		poner_termino(coef*(-1), exp);
		if (exp > 0) {
			poner_termino(coef * exp, exp - 1);
		}
	}
}

void PoliListaPtr::poner1(int coef, int exp) {
	// ------------
	ListaPtr* k = lista;
	// -------------
	if (k->vacia()) {
		k->inserta(k->primero(), exp);
		k->inserta(k->primero(), coef);
		k->inserta(k->primero(), exp);
	}
	else {
		NodoL* encontrado = NULL;
		NodoL* aux = k->siguiente(k->primero());
		while (aux != NULL) {
			int elem = k->recupera(k->siguiente(aux));
			if (elem == exp) {
				encontrado = aux;
				break;
			}
			else
				aux = k->siguiente(k->siguiente(aux));
		}
		// Si encontrado sigue en nulo en una nueva insercion
		bool seActualizaGrado = false;
		if (encontrado == NULL) {
			// k->siguiente(k->primero()) es la segunda direcion;
			k->inserta(k->siguiente(k->primero()), exp);
			k->inserta(k->siguiente(k->primero()), coef);
			int gradoMax = k->recupera(k->primero());
			if (exp > gradoMax)
				seActualizaGrado = true;
		}
		else {
			int c = k->recupera(encontrado);
			int exp = k->recupera(k->siguiente(encontrado));
			k->modifica(encontrado, coef + c);
			if (coef + c == 0) {
				k->suprime(k->siguiente(encontrado));
				k->suprime(encontrado);
				if (k->longitud() == 1)
					k->suprime(k->primero());
				else {
					if (exp == k->recupera(k->primero()))
						seActualizaGrado = true;
				}
			}
		}
		if (seActualizaGrado == true) {
			NodoL* aux = k->siguiente(k->primero());
			int gradoNuevo = k->recupera(k->siguiente(aux));
			while (aux != NULL) {
				int elem = k->recupera(k->siguiente(aux));
				if (elem > gradoNuevo)
					gradoNuevo = elem;
				aux = k->siguiente(k->siguiente(aux));
			}
			k->modifica(k->primero(), gradoNuevo);
		}
	}
}

void PoliListaPtr::poner2(int coef, int exp) {
	// ------------
	ListaPtr* k = lista;
	// -------------
	if (k->vacia()) {
		k->inserta(k->primero(), exp);
		k->inserta(k->primero(), coef);
		k->inserta(k->primero(), exp);
	}
	else {
		NodoL* encontrado = NULL;
		NodoL* aux = k->primero();
		while (aux != k->fin()) {
			if (k->recupera(aux) == exp) {
				encontrado = aux;
				break;
			}
			else
				aux = k->siguiente(k->siguiente(aux));
		}
		// Si encontrado sigue en nulo en una nueva insercion
		bool seActualizaGrado = false;
		if (encontrado == NULL) {
			k->inserta(k->primero(), coef);
			k->inserta(k->primero(), exp);
			int gradoMax = k->recupera(k->fin());
			if (exp > gradoMax)
				seActualizaGrado = true;
		}
		else {
			int c = k->recupera(k->siguiente(encontrado));
			int exp = k->recupera(encontrado);
			k->modifica(k->siguiente(encontrado), coef + c);
			if (coef + c == 0) {
				k->suprime(k->siguiente(encontrado));
				k->suprime(encontrado);
				if (k->longitud() == 1)
					k->suprime(k->fin());
				else {
					if (exp == k->recupera(k->fin()))
						seActualizaGrado = true;
				}
			}
		}
		if (seActualizaGrado == true) {
			NodoL* aux = k->primero();
			int gradoNuevo = k->recupera(aux);
			while (aux != k->fin()) {
				int elem = k->recupera(aux);
				if (elem > gradoNuevo)
					gradoNuevo = elem;
				aux = k->siguiente(k->siguiente(aux));
			}
			k->modifica(k->fin(), gradoNuevo);
		}

	}
}

void PoliListaPtr::mostrar() {
	cout << lista->toStr() << endl;
}
