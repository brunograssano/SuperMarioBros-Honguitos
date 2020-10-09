#ifndef SRC_MODELO_JUEGO_H_
#define SRC_MODELO_JUEGO_H_

using namespace std;
#include <iostream>
#include "Mario.h"

class Juego{

	public:
		Juego* getInstance(){
			if(this->instanciaJuego==nullptr){ // TODO Ver si le pasamos el por defecto, o si lo sacamos directamente
				this->instanciaJuego = new Juego("a ver");
			}
			return this->instanciaJuego;
		}

		Juego* getInstance(string direccionConfiguracion){
			if(this->instanciaJuego==nullptr){
				this->instanciaJuego = new Juego(direccionConfiguracion);
			}
			return this->instanciaJuego;
		}

		~Juego(){
			// Se borran los niveles/vamos borrando a medida que se avanza?
			delete jugador;
		}

	private:
		Juego(string direccionConfiguracion){
			//Llamada al lector que nos va a dar los niveles

			jugador = new Mario();


		}

		Mario* jugador;
		Juego* instanciaJuego = nullptr;

};


#endif /* SRC_MODELO_JUEGO_H_ */
