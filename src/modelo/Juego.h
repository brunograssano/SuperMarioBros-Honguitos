#ifndef SRC_MODELO_JUEGO_H_
#define SRC_MODELO_JUEGO_H_

using namespace std;
#include <iostream>
#include <string>
#include "Mario.h"

class Juego{

	public:
		Juego(Juego &other) = delete;
		static Juego* getInstance();
		static Juego* getInstance(string direccionConfiguracion);
		Mario* obtenerMario();
		~Juego();

	private:
		Juego(string direccionConfiguracion){
			//Llamada al lector que nos va a dar los niveles

			jugador = new Mario();


		}

		Mario* jugador;
		static Juego* instanciaJuego;

};



#endif /* SRC_MODELO_JUEGO_H_ */
