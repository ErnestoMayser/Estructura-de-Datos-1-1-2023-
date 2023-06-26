// ---------------------------------------------------------------------------

#pragma hdrstop

#include "ListaPtr.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

ListaPtr::ListaPtr() {
	longi = 0;
	ptrElementos = NULL;
}

// Funciones de direccion
NodoL* ListaPtr::fin() {
	if (vacia()) {
		cout << "LISTA VACIA\n";
	}
	else {
		NodoL* ptrFin;
		NodoL* x = ptrElementos;
		while (x != NULL) {
			ptrFin = x;
			x = x->sig;
		}
		return ptrFin;
	}
}

NodoL* ListaPtr::fin1() {
	if (vacia()) {
		cout << "Error, lista vacia\n";
	}
	else {
		if (longitud() == 1) {
			return ptrElementos;
		}
		else {
			NodoL* aux = ptrElementos;
			while (aux->sig != ptrElementos) {
				aux = aux->sig;
			}
			return aux;
		}
	}
}

void ListaPtr::conectarUltimos() {
	NodoL* fi = fin();
	fi->sig = ptrElementos;
}

NodoL* ListaPtr::primero() {
	if (!this->vacia()) {
		return ptrElementos;
	}
	else {
		cout << "LISTA VACIA\n";
	}
}

NodoL* ListaPtr::siguiente(NodoL* p) {
	if (this->vacia()) {
		cout << "LISTA VACIA\n";
	}
	else if (p->sig == NULL) { // p == fin()
		cout << "DIRECCION INCORRECTA\n";
	}
	else {
		return p->sig;
	}
}

NodoL* ListaPtr::anterior(NodoL* p) {
	if (this->vacia()) {
		cout << "LISTA VACIA\n";
	}
	else if (p == primero()) {
		cout << "DIRECCION INCORRECTA\n";
	}
	else {
		NodoL* x = ptrElementos;
		NodoL* ant = NULL;
		while (x != NULL) {
			if (x == p) {
				return ant;
			}
			ant = x;
			x = x->sig;
		}
	}
}

// Selector
int ListaPtr::recupera(NodoL* p) {
	if (this->vacia()) {
		cout << "LISTA VACIA\n";
	}
	else {
		return p->elemento;
	}
}

// modificadores
void ListaPtr::inserta(NodoL* p, int e) {
	NodoL* x = new NodoL;
	if (x != NULL) {
		x->elemento = e;
		x->sig = NULL;
		if (vacia()) {
			ptrElementos = x;
			longi = 1;
		}
		else {
			longi++;
			if (p == primero()) {
				x->sig = p;
				ptrElementos = x;
			}
			else {
				NodoL* ant = anterior(p);
				ant->sig = x;
				x->sig = p;
			}
		}
	}
}

void ListaPtr::inserta1(NodoL* p, int e) {
	NodoL* x = new NodoL;
	x->elemento = e;
	x->sig = NULL;
	if (vacia()) {
		x->sig = x;
		x->ant = x;
		ptrElementos = x;
		longi = 1;
	}
	else {
		if (p == primero()) {
			if (longi == 1) {
				ptrElementos->sig = x;
				ptrElementos->ant = x;
				x->sig = p;
				x->ant = ptrElementos;
				ptrElementos = x;
			}else{
				ptrElementos->ant = x;
				x->sig = ptrElementos;
				x->ant = fin();
				ptrElementos = x;
			}
		}
		else {
			NodoL* ant = anterior(p);
			ant->sig = x;
			p->ant = x;
			x->sig = p;
			x->ant = ant;
		}
		longi++;
	}
}

void ListaPtr::suprime(NodoL* p) {
	if (longi == 0) {
		cout << "LISTA VACIA\n";
		return;
	}
	else if (p == ptrElementos) {
		NodoL* x = ptrElementos;
		ptrElementos = ptrElementos->sig;
		delete(x);
	}
	else {
		NodoL* ant = anterior(p);
		ant->sig = p->sig;
		delete(p);
	}
	longi--;
}

void ListaPtr::suprime1(NodoL* p) {
	if (longi == 0) {
		cout << "LISTA VACIA\n";
		return;
	}
	else if (p == ptrElementos) {
		NodoL* x = ptrElementos;
		ptrElementos = ptrElementos->sig;
		delete(x);
	}
	else {
		NodoL* aux = ptrElementos;
		NodoL* ant = NULL;
		while (aux != p) {
			ant = aux;
			aux = aux->sig;
		}
		ant->sig = aux->sig;
		delete(aux);
	}
	longi--;
}

/* void ListaPtr::suprimeEx(NodoL* p) {
 if (vacia()) {
 cout << "Lista Vacia" << endl;
 }
 else {
 if (p == ptrElementos) {
 if (longi == 1)
 ptrElementos = NULL;
 else {
 ptrElementos = ptrElementos->sig;
 NodoL* ultimo = fin();
 if (ultimo == ptrElementos) {
 ptrElementos->sig = ptrElementos;
 ptrElementos->ant = ptrElementos;
 }
 else {
 ptrElementos->ant = ultimo;
 ultimo->sig = ptrElementos;
 }
 }
 delete(p);
 }
 else {
 NodoL* anterior = p->ant;
 NodoL* siguiente = p->sig;
 anterior->sig = siguiente;
 siguiente->ant = anterior;
 delete(p);
 }
 }
 } */

