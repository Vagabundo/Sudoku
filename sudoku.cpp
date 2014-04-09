/*
 * sudoku.cpp
 *
 *  Created on: 15/02/2010
 *      Author: rromero
 */

#include "sudoku.h"

using namespace std;

/************************** Funciones privadas *************************/

// Esta función añade lista dada a la pila de jugadas
void sudoku::Add_Lista (const list<pair<pair<unsigned int, unsigned int>, celda> > &lista){
	_jugadas.push(lista);
}

// Esta función añade un nuevo elemento a la lista, que posteriormente se añadirá a la pila
void sudoku::Add_Celda (list<pair<pair<unsigned int, unsigned int>, celda> > &lista, const int &fila, const int &col){

	pair<pair<unsigned int, unsigned int>, celda> par2;
	pair<unsigned int, unsigned int> par1;

	par1.first = fila;
	par1.second = col;

	par2.first = par1;
	par2.second = _tablero[fila][col];

	lista.push_back(par2);
}

/************************** Funciones públicas *************************/

sudoku::sudoku(const string &file) : _tablero(vector<vector<celda> >(9, vector<celda>(9))) {
	string basura;
	unsigned int dato;

	ifstream fich(file.c_str());
	if (fich.is_open()) {
		fich >> basura;

	    unsigned int fila = 1;
	    unsigned int columna = 1;

	    while ((fila < 10) and (columna < 10)) {
	    	fich >> basura;
	    	// string to int
	    	istringstream buffer(basura);
			dato = 0;
	    	buffer >> dato;
	    	if ((dato >= 1) and (dato <= 9)) {
	    		bool res = _tablero[fila-1][columna-1].fijar_valor(dato, true);
	    		if (!res) {
	    			cout << "Problemas con el tablero..." << endl;
	    		}
	    	}
	    	++columna;
	    	if (columna == 10) {
	    		columna = 1;
	    		++fila;
	    	}
	    }

	    fich.close();
	  }
	else {
		cout << "Imposible abrir fichero " << file << endl;
	}
}

sudoku::~sudoku(){
}

bool sudoku::fijar_valor(const unsigned int &fila, const unsigned int &columna, const unsigned int &valor){

	bool fijado = false;
	list<pair<pair<unsigned int, unsigned int>, celda> > lista;

	if (es_factible(fila, columna, valor) && valor < 10 && valor > 0  && !_tablero[fila][columna].valida()){

		//elimino las opciones de la celda
		if (!_tablero[fila][columna].opciones().empty()){
			bool guardado = false;
			for (int i = 1; i < 10; i++)
				if (_tablero[fila][columna].opciones().find(i) != _tablero[fila][columna].opciones().end()){
					if (!guardado){    //si no está vacia, añado la celda a la lista para guardarla
						Add_Celda (lista, fila, columna);
						guardado = true;
					}
					_tablero[fila][columna].borrar_opcion(i);
				}
		}

		//elimino opciones de la fila
		for (int j = 0; j < 9; j++)
			if (_tablero[fila][j].opciones().find(valor) != _tablero[fila][j].opciones().end()){
				Add_Celda (lista, fila, j);
				_tablero[fila][j].borrar_opcion(valor);
			}

		//elimino opciones de la columna
		for (int i = 0; i < 9; i++)
			if (_tablero[i][columna].opciones().find(valor) != _tablero[i][columna].opciones().end()){
				Add_Celda (lista, i, columna);
				_tablero[i][columna].borrar_opcion(valor);
			}

		//elimino opciones del cuadro
		int cuadrante_i = (fila / 3);
		int cuadrante_j = (columna / 3);

		for (int i = (cuadrante_i*3); i < ((cuadrante_i*3)+3); i++)
			for (int j = (cuadrante_j*3); j < ((cuadrante_j*3)+3); j++)
				if (_tablero[i][j].opciones().find(valor) != _tablero[i][j].opciones().end()){
					Add_Celda (lista, i, j);
					_tablero[i][j].borrar_opcion(valor);
				}

		//fijo el valor
		bool hecho = _tablero[fila][columna].fijar_valor(valor);

		//push en la pila
		Add_Lista (lista);

		fijado = hecho;
	}
	else
		fijado = false;

	return fijado;
}

