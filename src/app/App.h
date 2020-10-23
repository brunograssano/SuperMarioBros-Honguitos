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
#include "../log/TipoLog.h"
#include "../lector/ArchivoLeido.hpp"

const int ANCHO_PANTALLA = 800;
const int ALTO_PANTALLA = 540;

const int ANCHO_FONDO = 8177;

class App{

	protected:
		App(ArchivoLeido* archivoLeido){

			Log* log = Log::getInstance(archivoLeido->tipoLog);
			ancho_pantalla = archivoLeido->anchoVentana;
			alto_pantalla = archivoLeido->altoVentana;

			if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
				log->huboUnErrorSDL("Error inicializando SDL", SDL_GetError());
			}

			ventanaAplicacion = SDL_CreateWindow( "Super Mario Bros", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ancho_pantalla, alto_pantalla, SDL_WINDOW_SHOWN );
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
			juego = Juego::getInstance(archivoLeido->niveles);
			spriteMario = new SpriteMario("../resources/mario_grande.png");
			rectanguloCamara = { 0, 0, ancho_pantalla , alto_pantalla};


			string direccion = "resources/IconoHongo.png";
			SDL_Surface* icono = IMG_Load(direccion.c_str());
			if(icono == NULL){
				Log::getInstance()->huboUnErrorSDL("No se pudo cargar el icono en: " + direccion, IMG_GetError());
			}
			else{
				SDL_SetWindowIcon(ventanaAplicacion, icono);
				SDL_FreeSurface(icono);
			}

			dibujador = new Dibujador(cargadorTexturas,renderizador,spriteMario);
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

		int ancho_pantalla = 800;
		int alto_pantalla = 540;

	public:
		App(App &other) = delete;
		static App *GetInstance();
		static App *GetInstance(ArchivoLeido* archivoLeido);


		void actualizar(SDL_Event evento);
		void actualizar();
		void moverCamara();

		SDL_Renderer* obtenerRenderizador();

		SDL_Rect* obtenerRectCamara();
		void dibujar();
		~App();


};




#endif /* SRC_APP_APP_H_ */
