#ifndef SRC_MODELO_JUEGO_H_
#define SRC_MODELO_JUEGO_H_

using namespace std;
#include "Nivel.h"
#include <queue>
#include <list>
#include <iostream>
#include <string>
#include "Mario.h"

#include "Enemigos/Goomba.h"

class Juego{

	public:
		Juego(Juego &other) = delete;
		static Juego* getInstance();
		static Juego* getInstance(string direccionConfiguracion);

		void actualizarPosicionesEnemigos();
		list<Enemigo*> obtenerEnemigos();
		Mario* obtenerMario();

		~Juego();

	private:
		Juego(string direccionConfiguracion){
			//Llamada al lector que nos va a dar los niveles

			jugador = new Mario();

			//PRUEBA CON UN NIVEL
			Nivel* unNivel = new Nivel(0,"0",0,0);
			unNivel->agregarEnemigo(new Goomba("a"));
			niveles.push(unNivel);

		}

		queue<Nivel*> niveles;
		Mario* jugador;
		static Juego* instanciaJuego;

};



#endif /* SRC_MODELO_JUEGO_H_ */