void sudoku::borrar_valor(const unsigned int &fila, const unsigned int &columna){

	list<pair<pair<unsigned int, unsigned int>, celda> > lista;
	Add_Celda (lista, fila, columna);
	Add_Lista (lista);
	_tablero[fila][columna].borrar_valor();

	//si no se ha podido borrar, deshago el push para que no se quede guardada la jugada
	if (_tablero[fila][columna].valor() != 0)
		undo();
}

bool sudoku::finalizado() const{

	bool hecho = true;

	for (int i = 0; i < 9 && hecho; i++)
		for (int j = 0; j < 9 && hecho; j++)
			if (!_tablero[i][j].valida())
				hecho = false;

	return hecho;
}

list<unsigned int> sudoku::opciones(const unsigned int &fila, const unsigned int &columna) const{
	set<unsigned int> setaux = _tablero[fila][columna].opciones();
	list<unsigned int> listaux;
	set<unsigned int>::iterator it;

	for (it = setaux.begin(); it != setaux.end(); it++)
		listaux.push_back(*it);

	return listaux;
}

bool sudoku::nueva_opcion(const unsigned int &fila, const unsigned int &columna, const unsigned int &valor){

	bool hecho = false;
	if (es_factible (fila, columna, valor) && valor < 10 && valor > 0){
		if (_tablero[fila][columna].opciones().find(valor) == _tablero[fila][columna].opciones().end()){
			list<pair<pair<unsigned int, unsigned int>, celda> > lista;
			Add_Celda (lista, fila, columna);
			Add_Lista (lista);
		}
		hecho = _tablero[fila][columna].nueva_opcion(valor);
	}
	return hecho;
}

bool sudoku::borrar_opcion(const unsigned int &fila, const unsigned int &columna, const unsigned int &valor){
	if (valor < 10 && valor > 0 && _tablero[fila][columna].opciones().find(valor) != _tablero[fila][columna].opciones().end()){
		list<pair<pair<unsigned int, unsigned int>, celda> > lista;
		Add_Celda (lista, fila, columna);
		Add_Lista (lista);
	}
	return _tablero[fila][columna].borrar_opcion(valor);
}

const celda & sudoku::valor(const unsigned int &fila, const unsigned int &columna) const{
	return _tablero[fila][columna];
}

bool sudoku::es_factible(const unsigned int &fila, const unsigned int &columna, const unsigned int &valor) const{

	bool factible = true;

	if (valor > 9 || valor < 1 || _tablero[fila][columna].valida())
		factible = false;

	else {
		//buscamos en la fila
		for (int j = 0; j < 9 && factible; j++)
			if (_tablero[fila][j].valor() == valor)
				factible = false;
	
		//buscamos en la columna
		for (int i = 0; i < 9 && factible; i++)
			if (_tablero[i][columna].valor() == valor)
				factible = false;

		//buscamos en su cuadro
		int cuadrante_i = (fila / 3);
		int cuadrante_j = (columna / 3);

		for (int i = (cuadrante_i*3); i < ((cuadrante_i*3)+3) && factible; i++)
			for (int j = (cuadrante_j*3); j < ((cuadrante_j*3)+3); j++)
				if (_tablero[i][j].valor() == valor)
					factible = false;
	}

	return factible;
}

bool sudoku::undo(){

	bool hecho = false;
	
	if (!_jugadas.empty()){

		list<pair<pair<unsigned int, unsigned int>, celda> > lista =_jugadas.top();
		list<pair<pair<unsigned int, unsigned int>, celda> >::iterator it;

		for (it = lista.begin(); it != lista.end(); it++)
			_tablero[(*it).first.first][(*it).first.second] = (*it).second;

		_jugadas.pop();
		hecho = true;
	}
	return hecho;
}

ostream& operator<<(ostream& os, const sudoku& c){

	os <<endl<<endl<< "        /*******  Sudoku  *******/";
	for (int i = 0; i < 9; i++){
		os << "        ";
		if (i%3 == 0)
			os << endl<< "        ";
		for (int j = 0; j < 9; j++){
			if (j%3 == 0)
				os << "  ";
			os << c.valor(i,j) << " ";
		}
		os << endl;
	}
	return os;
}
