#ifndef SRC_APP_APP_HPP_
#define SRC_APP_APP_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

#include "Dibujadores/Dibujadores.hpp"
#include "juegoCliente/JuegoCliente.hpp"
#include "CargadorTexturas.hpp"
#include "src/Utils/Constantes.hpp"
#include "../../Utils/Utils.hpp"
#include "../Cliente.hpp"

#include <map>

class App{

	protected:
		App(info_partida_t informacion, Cliente* cliente);
		static App* aplicacion;
		CargadorTexturas* cargadorTexturas;
		SDL_Window* ventanaAplicacion{};
		SDL_Renderer* renderizador{};
		SDL_Rect rectanguloCamara{};
		Dibujadores* dibujador;
		void inicializarSDL();
		JuegoCliente* juegoCliente;
		bool sePusoMusicaInicio;
		bool comenzoElJuego;
		bool sonoSalto;
		bool terminoElJuego;
		bool errorServidor;
		bool estaReproduciendoMusicaGanadores;
		map<int,string> direccionesNiveles;
		int ancho_pantalla;
		int alto_pantalla;
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
};

#endif /* SRC_APP_APP_HPP_ */
