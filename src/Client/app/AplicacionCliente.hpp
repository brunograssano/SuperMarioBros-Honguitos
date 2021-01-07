#ifndef SRC_APP_APP_HPP_
#define SRC_APP_APP_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

#include "Dibujadores/Dibujadores.hpp"
#include "ManejadorSDL.hpp"
#include "juegoCliente/JuegoCliente.hpp"
#include "CargadorTexturas.hpp"
#include "../../Utils/log/Log.hpp"
#include "../../Server/lector/ArchivoLeido.hpp"
#include "../../Client/reproductorDeMusica/ReproductorMusica.hpp"
#include "src/Utils/Constantes.hpp"
#include "../../Utils/Utils.hpp"
#include "../Cliente.hpp"

#include <map>

class App{

	protected:
		App(info_partida_t informacion, Cliente* cliente){
			Log* log = Log::getInstance();
			this->cliente = cliente;

			ancho_pantalla = informacion.anchoVentana;
            alto_pantalla = informacion.altoVentana;
			inicializarSDL(log);

			cargadorTexturas = new CargadorTexturas(renderizador);

			for(int i=0; i<informacion.cantidadFondosNiveles; i++){
				//*Traerme el vector de mundos*//
				this->direccionesNiveles[informacion.mundo+i] = string(informacion.direccionesFondoNiveles[i]);
			}

			//if(informacion.iniciadoCorrectamente){
			cargadorTexturas->cargarTexturasNiveles(direccionesNiveles,informacion.cantidadFondosNiveles, renderizador, informacion.mundo);
			//}

			rectanguloCamara = { 0, 0, ancho_pantalla , alto_pantalla};

			juegoCliente = new JuegoCliente(informacion.cantidadJugadores,informacion.jugadores,informacion.idPropio);

			sePusoMusicaInicio = false;
			sonoSalto = false;
			terminoElJuego = false;
			comenzoElJuego = false;
			errorServidor = false;
			estaReproduciendoMusicaGanadores = false;

			bool juegoInicializadoCorrectamente = true;
			dibujador = new Dibujadores(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla,juegoInicializadoCorrectamente);

			log->mostrarMensajeDeInfo("Inicio del juego");

		}

		static App* aplicacion;
		CargadorTexturas* cargadorTexturas;
		SDL_Window* ventanaAplicacion;
		SDL_Renderer* renderizador;
		SDL_Rect rectanguloCamara;
		Dibujadores* dibujador;

		void inicializarSDL(Log* log);
		void determinarDimensionesPantalla(int posibleAnchoVentana,int posibleAltoVentana);

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
		App(App &other) = delete;
		static App *getInstance();
		static App *getInstance(info_partida_t informacion,Cliente* cliente);

		void actualizarServer(const Uint8 *keystate);
		void actualizar();
		void agregarRonda(info_ronda_t info_ronda);
		void ocurrioUnErrorServidor();

		void dibujar();
		~App();


};

#endif /* SRC_APP_APP_HPP_ */
