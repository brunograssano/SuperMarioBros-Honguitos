#ifndef SRC_CLIENT_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_
#define SRC_CLIENT_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_

#include <queue>
#include <map>
#include <string>
#include <list>
using namespace std;

#include "../../../Utils/Utils.hpp"

class JuegoCliente{

	public:
		JuegoCliente(int cantidadJugadores,jugador_t jugadores[MAX_JUGADORES],int idPropio,int anchoPantalla);
		~JuegoCliente() = default;

		void agregarRonda(info_ronda_t ronda);
		void actualizar();
		map<int,jugador_t> obtenerJugadores();
		list<enemigo_t> obtenerEnemigos();
		list<bloque_t> obtenerBloques();
		list<moneda_t> obtenerMonedas();
        list<tuberia_t> obtenerTuberias();
        list<efecto_t> obtenerEfectos();
        list<pozo_t> obtenerPozos();
		int obtenerTiempoFaltante() const;
		int obtenerMundoActual() const;
		int obtenerIDPropio() const;
		int obtenerPosXCamara() const;
		bool ganaronElJuego() const;
		bool perdieronElJuego() const;
        void agregarNivel(nivel_t nivel);
    private:
        bool enRango(int posX, int w) const;
		queue<info_ronda_t> rondas;
		map<int,jugador_t> jugadores;
		list<bloque_t> bloques;
        list<bloque_t> ladrillos;
        list<pozo_t> pozos;
		list<enemigo_t> enemigos;
		list<moneda_t> monedas;
        list<tuberia_t> tuberias;
        list<efecto_t> efectos;
		int cantidadJugadores;
		int idPropio;

		int anchoVista;
		int numeroMundo;
		int tiempoFaltante;
		int posXCamara;
		bool ganaron;
		bool perdieron;


};



#endif /* SRC_CLIENT_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_ */