void ListaPtr::modifica(NodoL* p, int e) {
	if (vacia()) {
		cout << "LISTA VACIA\n";
	}
	else {
		p->elemento = e;
	}
}

//
bool ListaPtr::vacia() {
	return longi == 0; // ptrElementos == NULL;
}

int ListaPtr::longitud() {
	return longi;
}

string ListaPtr::toStr() {
	string r = "[";
	NodoL* x = ptrElementos;
	while (x != NULL) {
		r += to_string(x->elemento);
		if (x->sig != NULL)
			r += ",";
		x = x->sig;
	}
	r = r + "]";
	return r;
}

//
NodoL* ListaPtr::localiza(int e) {
	NodoL* x = ptrElementos;
	while (x != NULL) {
		if (x->elemento == e)
			return x;
		x = x->sig;
	}
	return NULL;
}

void ListaPtr::elimina_dato(int e) {
	NodoL* x = ptrElementos;
	while (x != NULL) {
		if (x->elemento == e) {
			NodoL* sup = x;
			x = x->sig;
			suprime(sup);
		}
		else {
			x = x->sig;
		}
	}
}

void ListaPtr::anula() {
	longi = 0;
	NodoL* x = ptrElementos;
	while (x != NULL) {
		NodoL* aux = x;
		x = x->sig;
		delete(aux);
	}
	ptrElementos = NULL;
}

void ListaPtr::inserta_inicio(int e) {
	inserta(ptrElementos, e);
}

void ListaPtr::inserta_fin(int e) {
	NodoL* x = new NodoL;
	x->elemento = e;
	x->sig = NULL;
	if (vacia()) {
		ptrElementos = x;
	}
	else {
		NodoL* final = fin();
		final->sig = x;
	}
	longi++;
}

void ListaPtr::muestra_nodos() {
	cout << "ptrElementos --> ";
	if (vacia()) {
		cout << "NULL";
	}
	else {
		NodoL* aux = ptrElementos;
		while (aux != NULL) {
			cout << "Nodo direccion: " << &(*aux);
			cout << " | Nodo dato: " << aux->elemento;
			if (aux->sig == NULL)
				cout << " | Nodo sig: NULL";
			else
				cout << " | Nodo sig: " << &(*aux->sig);
			aux = aux->sig;
			cout << endl << "                 ";
		}
	}
	cout << endl;
}

bool ListaPtr::es_palindroma() {
	if (this->vacia()) {
		cout << "LISTA VACIA" << endl;
		return false;
	}
	else if (this->longitud() == 1) {
		return true;
	}
	else {
		NodoL* adelante;
		NodoL* atras;
		adelante = primero();
		atras = fin();
		while (atras->sig != adelante && atras != adelante) {
			if (adelante->elemento != atras->elemento) {
				return false;
			}
			adelante = siguiente(adelante);
			atras = anterior(atras);
		}
		return true;
	}
}

void ListaPtr::inserta(int k, int elem) {
	// funciona cuando hay 1 o mas datos en la lista
	if (k >= 0 && k < longi) {
		NodoL* nuevo_nodo = new NodoL;
		nuevo_nodo->elemento = elem;
		nuevo_nodo->sig = NULL;
		if (k == 0) {
			nuevo_nodo->sig = ptrElementos;
			ptrElementos = nuevo_nodo;
		}
		else {
			NodoL* aux = ptrElementos;
			int cont = 0;
			while (cont < k && aux != NULL) {
				aux = aux->sig;
				cont++;
			}
			NodoL* ant = anterior(aux);
			ant->sig = nuevo_nodo;
			nuevo_nodo->sig = aux;

		}
	}
}

void ListaPtr::elimina_nodo_con_mayor_dato() {
	if (this->vacia()) {
		return;
	}
	else if (this->longi == 1) {
		this->suprime(this->primero());
	}
	else {
		NodoL* elim;
		NodoL* recorre;
		// elim = ptrElementos;
		// recorre = ptrElementos;
		elim = recorre = ptrElementos;
		while (recorre != NULL) {
			if (recorre->elemento > elim->elemento) {
				elim = recorre;
			}
			recorre = recorre->sig;
		}
		this->suprime(elim);
	}
}

