
#ifndef SRC_TIPOLOG_H_
#define SRC_TIPOLOG_H_
#include <string>
#include <iostream>
using namespace std;


class TipoLog{

public:
	//DEBUG//
	virtual void mostrarPosicionMario(int coordenadaX, int coordenadaY){
		cout<<"La posicion de mario es: ("<<coordenadaX<<","<<coordenadaY<<")"<<endl;
	}

	//INFO//
	virtual void seCargaUnaTexturaDesde(string rutaTextura){
		cout<<"Se carga una textura desde: "<< rutaTextura <<endl;
	}

	//ERRORES//
	virtual void huboUnErrorAlInicializar(){
		cout<<"Hubo un error en la inicializacion del programa"<<endl;
	}

	virtual void huboUnErrorEnLaCargaDeLaTextura(string rutaTextura){
		cout<<"Hubo un error en la carga de la siguiente textura: "<< rutaTextura <<endl;
	}



};




#endif /* SRC_TIPOLOG_H_ */
