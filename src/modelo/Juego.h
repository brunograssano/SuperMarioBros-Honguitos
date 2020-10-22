#ifndef SRC_MODELO_JUEGO_H_
#define SRC_MODELO_JUEGO_H_

using namespace std;
#include "Nivel.h"
#include <list>
#include <iostream>
#include <string>
#include "Mario.h"



class Juego{

	public:
		Juego(Juego &other) = delete;
		static Juego* getInstance();
		static Juego* getInstance(list<Nivel*> archivoLeido);
		string obtenerDireccionFondoNivelActual();
		void actualizarPosicionesEnemigos();
		list<Enemigo*> obtenerEnemigos();
		list<Plataforma*> obtenerPlataformas();
		list<Moneda*> obtenerMonedas();
		Mario* obtenerMario();
		int obtenerTiempoDelNivel();
		int obtenerPuntuacionJugador();
		int obtenerMundoActual();

		~Juego();

	private:
		Juego(list<Nivel*> nivelesLector){

			jugador = new Mario();
			niveles = nivelesLector;

			for (auto const& nivel : niveles) {
			    nivel->inicializarPosicionEnemigo();
			}
		}

		list<Nivel*> niveles;
		Mario* jugador;
		static Juego* instanciaJuego;

};



#endif /* SRC_MODELO_JUEGO_H_ */
