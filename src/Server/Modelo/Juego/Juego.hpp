#ifndef SRC_SERVER_MODELO_JUEGO_HPP_
#define SRC_SERVER_MODELO_JUEGO_HPP_


class Mario;
#include "src/Server/Modelo/Juego/Mario/Mario.hpp"
#include "src/Server/Modelo/Juego/Nivel/Nivel.hpp"
#include "Camara/Camara.hpp"

class Juego{

	private:
		Juego(std::list<Nivel*> nivelesLector, int cantJugadores, int alto_pantalla, int ancho_pantalla);
        void avanzarNivel();

        Camara camara;
        bool hanGanado;
        std::map<int,Mario*> jugadores;
        std::list<Nivel*> niveles;
		podio_t podioAcumulado{};
        std::vector<podio_t> podios;
        bool seGuardoUltimoPodio;

        int obtenerTiempoRestante();
        int obtenerMundoActual();
        bool murieronTodos();
		static Juego* instanciaJuego;

    public:
		Juego(Juego &other) = delete;
        ~Juego();
		static Juego* getInstance();
		static Juego* getInstance(std::list<Nivel*> archivoLeido,int cantJugadores, int alto_pantalla, int ancho_pantalla);

		void iniciar();

        bool ganaron() const;
        bool perdieron();
        bool hayConectados();

		void actualizarModelo();
        void actualizarJugador(unsigned short idJugador, entrada_usuario_t entradaUsuario);

		void desconectarJugador(int idJugador);
		void conectarJugador(int idMarioConectandose);

        info_partida_t obtenerInfoPartida(std::map<int,std::string> mapaIDNombre,int IDJugador);
        info_ronda_t obtenerInfoRonda();
        nivel_t serializarNivel();
        podio_t obtenerUltimoPodio();
        podio_t obtenerPodioAcumulado();

        int cantidadDeNiveles();
        void guardarPodio(Podio *podio);
        void revisarSiGanaronElJuego();
};



#endif /* SRC_SERVER_MODELO_JUEGO_HPP_ */
