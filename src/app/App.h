#ifndef SRC_APP_APP_H_
#define SRC_APP_APP_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

#include "Dibujador.h"
#include "../modelo/Juego.h"
#include "CargadorTexturas.h"
#include "../sprites/SpriteMario.h"
#include "../log/Log.h"
#include "../lector/ArchivoLeido.hpp"

const int ANCHO_FONDO = 8177;

class App{

	protected:
		App(ArchivoLeido* archivoLeido){

			Log* log = Log::getInstance(archivoLeido->tipoLog);
			determinarDimensionesPantalla(archivoLeido->anchoVentana,archivoLeido->altoVentana);
			inicializarSDL(log);

			cargadorTexturas = new CargadorTexturas(renderizador);
			juego = Juego::getInstance(archivoLeido->niveles);
			spriteMario = new SpriteMario("../resources/mario_grande.png");
			rectanguloCamara = { 0, 0, ancho_pantalla , alto_pantalla};

			posicionFinalNivel = 5000;
			tiempoFaltante = 0;
			tiempoDeInicio = 0;
			terminoElJuego = false;
			ganaron = false;
			dibujador = new Dibujador(cargadorTexturas,renderizador,spriteMario,ancho_pantalla,alto_pantalla);

			log->mostrarMensajeDeInfo("Inicio del juego");
			delete archivoLeido;
		}

		Juego* juego;
		static App* aplicacion;
		CargadorTexturas* cargadorTexturas;
		SDL_Window* ventanaAplicacion;
		SDL_Renderer* renderizador;
		SpriteMario* spriteMario;
		SDL_Rect rectanguloCamara;
		Dibujador* dibujador;
		int tiempoFaltante;
		int tiempoDeInicio;
		int posicionFinalNivel;

		void revisarSiTerminoNivel(Mario* jugador);
		void inicializarSDL(Log* log);
		void determinarDimensionesPantalla(int posibleAnchoVentana,int posibleAltoVentana);

		bool terminoElJuego;
		bool ganaron;

		int ancho_pantalla;
		int alto_pantalla;

	public:
		App(App &other) = delete;
		static App *getInstance();
		static App *getInstance(ArchivoLeido* archivoLeido);


		void actualizar(SDL_Event evento);
		void actualizar();
		void moverCamara(Mario* jugador);
		int obtenerTiempoFaltante();
		void escribirMensajesDeArchivoLeidoEnLog(list<string> mensajesError);

		SDL_Renderer* obtenerRenderizador();

		SDL_Rect* obtenerRectCamara();
		void dibujar();
		~App();


};

#endif /* SRC_APP_APP_H_ */
