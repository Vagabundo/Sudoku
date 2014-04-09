#include "sudoku.h"

using namespace std;

/********* Declaración de funciones de main (para ahorrar código y hacerlo más legible) ***********/

//funcion que muestra el sudoku y las opciones almacenadas, y le pide la opcion que desea al usuario
void Pedir_opcion(int &opcion, const sudoku &sud);

//función que le pide la fila, la columna y el valor al usuario
void FCyV(int &fila, int &columna, int &valor);

//función que le pide la fila y la columna al usuario
void FyC(int &fila, int &columna);

//muestra las opciones almacenadas en cada casilla
void MostrarOpciones(const sudoku &sud);	

int main (int argc, char *argv[]){

	sudoku sud (argv[1]);
	int fila, columna, valor;
	int opcion = 1;

	cout <<endl<<endl<<"Bienvenido al juego de Sudoku. Por Roberto José del Río Rodríguez";

	while (opcion != 7 and !sud.finalizado()){

		Pedir_opcion(opcion, sud);

		if (opcion < 1 or opcion > 7)
			cout <<endl<<"Elige una opción entre el 1 y el 7"<<endl;

		switch (opcion){
			case 1:

				FCyV(fila, columna, valor);

				if (sud.nueva_opcion(fila,columna,valor))
					cout<<endl<<"Opcion agregada con éxito";
				else
					cout<<endl<<"No se ha podido agregar el valor "<<valor<<" a las opciones";
				break;

			case 2:

				FCyV(fila, columna, valor);

				if (sud.borrar_opcion(fila,columna,valor))
					cout<<endl<<"Opcion borrada con éxito";
				else
					cout<<endl<<"No se ha podido borrar el valor "<<valor<<" de las opciones";
				break;

			case 3:

				FCyV(fila, columna, valor);

				if (sud.fijar_valor(fila,columna,valor))
					cout<<endl<<"Valor fijado con éxito";
				else
					cout<<endl<<"No se ha podido fijar el valor "<<valor<<" a la casilla";
				break;

			case 4:

				FyC(fila, columna);

				sud.borrar_valor(fila,columna);
				bool borrado;
				borrado = false;

				//estas lineas de código son para comprobar que se ha podido borrar,
				//es decir, que la celda no es fija.
				//Para ello intentamos meter cualquier valor de 1 a 9. Si no se puede, es que es fija
				for (int i = 1; i < 10 && !borrado; i++)
					if (sud.fijar_valor(fila,columna,i)){
						sud.undo();
						borrado = true;
					}

				if (borrado)
					cout<<endl<<"Valor borrado con éxito";
				else
					cout<<endl<<"No se ha podido borrar el valor";
					
				break;

			case 5:

				FCyV(fila, columna, valor);

				if (sud.es_factible(fila,columna,valor))
					cout<<endl<<"Es factible";
				else
					cout<<endl<<"No es factible";
				break;


			case 6:

				if (sud.undo())
					cout<<endl<<"Jugada deshecha con éxito. Piénsate mejor la próxima jugada";
				else
					cout<<endl<<"No se ha podido deshacer la jugada.";
				break;
		}
	}

	if (sud.finalizado()){
		cout <<sud;
		cout <<endl<<endl<<endl <<"          ¡¡Sudoku completado!!";
		cout <<endl <<"               Enhorabuena";
		cout <<endl <<"         Ahora a por el siguiente";
	}
	else
		cout <<endl <<"Gracias por intentarlo. Suerte para la próxima :)";

	cout <<endl<<endl;
}

/**************** Implementación de funciones de main ****************/

//funcion que muestra el sudoku y las opciones almacenadas, y le pide la opcion que desea al usuario
void Pedir_opcion(int &opcion, const sudoku &sud){

	MostrarOpciones(sud);
	cout << sud;

	cout <<endl<<endl<<"Introduzca la opcion que desee:"<<endl<<endl;
	cout << "1 - Agregar opcion a una celda." <<endl;
	cout << "2 - Borrar opcion de una celda." <<endl;
	cout << "3 - Fijar valor a una celda." <<endl;
	cout << "4 - Borrar valor de una celda." <<endl;
	cout << "5 - Verificar factible." <<endl;
	cout << "6 - Deshacer." <<endl;
	cout << "7 - Salir." <<endl<<endl;

	cout << "Opcion: ";
	cin >> opcion;
}


//función que le pide la fila, la columna y el valor al usuario
void FCyV(int &fila, int &columna, int &valor){

	FyC (fila, columna);
	cout <<endl<< "Introduzca el valor: ";
	cin >> valor;
}	

//función que le pide la fila y la columna al usuario
void FyC(int &fila, int &columna){

	cout <<endl<< "Introduzca la fila de la celda: ";
	cin >> fila; fila--;
	cout <<endl<< "Introduzca la columna de la celda: ";
	cin >> columna; columna--;
}

//muestra la opciones de cada casilla
void MostrarOpciones(const sudoku &sud){

	cout<<endl<<endl<< "/*************  Opciones  *************/"<<endl<<endl;

	list <unsigned int>::iterator it;
	list <unsigned int> aux;

	for (int i = 0; i < 9; i++){
		cout << "   ";
		if (i%3 == 0)
			cout << endl <<"   ";
		for (int j = 0; j < 9; j++){
			if (j%3 == 0)
				cout << "  ";
			aux = sud.opciones(i,j);
			cout << "[ ";
			for (it = aux.begin(); it != aux.end(); it++)
				cout << *it <<" ";

			cout << "]";
		}
		cout<<endl;
	}
}
				
	
	
