#ifndef SRC_SERVER_MODELO_JUEGO_HPP_
#define SRC_SERVER_MODELO_JUEGO_HPP_

#include "../modelo/Nivel.hpp"
#include <list>
#include <map>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

class Mario;
#include "src/Server/modelo/Mario/Mario.hpp"
#include "src/Utils/Contador.hpp"
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
        bool quedaSoloUnNivel();
        bool todosEnLaMeta();
        void avanzarNivel(SDL_Rect* camara, Contador* contador /*TODO: Sacar estos parametros*/);
        void sumarPuntosAJugadores(int puntos);


        map<int,Mario*> jugadores;
		list<Nivel*> niveles;

		static Juego* instanciaJuego;

public:
		Juego(Juego &other) = delete;
		static Juego* getInstance();
		static Juego* getInstance(list<Nivel*> archivoLeido,int cantJugadores);

		list<Nivel*> obtenerNiveles();
        bool ganaron();
		void actualizarModelo(SDL_Rect* camara, Contador* contador/*TODO: Sacar estos parametros*/);
        void actualizarJugador(unsigned short idJugador, entrada_usuario_t entradaUsuario);
		void desconectarJugador(int idJugador);
		void conectarJugador(int idMarioConectandose);

        list<Enemigo*> obtenerEnemigos();
		list<Plataforma*> obtenerPlataformas();
		list<Moneda*> obtenerMonedas();
        list<Tuberia*> obtenerTuberias();
		map<int,Mario*> obtenerMarios();
        int obtenerMundoActual();
		~Juego();

};



#endif /* SRC_SERVER_MODELO_JUEGO_HPP_ */
