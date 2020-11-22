#ifndef SRC_MODELO_JUEGO_HPP_
#define SRC_MODELO_JUEGO_HPP_

using namespace std;
#include "Nivel.hpp"
#include <list>
#include <map>
#include <iostream>
#include <string>

class Mario;
#include "Mario.hpp"

class Juego{

	private:

		void inicializar(int cantJugadores);

		Juego(list<Nivel*> nivelesLector, int cantJugadores){

			inicializar(cantJugadores);
			for(int i = 0; i < cantJugadores; i++){
				jugadores[i] = new Mario(i);
			}
			niveles = nivelesLector;

			for (auto const& nivel : niveles) {
				nivel->inicializarPosicionesOcupadasPorBloques();
				nivel->inicializarPosicionMonedas();
				nivel->inicializarPosicionEnemigo();
			}
		}

		map<int,Mario*> jugadores;
		list<Nivel*> niveles;

		static Juego* instanciaJuego;
	public:
		Juego(Juego &other) = delete;
		static Juego* getInstance();
		static Juego* getInstance(list<Nivel*> archivoLeido,int cantJugadores);

		list<Nivel*> obtenerNiveles();
		void avanzarNivel();
		void actualizarPosicionesEnemigos();
		void sumarPuntosAJugadores(int puntos);
		bool quedaSoloUnNivel();

		string obtenerDireccionFondoNivelActual();
		list<Enemigo*> obtenerEnemigos();
		list<Plataforma*> obtenerPlataformas();
		list<Moneda*> obtenerMonedas();
		map<int,Mario*> obtenerMarios();
		int obtenerTiempoDelNivel();
		int obtenerPuntuacionJugador();
		int obtenerMundoActual();
		int obtenerPuntoBanderaFinActual();

		~Juego();

};



#endif /* SRC_MODELO_JUEGO_HPP_ */
