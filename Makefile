################### Todo ####################

all: mrproper juego

####### Compilación de los objetos ##########

celda.o: celda.h celda.cpp
	@g++ -c -Iinclude celda.cpp -o celda.o
	@echo creando objeto celda.o

sudoku.o: sudoku.h sudoku.cpp
	@g++ -c -Iinclude sudoku.cpp -o sudoku.o
	@echo creando objeto sudoku.o

juego.o: juego.cpp
	@g++ -c -Iinclude juego.cpp -o juego.o
	@echo creando objeto juego.o

###### Compilación del ejecutabe juego ######

juego: celda.o sudoku.o juego.o
	@g++ celda.o sudoku.o juego.o -o juego
	@echo creando ejecutable juego

##### Limpieza de los objeto anteriores #####

mrproper: 
	@\rm -rf juego *.o
	@echo borrando objetos y ejecutable juego


