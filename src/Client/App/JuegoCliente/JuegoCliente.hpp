#ifndef SRC_CLIENT_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_
#define SRC_CLIENT_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_

#include <queue>
#include <map>
#include <string>
#include <list>
#include <SDL2/SDL.h>
using namespace std;

#include "src/Utils/Utils.hpp"

class JuegoCliente{

	public:
		JuegoCliente(int cantidadJugadores,jugador_t jugadores[],int idPropio,int anchoPantalla,int altoPantalla,
                        podio_t podios[], unsigned short topePodios, podio_t podioPuntosTotales);
		~JuegoCliente() = default;

		void agregarRonda(info_ronda_t ronda);
		void actualizar();
		map<int,jugador_t> obtenerJugadores();
		list<entidad_t> obtenerEnemigos();
		list<entidad_t> obtenerBloques();
		list<entidad_t> obtenerMonedas();
        list<entidad_t> obtenerTuberias();
        list<efecto_t> obtenerEfectos();
        list<entidad_t> obtenerPozos();
        SDL_Rect rectanguloCamara{};
		int obtenerTiempoFaltante() const;
		int obtenerMundoActual() const;
		int obtenerNivelesJugados() const ;
		int obtenerIDPropio() const;
		SDL_Rect obtenerCamara() const;
		bool ganaronElJuego() const;
		bool perdieronElJuego() const;
        podio_t obtenerPodioPuntosAcumulados();
        vector<podio_t> obtenerPodios();
        bool hayQueMostrarPuntosDeNivel; //TODO: esto no tiene que quedar asi, es para avisar cambio de nivel al dibujador    void agregarNivel(nivel_t nivel);
        void agregarNivel(nivel_t nivel);

    private:
        bool enRango(int posX, int w) const;
		queue<info_ronda_t> rondas;
		map<int,jugador_t> jugadores;
		list<entidad_t> bloques;
        list<entidad_t> ladrillos;
        list<entidad_t> pozos;
		list<entidad_t> enemigos;
		list<entidad_t> monedas;
        list<entidad_t> tuberias;
        list<efecto_t> efectos;
        vector<podio_t> podios;
        podio_t podioPuntosTotales{};
		int cantidadJugadores;
		int idPropio;
		int anchoVista;
		int numeroMundo;
		int tiempoFaltante;
		bool ganaron;
		bool perdieron;
        bool hayQueCargarPodioNivel;
		int nivelesJugados;

        static void cargarLista(list<entidad_t>* listaACargar, entidad_t *vector, unsigned short tope);
};



#endif /* SRC_CLIENT_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_ */
