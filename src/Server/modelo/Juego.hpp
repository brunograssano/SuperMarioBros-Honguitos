#ifndef SRC_SERVER_MODELO_JUEGO_HPP_
#define SRC_SERVER_MODELO_JUEGO_HPP_

using namespace std;
#include "../modelo/Nivel.hpp"
#include <list>
#include <map>
#include <iostream>
#include <string>
#include <utility>

class Mario;
#include "../modelo/Mario.hpp"

class Juego{

	private:

		void inicializar();

		Juego(list<Nivel*> nivelesLector, int cantJugadores){

            inicializar();
			for(int i = 0; i < cantJugadores; i++){
				jugadores[i] = new Mario(i);
			}
			niveles = std::move(nivelesLector);

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
		void actualizarModelo();
		void sumarPuntosAJugadores(int puntos);
		bool quedaSoloUnNivel();
		void desconectarJugador(int idJugador);
		void conectarJugador(int idMarioConectandose);

        list<Enemigo*> obtenerEnemigos();
		list<Plataforma*> obtenerPlataformas();
		list<Moneda*> obtenerMonedas();
        list<Tuberia*> obtenerTuberias();
		map<int,Mario*> obtenerMarios();
        int obtenerMundoActual();
		int obtenerPuntoBanderaFinActual();

		~Juego();

};



#endif /* SRC_SERVER_MODELO_JUEGO_HPP_ */