// Lista: 5,3,2,4,3,10,5,6 ----> Lista Nueva: 2,4,3,10,5,6
ListaPtr* ListaPtr::sin_repetidos_ptr() {
	// Copia de la lista original
	ListaPtr* nueva = new ListaPtr();
	NodoL* aux = ptrElementos;
	while (aux != NULL) {
		nueva->inserta_fin(aux->elemento);
		aux = aux->sig;
	}
	//
	NodoL* nodo1 = nueva->primero();
	while (nodo1 != nueva->fin()) {
		NodoL* nodo2 = nueva->siguiente(nodo1);
		bool repetido = false;
		while (nodo2 != NULL && repetido == false) {
			if (nodo1->elemento == nodo2->elemento) {
				repetido = true;
			}
			nodo2 = nodo2->sig;
		}
		if (repetido == true) {
			NodoL* elim = nodo1;
			nodo1 = nodo1->sig;
			nueva->suprime(elim);
		}
		else {
			nodo1 = nodo1->sig;
		}
	}
	return nueva;
}

ListaPtr ListaPtr::sin_repetidos() {
	ListaPtr nueva;
	NodoL* aux = ptrElementos;
	while (aux != NULL) {
		nueva.inserta_fin(aux->elemento);
		aux = aux->sig;
	}
	//
	NodoL* nodo1 = nueva.primero();
	while (nodo1 != nueva.fin()) {
		NodoL* nodo2 = nueva.siguiente(nodo1);
		bool repetido = false;
		while (nodo2 != NULL && repetido == false) {
			if (nodo1->elemento == nodo2->elemento) {
				repetido = true;
			}
			nodo2 = nodo2->sig;
		}
		if (repetido == true) {
			NodoL* elim = nodo1;
			nodo1 = nodo1->sig;
			nueva.suprime(elim);
		}
		else {
			nodo1 = nodo1->sig;
		}
	}
	return nueva;
}

void ListaPtr::intercambio(NodoL* nodo1, NodoL* nodo2) {
	if (nodo1 == ptrElementos) {
		if (nodo1->sig == nodo2) {
			nodo1->sig = nodo2->sig;
			nodo2->sig = nodo1;
			ptrElementos = nodo2;
		}
		else {
			NodoL* sigNodo1 = nodo1->sig;
			NodoL* antNodo2 = anterior(nodo2);
			nodo1->sig = nodo2->sig;
			nodo2->sig = sigNodo1;
			antNodo2->sig = nodo1;
			ptrElementos = nodo2;
		}
	}
	else {
		if (nodo1->sig == nodo2) {
			NodoL* antNodo1 = anterior(nodo1);
			nodo1->sig = nodo2->sig;
			antNodo1->sig = nodo2;
			nodo2->sig = nodo1;
		}
		else {
			NodoL* antNodo1 = anterior(nodo1);
			NodoL* sigNodo1 = nodo1->sig;
			NodoL* antNodo2 = anterior(nodo2);
			nodo1->sig = nodo2->sig;
			antNodo1->sig = nodo2;
			nodo2->sig = sigNodo1;
			antNodo2->sig = nodo1;
		}
	}
}

void ListaPtr::ordenamiento() {
	int n = this->longitud();
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			NodoL* nodo1 = nodoEnPosicion(i);
			NodoL* nodo2 = nodoEnPosicion(j);
			int elem2 = nodo2->elemento;
			int elem1 = nodo1->elemento;
			if (elem2 < elem1) {
				intercambio(nodo1, nodo2);
			}
		}
	}
}

NodoL* ListaPtr::nodoEnPosicion(int k) {
	if (this->vacia()) {
		return NULL;
	}
	else {
		NodoL* aux = ptrElementos;
		int cont = 0;
		while (cont < k) {
			aux = aux->sig;
			cont++;
		}
		return aux;
	}
}

void ListaPtr::mostrarNodos(ListaPtr* lista) {
	NodoL* aux = lista->ptrElementos;
	while (aux != NULL) {
		cout << "Dato: " << aux->elemento << " | ";
		cout << "Dir: " << &(*aux) << " | ";
		if (aux->sig == NULL)
			cout << "Sig : NULL " << endl;
		else
			cout << "Sig : " << &(*aux->sig) << endl;
		aux = aux->sig;
	}
}

void ListaPtr::ordenamientoOp() {
	int n = longi;
	NodoL* nuevoPtr;
	for (int i = 0; i < n; i++) {
		NodoL* aux = ptrElementos;
		NodoL* menor = aux;
		while (aux != NULL) {
			if (aux->elemento < menor->elemento)
				menor = aux;
			aux = aux->sig;
		}
		suprime(menor);
		menor->sig = NULL;
		if (i == 0)
			nuevoPtr = menor;
		else {
			aux = nuevoPtr;
			while (aux->sig != NULL)
				aux = aux->sig;
			aux->sig = menor;
		}
	}
	ptrElementos = nuevoPtr;
}

void ListaPtr::ordenamientoOp1() {
	int n = longi;
	int m = n;
	for (int i = 0; i < n; i++) {
		NodoL* aux = ptrElementos;
		NodoL* menor = aux;
		for (int j = 0; j < m; j++) {
			if (aux->elemento < menor->elemento)
				menor = aux;
			aux = aux->sig;
		}
		suprime(menor);
		aux = ptrElementos;
		while (aux->sig != NULL)
			aux = aux->sig;
		menor->sig = NULL;
		aux->sig = menor;
		m--;
	}
}
