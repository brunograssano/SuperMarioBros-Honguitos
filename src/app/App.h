#ifndef SRC_APP_APP_H_
#define SRC_APP_APP_H_

#include <SDL2/SDL.h>
#include "../modelo/Juego.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "CargadorTexturas.h"
#include "SpriteMario.h"

#include "../log/Log.h"
#include "../log/TipoLog.h"


#include "../log/Error.h"
#include "../log/Info.h"
#include "../log/Debug.h"

const int ANCHO_PANTALLA = 800;
const int ALTO_PANTALLA = 540;

const int ANCHO_FONDO = 8177;

class App{

	protected:
		App(){

			// TODO venir del lector o de linea de comando el tipo de log
			TipoLog* tipo = new Error();
			Log* log = Log::getInstance(tipo);

			if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
				log->huboUnErrorSDL("Error inicializando SDL", SDL_GetError());
			}

			ventanaAplicacion = SDL_CreateWindow( "Super Mario Bros", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_PANTALLA, ALTO_PANTALLA, SDL_WINDOW_SHOWN );
			if( ventanaAplicacion == NULL ){
				log->huboUnErrorSDL("No se pudo crear una ventana de SDL", SDL_GetError());
			}

			if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ){
				log->huboUnErrorSDL("No se pudo inicializar IMG Init", IMG_GetError());
			}

			renderizador = SDL_CreateRenderer( ventanaAplicacion, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( renderizador == NULL ){
				log->huboUnErrorSDL("No se pudo crear un renderizador de SDL", SDL_GetError());
			}

			cargadorTexturas = new CargadorTexturas(renderizador);
			juego = Juego::getInstance();
			spriteMario = new SpriteMario();
			rectanguloCamara = { 0, 0, ANCHO_PANTALLA , ALTO_PANTALLA};

		}

		Juego* juego;
		static App* aplicacion;
		CargadorTexturas* cargadorTexturas;
		SDL_Window* ventanaAplicacion;
		SDL_Renderer* renderizador;
		SpriteMario* spriteMario;
		SDL_Rect rectanguloCamara;

	public:
		App(App &other) = delete;
		static App *GetInstance();

		void actualizar(SDL_Event evento);
		void actualizar();
		void moverCamara();
		SDL_Renderer* obtenerRenderizador();

		SDL_Rect* obtenerRectCamara();
		void dibujar();
		~App();


};




#endif /* SRC_APP_APP_H_ */
