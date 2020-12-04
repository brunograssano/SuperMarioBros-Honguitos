#ifndef SRC_CLIENT_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_
#define SRC_CLIENT_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_


using namespace std;
#include <queue>
#include <map>
#include <string>
#include <list>


#include "../../../Utils/Utils.hpp"

class JuegoCliente{

	public:
		JuegoCliente(int cantidadJugadores,jugador_t jugadores[MAX_JUGADORES],int idPropio);
		~JuegoCliente();

		void agregarRonda(info_ronda_t ronda);
		void actualizar();
		map<int,jugador_t> obtenerJugadores();
		list<enemigo_t> obtenerEnemigos();
		list<bloque_t> obtenerBloques();
		list<moneda_t> obtenerMonedas();
		int obtenerTiempoFaltante();
		int obtenerMundoActual();
		int obtenerIDPropio();
		int obtenerPosXCamara();
		bool ganaronElJuego();
		bool perdieronElJuego();

	private:
		queue<info_ronda_t> rondas;
		map<int,jugador_t> jugadores;
		list<bloque_t> bloques;
		list<enemigo_t> enemigos;
		list<moneda_t> monedas;
		int cantidadJugadores;
		int idPropio;

		int numeroMundo;
		int tiempoFaltante;
		int posXCamara;
		bool ganaron;
		bool perdieron;
};



#endif /* SRC_CLIENT_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_ */
