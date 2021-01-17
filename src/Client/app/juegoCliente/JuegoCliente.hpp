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
		JuegoCliente(int cantidadJugadores,jugador_t jugadores[],int idPropio,int anchoPantalla, podio_t podios[], unsigned short topePodios, podio_t podioPuntosTotales);
		~JuegoCliente() = default;

		void agregarRonda(info_ronda_t ronda);
		void actualizar();
		map<int,jugador_t> obtenerJugadores();
		list<enemigo_t> obtenerEnemigos();
		list<bloque_t> obtenerBloques();
		list<moneda_t> obtenerMonedas();
        list<tuberia_t> obtenerTuberias();
        list<efecto_t> obtenerEfectos();
		int obtenerTiempoFaltante() const;
		int obtenerMundoActual() const;
		int obtenerNivelesJugados() ;
		int obtenerIDPropio() const;
		int obtenerPosXCamara() const;
		bool ganaronElJuego() const;
		bool perdieronElJuego() const;
		podio_t obtenerPodioPuntosAcumulados();
        vector<podio_t> obtenerPodios();
        bool hayQueMostrarPuntosDeNivel; //TODO: esto no tiene que quedar asi, es para avisar cambio de nivel al dibujador
        void agregarNivel(nivel_t nivel);

private:
    bool enRango(int posX) const;
		queue<info_ronda_t> rondas;
		map<int,jugador_t> jugadores;
		list<bloque_t> bloques;
        list<bloque_t> ladrillos;
        list<pozo_t> pozos;
		list<enemigo_t> enemigos;
		list<moneda_t> monedas;
        list<tuberia_t> tuberias;
        list<efecto_t> efectos;
        vector<podio_t> podios;
        podio_t podioPuntosTotales;
		int cantidadJugadores;
		int idPropio;
		int anchoVista;
		int numeroMundo;
		int tiempoFaltante;
		int posXCamara;
		bool ganaron;
		bool perdieron;
        bool hayQueCargarPodioNivel;
		int nivelesJugados;
};



#endif /* SRC_CLIENT_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_ */
