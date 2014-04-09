#include "celda.h"

using namespace std;

celda::celda(){
	_fija = false;
	_valor = 0;
}

celda::~celda(){

}

bool celda::fijar_valor(const unsigned int &dato, const bool &fija){

	bool hecho = false;

	if (_fija)
		hecho = false;

	else{
		_valor = dato;
		_fija = fija;
		hecho = true;
	}

	return hecho;
}


void celda::borrar_valor(){
	if (_fija == false)
	_valor = 0;
}

unsigned int celda::valor() const{
	return _valor;
}

bool celda::valida() const{

	bool hecho = false;

	if (_valor > 0)
		hecho = true;
	else
		hecho = false;

	return hecho;
}

bool celda::nueva_opcion(const unsigned int &dato){

		bool hecho = false;

	if (_opciones.find(dato) != _opciones.end())
		hecho = false;
	
	else {
		_opciones.insert(dato);
		hecho = true;
	}

	return hecho;
}

bool celda::borrar_opcion(const unsigned int &dato){

	bool hecho = false;

	if (_opciones.find(dato) != _opciones.end()){
		_opciones.erase(dato);
		hecho = true;
	}
	else
		hecho = false;

	return hecho;

}

const set<unsigned int> & celda::opciones() const{
	return _opciones;
}

celda& celda::operator=(const celda &otra){
	_fija = otra._fija;
	_valor = otra._valor;
	_opciones = otra._opciones;
}	

ostream& operator<<(ostream& os, const celda& c){
	if (c.valida())
		os << c.valor();
	else
		os << "_";

	return os;
}
