// ---------------------------------------------------------------------------

#pragma hdrstop

#include "UPoliListaSm.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

PoliListaSm::PoliListaSm() {
	lista = new ListaSm();
	nt = 0;
}

bool PoliListaSm::es_cero() {
	return nt == 0;
}

// Me devuelve el coeficiente del exponente que mando si existe
// Si no existe me devuelve nulo = -1
int PoliListaSm::exponente_existe(int exp) {
	int aux = lista->primero();
	while (aux != nulo) {
		int aux_sig = lista->siguiente(aux); // aux->sig
		int aux_sig_elem = lista->recupera(aux_sig); // aux->sig->elemento
		if (aux_sig_elem == exp) {
			return aux;
		}
		aux = lista->siguiente(aux_sig);
	}
	return nulo;
}

void PoliListaSm::poner_termino(int coef, int exp) {
	int existe = exponente_existe(exp);
	if (existe == nulo) {
		if (coef != 0 && exp >= 0) {
			lista->inserta_fin(coef);
			lista->inserta_fin(exp);
			nt++;
		}
	}
	else {
		int existe_elem = lista->recupera(existe);
		lista->modifica(existe, existe_elem + coef);
		// existe->elemento = existe->elemento + coef;
		if (existe_elem == 0) {
			int exp_elim = lista->siguiente(existe);
			lista->suprime(existe);
			lista->suprime(exp_elim);
			nt--;
		}
	}
}

int PoliListaSm::coeficiente(int exp) {
	if (exp >= 0 && exp <= grado()) {
		int aux = lista->primero();
		while (aux != nulo) {
			int aux_sig = lista->siguiente(aux); // aux->sig
			int aux_sig_elem = lista->recupera(aux_sig); // aux->sig->elemento
			if (aux_sig_elem == exp)
				return lista->recupera(aux); // return aux->elemento
			aux = lista->siguiente(aux_sig);
		}
	}
	cout << "ERROR NO EXISTE EXPONENTE CON ESE TERMINO\n";
}

int PoliListaSm::exponente(int nro) {
	int c = 0;
	int aux = lista->primero();
	int aux_sig = lista->siguiente(aux); // aux->sig
	int aux_sig_elem = lista->recupera(aux_sig); // aux->sig->elemento
	int res = aux_sig_elem;
	while (c < nro) {
		aux = lista->siguiente(aux_sig); // aux = aux->sig->sig;
		aux_sig = lista->siguiente(aux); // aux->sig
		aux_sig_elem = lista->recupera(aux_sig); // aux->sig->elemento
		res = aux_sig_elem;
		c++;
	}
	return res;
}

int PoliListaSm::grado() {
	int aux = lista->primero();
	int aux_sig = lista->siguiente(aux); // aux->sig
	int aux_sig_elem = lista->recupera(aux_sig); // aux->sig->elemento
	int may = aux_sig_elem;
	while (aux != nulo) {
		if (aux_sig_elem > may)
			may = aux_sig_elem;
		aux = lista->siguiente(aux_sig); // aux = aux->sig->sig;
		aux_sig = lista->siguiente(aux); // aux->sig
		aux_sig_elem = lista->recupera(aux_sig); // aux->sig->elemento
	}
	return may;
}

int PoliListaSm::numero_terminos() {
	return nt;
}

PoliListaSm* PoliListaSm::suma(PoliListaSm* otro) {
	PoliListaSm *pr = new PoliListaSm();
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

PoliListaSm* PoliListaSm::resta(PoliListaSm* otro) {
	PoliListaSm *pr = new PoliListaSm();
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

string PoliListaSm::toStr() {
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

void PoliListaSm::derivar() {
	for (int i = 0; i < numero_terminos(); i++) {
		int exp = exponente(i);
		int coef = coeficiente(exp);
		poner_termino(coef*(-1), exp);
		if (exp > 0) {
			poner_termino(coef * exp, exp - 1);
		}
	}
}
