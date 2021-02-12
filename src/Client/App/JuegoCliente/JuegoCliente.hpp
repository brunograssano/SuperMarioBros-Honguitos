#ifndef SRC_CLIENT_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_
#define SRC_CLIENT_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_

#include <map>
#include <string>
#include <list>
#include <SDL2/SDL.h>

#include "src/Utils/Utils.hpp"
#include "src/Utils/ColaBloqueante.hpp"

class JuegoCliente{

	public:
		JuegoCliente(int cantidadJugadores,jugador_t jugadores[],int idPropio,int anchoPantalla,int altoPantalla,
                        podio_t podios[], unsigned short topePodios, podio_t podioPuntosTotales);
		~JuegoCliente() = default;

		void agregarRonda(info_ronda_t ronda);
		void actualizar();
        std::map<int,jugador_t> obtenerJugadores();

		int obtenerTiempoFaltante() const;
		int obtenerMundoActual() const;
		int obtenerNivelesJugados() const ;
		int obtenerIDPropio() const;
		SDL_Rect obtenerCamara() const;
		bool ganaronElJuego() const;
		bool perdieronElJuego() const;
		void dejarDeMostrarPuntosNivel();
		bool hayQueMostrarPuntosNivel();
        podio_t obtenerPodioPuntosAcumulados();
        std::vector<podio_t> obtenerPodios();
        void agregarNivel(nivel_t nivel);
        void agregarPodios(ultimos_podios_t ultimos_podios);

        std::list<entidad_t> obtenerEntidad(int claveEntidad);

private:
        bool enRango(int posX, int w) const;
        static void cargarLista(std::list<entidad_t>* listaACargar, entidad_t *vector, unsigned short tope);
        static void crearListaDeFondoPozo(std::list<entidad_t>* listaACargar, entidad_t pozos[MAX_POZOS], uint8_t topePozos);
        BlockingQueue<info_ronda_t> rondas;
        std::map<int,jugador_t> jugadores;
        std::map<int,std::list<entidad_t>> entidades;
        std::list<entidad_t> ladrillos;
        std::vector<podio_t> podios;
        podio_t podioPuntosTotales{};
        SDL_Rect rectanguloCamara{};
		int cantidadJugadores;
		int idPropio;
		int anchoVista;
		int numeroMundo;
		int tiempoFaltante;
		bool ganaron;
		bool perdieron;
        bool hayQueCargarPodioNivel;
        bool hayQueMostrarPuntosDeNivel;
		int nivelesJugados;
};



#endif /* SRC_CLIENT_APP_JUEGOCLIENTE_JUEGOCLIENTE_HPP_ */
