// ---------------------------------------------------------------------------

#pragma hdrstop

#include "UMemoria.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

CSMemoria::CSMemoria() {
	// NodoM *mem;
	mem = new NodoM[max_memoria];
	for (int i = 0; i < max_memoria; i++) {
		mem[i].link = i + 1;
	}
	mem[max_memoria - 1].link = nulo;
	libre = 0;
}

direccion_mem CSMemoria::new_espacio(string cad) {
	// cant = Numero_Ids(Cadena) // implementar numroids
	// DIR = LIBRE
	// D = LIBRE
	// PARA CADA I = 1 HASTA CANT -1
	// MEM[D].ID=Obtener_Id(i)
	// D = MEM [ D ].LINK
	// LIBRE=MEM [ D ].LINK
	// MEM [ D ].LINK = -1
	// MEM[D].ID=Obtener_Id(cant)
	//// RETORNAR DIR
	int x = 0;
	int cant = cantidad_ids(cad); // id = "dia,mes,año" -> 3
	if (cant <= espacios_disponibles()) {
		int dir = libre;
		int d = libre;
		string *ides = vector_ids(cad);
		for (int i = 0; i < cant - 1; i++) {
			mem[d].id = ides[i];
			d = mem[d].link;
		}
		libre = mem[d].link;
		mem[d].link = nulo;
		mem[d].id = ides[cant - 1];
		return dir;
	}
	else
		cout << "MEMORIA INSUFICIENTE\n";
}

void CSMemoria::delete_espacio(direccion_mem dir) {
	// X = DIR
	// MIENTRAS MEM[ X ].LINK<>-1
	// X= MEM [ X].LINK
	// MEM [ X].LINK=LIBRE
	// LIBRE=DIR
	int x = dir;
	while (mem[x].link != nulo) {
		x = mem[x].link;
	}
	mem[x].link = libre;
	libre = dir;
}

// poner_dato(0,"->dato",123);
void CSMemoria::poner_dato(direccion_mem dir, string id, int valor) {
	// Z = DIR
	// lugar=buscar_lugar_id(cadena_id)
	// PARA CADA I = I HASTA LUGAR -1
	// Z= MEM[ Z ].LINK
	// MEM[ Z ].DATO = valor
	if (id.substr(0, 2) == "->") // string id = "->dato" ---> "dato"
			id.erase(0, 2);
	int z = dir;
	while (z != nulo) {
		if (mem[z].id == id) { // "->dato == dato"
			mem[z].dato = valor;
			z = nulo;
		}
		else
			z = mem[z].link;
	}
}

int CSMemoria::obtener_dato(direccion_mem dir, string id) {
	// Z = DIR
	// lugar=buscar_lugar_id(cadena_id)
	// PARA CADA I = I HASTA LUGAR -1
	// Z= MEM[ Z ].LINK
	// RETORNAR MEM[ Z ].DATO
	if (id.substr(0, 2) == "->")
		id.erase(0, 2);
	int z = dir;
	while (z != nulo) {
		if (mem[z].id == id)
			return mem[z].dato;
		else
			z = mem[z].link;
	}
	return 0;
}

int CSMemoria::espacios_disponibles() {
	// X = LIBRE
	// C = 0 // CONTADOR
	// MIENTRAS X <> -1
	// C=C+1
	// X=MEM[ X ].LINK
	// FIN
	//// RETORNAR C
	int x = libre;
	int c = 0;
	while (x != nulo) {
		c++;
		x = mem[x].link;
	}
	return c;
}

int CSMemoria::espacios_ocupados() {
	return max_memoria - espacios_disponibles();
}

bool CSMemoria::ocupado(direccion_mem dir) {
	// X = LIBRE C = FALSO // BANDERA
	// MIENTRAS ( X <> -1) Y (C = FALSO)
	// SI X = DIR ENTONCES C = VERDADERO
	// FIN SI
	// X=MEM[ X ].LINK
	// FIN
	//// RETORNAR C // VERDADERO SI DIR ESTA LIBRE
	// FIN // FALSO SI DIR ESTA OCUPADA

	int x = libre;
	bool c = false;
	while (x != nulo && c == false) {
		if (x == dir)
			c = true;
		x = mem[x].link;
	}
	if (c == false)
		return true;
	else
		return false;
}

