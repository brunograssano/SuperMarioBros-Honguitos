#ifndef SRC_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_
#define SRC_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_


using namespace std;
#include <map>
#include <string>
#include <list>


#include "../../Utils.hpp"

class JuegoCliente{

	public:
		JuegoCliente(int cantidadJugadores,jugador_t jugadores[MAX_JUGADORES],int idPropio);
		~JuegoCliente();

		map<int,jugador_t> obtenerJugadores();
		list<enemigo_t> obtenerEnemigos();
		list<bloque_t> obtenerBloques();
		list<moneda_t> obtenerMonedas();
		int obtenerTiempoFaltante();
		int obtenerMundoActual();
		int obtenerIDPropio();

	private:
		map<int,jugador_t> jugadores;
		list<bloque_t> bloques;
		list<enemigo_t> enemigos;
		list<moneda_t> monedas;
		int cantidadJugadores;
		int idPropio;

		int numeroMundo;
		int tiempoFaltante;
		int tiempoDeInicio;
};



#endif /* SRC_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_ */
