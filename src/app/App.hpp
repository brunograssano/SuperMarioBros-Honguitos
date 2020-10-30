#ifndef SRC_APP_APP_HPP_
#define SRC_APP_APP_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

#include "Dibujadores/Dibujadores.hpp"
#include "../modelo/Juego.hpp"
#include "CargadorTexturas.hpp"
#include "../sprites/SpriteMario.hpp"
#include "../log/Log.hpp"
#include "../lector/ArchivoLeido.hpp"
#include "../reproductorDeMusica/ReproductorMusica.hpp"

const int ANCHO_FONDO = 8177;

class App{

	protected:
		App(ArchivoLeido* archivoLeido){

			Log* log = Log::getInstance(archivoLeido->tipoLog);
			escribirMensajesDeArchivoLeidoEnLog(archivoLeido->mensajeError);
			determinarDimensionesPantalla(archivoLeido->anchoVentana,archivoLeido->altoVentana);
			inicializarSDL(log);

			cargadorTexturas = new CargadorTexturas(renderizador);
			cargadorTexturas->cargarTexturasNiveles(archivoLeido->niveles, renderizador);

			juego = Juego::getInstance(archivoLeido->niveles);
			rectanguloCamara = { 0, 0, ancho_pantalla , alto_pantalla};

			posicionFinalNivel = 5000;
			tiempoFaltante = 0;
			tiempoDeInicio = 0;
			sePusoMusicaInicio = false;
			terminoElJuego = false;
			comenzoElJuego = false;
			ganaron = false;
			dibujador = new Dibujadores(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);

			log->mostrarMensajeDeInfo("Inicio del juego");
			delete archivoLeido;
		}

		Juego* juego;
		static App* aplicacion;
		CargadorTexturas* cargadorTexturas;
		SDL_Window* ventanaAplicacion;
		SDL_Renderer* renderizador;
		SDL_Rect rectanguloCamara;
		Dibujadores* dibujador;
		int tiempoFaltante;
		int tiempoDeInicio;
		int posicionFinalNivel;

		void revisarSiTerminoNivel(Mario* jugador);
		void inicializarSDL(Log* log);
		void determinarDimensionesPantalla(int posibleAnchoVentana,int posibleAltoVentana);

		bool sePusoMusicaInicio;
		bool terminoElJuego;
		bool comenzoElJuego;
		bool ganaron;

		int ancho_pantalla;
		int alto_pantalla;

	public:
		App(App &other) = delete;
		static App *getInstance();
		static App *getInstance(ArchivoLeido* archivoLeido);


		void actualizar(const Uint8 *keystate);
		void actualizar();
		void moverCamara(Mario* jugador);
		int obtenerTiempoFaltante();
		void escribirMensajesDeArchivoLeidoEnLog(list<string> mensajesError);

		SDL_Renderer* obtenerRenderizador();

		SDL_Rect* obtenerRectCamara();
		void dibujar();
		~App();


};

#endif /* SRC_APP_APP_HPP_ */
