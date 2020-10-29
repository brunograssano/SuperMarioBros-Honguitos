#ifndef SRC_MODELO_JUEGO_HPP_
#define SRC_MODELO_JUEGO_HPP_

using namespace std;
#include "Nivel.hpp"
#include <list>
#include <iostream>
#include <string>

class Mario;
#include "Mario.hpp"

class Juego{

	private:
		Mario* jugador;
		Juego(list<Nivel*> nivelesLector){

			inicializar();
			niveles = nivelesLector;

			for (auto const& nivel : niveles) {
				nivel->inicializarPosicionesOcupadasPorBloques();
				nivel->inicializarPosicionMonedas();
				nivel->inicializarPosicionEnemigo();
			}
		}

		list<Nivel*> niveles;
		void inicializar();
		static Juego* instanciaJuego;
	public:
		Juego(Juego &other) = delete;
		static Juego* getInstance();
		static Juego* getInstance(list<Nivel*> archivoLeido);

		void avanzarNivel();
		void actualizarPosicionesEnemigos();
		void sumarPuntosAJugadores(int puntos);
		bool quedaSoloUnNivel();

		string obtenerDireccionFondoNivelActual();
		list<Enemigo*> obtenerEnemigos();
		list<Plataforma*> obtenerPlataformas();
		list<Moneda*> obtenerMonedas();
		Mario* obtenerMario();
		int obtenerTiempoDelNivel();
		int obtenerPuntuacionJugador();
		int obtenerMundoActual();
		int obtenerPuntoBanderaFinActual();

		~Juego();

};



#endif /* SRC_MODELO_JUEGO_HPP_ */
