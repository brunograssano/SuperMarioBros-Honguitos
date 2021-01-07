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
				nivel->inicializar();
			}

            hanGanado = false;
		}
        bool todosEnLaMeta();
        void avanzarNivel(Camara* camara/*TODO: Sacar estos parametros*/);
        void sumarPuntosAJugadores(int puntos);

        bool hanGanado;
        map<int,Mario*> jugadores;
		list<Nivel*> niveles;

        int obtenerTiempoRestante();
        int obtenerMundoActual();

		static Juego* instanciaJuego;

public:
		Juego(Juego &other) = delete;
        ~Juego();
		static Juego* getInstance();
		static Juego* getInstance(list<Nivel*> archivoLeido,int cantJugadores);

		void iniciar();

        bool ganaron();
        bool perdieron();
        bool hayConectados();

		void actualizarModelo(Camara* camara/*TODO: Sacar este parametros*/);
        void actualizarJugador(unsigned short idJugador, entrada_usuario_t entradaUsuario);

		void desconectarJugador(int idJugador);
		void conectarJugador(int idMarioConectandose);

        info_partida_t obtenerInfoPartida(map<int,string> mapaIDNombre,int IDJugador, Camara* camara);
        info_ronda_t obtenerInfoRonda(map<int,string> mapaIDNombre, Camara* camara);

};



#endif /* SRC_SERVER_MODELO_JUEGO_HPP_ */