void CSMemoria::mostrar_libres() {
	cout << "Dir | id | dato | link" << endl;
	cout << "----------------------" << endl;
	for (int i = 0; i < max_memoria; i++) {
		if (!ocupado(i)) {
			cout << i << "   " << mem[i].id << "   " << mem[i]
				.dato << "   " << mem[i].link << endl;
		}
	}
	cout << "----------------------" << endl;

}

void CSMemoria::mostrar_ocupados() {
	cout << "Dir | id | dato | link" << endl;
	cout << "----------------------" << endl;
	for (int i = 0; i < max_memoria; i++) {
		if (ocupado(i)) {
			cout << i << "   " << mem[i].id << "   " << mem[i]
				.dato << "   " << mem[i].link << endl;
		}
	}
	cout << "----------------------" << endl;
}

// void CSMemoria::mostrar_memoria() {
// cout << "Dir | id | dato | link" << endl;
// cout << "----------------------" << endl;
// for (int i = 0; i < max_memoria; i++) {
// cout << i << "   " << mem[i].id << "   " << mem[i].dato << "   " << mem
// [i].link << endl;
// }
// cout << "----------------------" << endl;
// cout << "Libre : " << libre << endl;
// // cout << "Espacios ocupados : " << espacios_ocupados() << endl;
// // cout << "Espacios disponibles : " << espacios_disponibles() << endl;
// }

/*
 void CSMemoria::mostrar_memoria() {
 int esp = 5;
 string cab_dir = rellenar("dir", esp);
 string cab_id = rellenar("id", esp);
 string cab_dato = rellenar("dato", esp);
 string cab_link = rellenar("link", esp);
 string esp7 = "       ";
 string cabecera = esp7 + "|" + cab_dir + "|" + cab_dato + "|" + cab_id +
 "|" + cab_link + "|";
 string linea = esp7 + repetir(cabecera.length() - esp7.length(), '-');
 cout << cabecera << endl;
 cout << linea << endl;
 for (int i = 0; i < max_memoria; i++) {
 string ocup;
 ocupado(i) ? ocup = "ocupado" : ocup = esp7;
 string dir = rellenar(to_string(i), esp);
 string id = rellenar(mem[i].id, esp);
 string dato = rellenar(to_string(mem[i].dato), esp);
 string link = rellenar(to_string(mem[i].link), esp);
 cout << ocup << "|" << dir << "|" << dato << "|" << id << "|" << link <<
 "|" << endl;
 }
 cout << linea << endl;
 cout << esp7 << "Libre = " << to_string(libre) << endl;
 // cout << "Memoria disponible : " << to_string(espacios_disponibles()) << endl;
 // cout << "Memoria ocupado : " << to_string(espacios_ocupados()) << endl;
 } */

void CSMemoria::mostrar_memoria() {
	int espacios = 10;
	string dir1 = rellenar("DIR", 3);
	string id1 = rellenar("ID", espacios);
	string dato1 = rellenar("DATO", espacios);
	string link1 = rellenar("LINK", 4);
	string espacios7 = ""; // "       ";
	string cabecera = espacios7 + "|" + dir1 + "|" + dato1 + "|" + id1 + "|" +
		link1 + "|";
	string linea = espacios7 + "+" +
		repetir(cabecera.length() - espacios7.length() - 2, '-') + "+";
	cout << cabecera << endl;
	cout << linea << endl;
	for (int i = 0; i < max_memoria; i++) {
		string ocup;
		ocupado(i) ? ocup = "ocupado" : ocup = espacios7;
		string dir = rellenar(to_string(i), 3);
		string id = rellenar(mem[i].id, espacios);
		string dato = rellenar(to_string(mem[i].dato), espacios);
		string link = rellenar(to_string(mem[i].link), 4);
		cout << "|" << dir << "|" << dato << "|" << id << "|" << link <<
			"|" << endl;
	}
	cout << linea << endl;
	cout << espacios7 << "Libre = " << to_string(libre) << endl;
	cout << espacios7 << "Espacio disponible = " << to_string
		(espacios_disponibles()) << endl;
	cout << espacios7 << "Espacio ocupado = " << to_string(espacios_ocupados())
		<< endl;
}
