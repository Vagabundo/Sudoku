/*
 * celda.h
 *
 *  Created on: 15/02/2010
 *      Author: rromero
 */

#ifndef CELDA_H_
#define CELDA_H_

#include <set>
#include <iostream>

using namespace std;

class celda {
	public:
		celda();
		~celda();
		bool fijar_valor(const unsigned int &dato, const bool &fija = false);
		void borrar_valor();
		unsigned int valor() const;
		bool valida() const;
		bool nueva_opcion(const unsigned int &dato);
		bool borrar_opcion(const unsigned int &dato);
		const set<unsigned int> & opciones() const;

		celda& operator=(const celda &otra);
	private:
		bool 		      _fija;
		unsigned int	  _valor;
		set<unsigned int> _opciones;
};

ostream& operator<<(ostream& os, const celda& c);

#endif /* CELDA_H_ */
