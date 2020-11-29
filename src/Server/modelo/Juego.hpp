#ifndef SRC_SERVER_MODELO_JUEGO_HPP_
#define SRC_SERVER_MODELO_JUEGO_HPP_

using namespace std;
#include "../modelo/Nivel.hpp"
#include <list>
#include <map>
#include <iostream>
#include <string>

class Mario;
#include "../modelo/Mario.hpp"

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

		void actualizarMonedas();
		void actualizarPosicionesEnemigos();


	public:
		Juego(Juego &other) = delete;
		static Juego* getInstance();
		static Juego* getInstance(list<Nivel*> archivoLeido,int cantJugadores);

		list<Nivel*> obtenerNiveles();
		void avanzarNivel();
		void actualizarModelo();
		void sumarPuntosAJugadores(int puntos);
		bool quedaSoloUnNivel();
		void desconectarJugador(int idJugador);

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



#endif /* SRC_SERVER_MODELO_JUEGO_HPP_ */
