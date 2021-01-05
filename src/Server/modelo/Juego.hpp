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
#include "Camara/Camara.hpp"
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

            hanGanado = false;
		}
        bool todosEnLaMeta();
        void avanzarNivel(Camara* camara/*TODO: Sacar estos parametros*/);
        void sumarPuntosAJugadores(int puntos);

        bool hanGanado;
        map<int,Mario*> jugadores;
		list<Nivel*> niveles;

		static Juego* instanciaJuego;

public:
		Juego(Juego &other) = delete;
		static Juego* getInstance();
		static Juego* getInstance(list<Nivel*> archivoLeido,int cantJugadores);

		list<Nivel*> obtenerNiveles();
		void iniciar();
        bool ganaron();
        bool perdieron();
		void actualizarModelo(Camara* camara/*TODO: Sacar estos parametros*/);
        void actualizarJugador(unsigned short idJugador, entrada_usuario_t entradaUsuario);
		void desconectarJugador(int idJugador);
		void conectarJugador(int idMarioConectandose);

        list<Enemigo*> obtenerEnemigos();
		list<Plataforma*> obtenerPlataformas();
		list<Moneda*> obtenerMonedas();
        list<Tuberia*> obtenerTuberias();
		map<int,Mario*> obtenerMarios();
		int obtenerTiempoRestante();
        int obtenerMundoActual();
		~Juego();

};



#endif /* SRC_SERVER_MODELO_JUEGO_HPP_ */
