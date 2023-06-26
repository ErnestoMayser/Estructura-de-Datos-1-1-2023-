// ---------------------------------------------------------------------------

#pragma hdrstop

#include "UPoliVector.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

PoliVector::PoliVector() {
	vc = new int[maxV];
	ve = new int[maxV];
	nt = 0;
}

bool PoliVector::es_cero() {
	return nt == 0;
}

void PoliVector::poner_termino(int coef, int exp) {
	int lug = existe_exponente(exp);
	if (lug != -1) {
		vc[lug] = vc[lug] + coef;
		if (vc[lug] == 0) {
			// desplazamos ese elemento
			eliminar_posicion(vc, lug, nt);
			eliminar_posicion(ve, lug, nt);
			nt--;
		}
	}
	else {
		nt++;
		vc[nt - 1] = coef;
		ve[nt - 1] = exp;
	}
}

int PoliVector::coeficiente(int exp) {
	if (exp >= 0 && exp <= grado()) {
		for (int i = 0; i < nt; i++) {
			if (ve[i] == exp)
				return vc[i];
		}
	}
	cout << "ERROR NO EXISTE TERMINO CON ESE EXPONENTE\n";
}

int PoliVector::exponente(int nro) {
	if (nro < nt)
		return ve[nro];
	else
		cout << "ERROR FUERA DE RANGO\n";
}

int PoliVector::grado() {
	if (nt > 0) {
		int max = ve[0];
		for (int i = 0; i < nt; i++) {
			if (ve[i] > max)
				max = ve[i];
		}
		return max;
	}
	else
		cout << "NO EXISTEN TERMINOS\n";
}

int PoliVector::numero_terminos() {
	return nt;
}

PoliVector* PoliVector::suma(PoliVector *otro) {
	PoliVector *pr = new PoliVector();
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

PoliVector* PoliVector::resta(PoliVector *otro) {
	PoliVector *pr = new PoliVector();
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

int PoliVector::existe_exponente(int exp) {
	for (int i = 0; i < nt; i++) {
		if (ve[i] == exp)
			return i;
	}
	return -1;
}

string PoliVector::toStr() {
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

void PoliVector::derivar() {
	for (int i = 0; i < numero_terminos(); i++) {
		int exp = exponente(i);
		int coef = coeficiente(exp);
		poner_termino(coef*(-1), exp);
		if (exp > 0) {
			poner_termino(coef * exp, exp - 1);
		}
	}
}
