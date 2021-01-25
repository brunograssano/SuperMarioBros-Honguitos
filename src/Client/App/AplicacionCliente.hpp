#ifndef SRC_APP_APP_HPP_
#define SRC_APP_APP_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>
#include <sstream>
using namespace std;

#include "Dibujadores/Dibujadores.hpp"
#include "JuegoCliente/JuegoCliente.hpp"
#include "CargadorTexturas.hpp"
#include "src/Utils/Constantes.hpp"
#include "src/Utils/Utils.hpp"
#include "../Cliente.hpp"

#include <map>

class App{

	protected:
		App(info_partida_t informacion, Cliente* cliente);
		static App* aplicacion;
		Dibujadores dibujador;
        void determinarMusica();
		JuegoCliente juegoCliente;
        bool comenzoElJuego;
        bool terminoElJuego;
        bool estaReproduciendoMusicaGanadores;
		bool presionoT;
		Cliente* cliente;

	public:
        ~App();
		App(App &other) = delete;
		static App *getInstance();
		static App *getInstance(info_partida_t informacion,Cliente* cliente);

		void actualizarServer(const Uint8 *keystate);
		void actualizar();
		void agregarRonda(info_ronda_t info_ronda);
        void agregarNivel(nivel_t nivel);
		void ocurrioUnErrorServidor();
		void dibujar();
        void manejarEntrada(SDL_Keycode codigoEntrada);
        void manejarClick(SDL_Event eventoClick);
};

#endif /* SRC_APP_APP_HPP_ */
