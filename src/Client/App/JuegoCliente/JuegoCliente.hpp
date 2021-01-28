#ifndef SRC_CLIENT_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_
#define SRC_CLIENT_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_

#include <queue>
#include <map>
#include <string>
#include <list>
#include <SDL2/SDL.h>

#include "src/Utils/Utils.hpp"

class JuegoCliente{

	public:
		JuegoCliente(int cantidadJugadores,jugador_t jugadores[],int idPropio,int anchoPantalla,int altoPantalla,
                        podio_t podios[], unsigned short topePodios, podio_t podioPuntosTotales);
		~JuegoCliente() = default;

		void agregarRonda(info_ronda_t ronda);
		void actualizar();
        std::map<int,jugador_t> obtenerJugadores();
        std::list<entidad_t> obtenerEnemigos();
        std::list<entidad_t> obtenerBloques();
        std::list<entidad_t> obtenerMonedas();
        std::list<entidad_t> obtenerTuberias();
        std::list<entidad_t> obtenerEfectos();
        std::list<entidad_t> obtenerPozos();
        SDL_Rect rectanguloCamara{};
		int obtenerTiempoFaltante() const;
		int obtenerMundoActual() const;
		int obtenerNivelesJugados() const ;
		int obtenerIDPropio() const;
		SDL_Rect obtenerCamara() const;
		bool ganaronElJuego() const;
		bool perdieronElJuego() const;
        podio_t obtenerPodioPuntosAcumulados();
        std::vector<podio_t> obtenerPodios();
        bool hayQueMostrarPuntosDeNivel; //TODO: esto no tiene que quedar asi, es para avisar cambio de nivel al dibujador    void agregarNivel(nivel_t nivel);
        void agregarNivel(nivel_t nivel);

    private:
        bool enRango(int posX, int w) const;
        static void cargarLista(std::list<entidad_t>* listaACargar, entidad_t *vector, unsigned short tope);
        std::queue<info_ronda_t> rondas;
        std::map<int,jugador_t> jugadores;
        std::list<entidad_t> bloques;
        std::list<entidad_t> ladrillos;
        std::list<entidad_t> pozos;
        std::list<entidad_t> enemigos;
        std::list<entidad_t> monedas;
        std::list<entidad_t> tuberias;
        std::list<entidad_t> efectos;
        std::vector<podio_t> podios;
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
};



#endif /* SRC_CLIENT_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_ */
