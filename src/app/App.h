#ifndef SRC_APP_APP_H_
#define SRC_APP_APP_H_

#include <SDL2/SDL.h>
#include "../modelo/Juego.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "CargadorTexturas.h"
#include "SpriteMario.h"

const int ANCHO_PANTALLA = 800;
const int ALTO_PANTALLA = 600;
const int ANCHO_FONDO = 4000;

class App{

	protected:
		App(){
			if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
				// TODO escribir en el log que ocurrio un error inicializando SDL --- SDL_GetError()
			}

			ventanaAplicacion = SDL_CreateWindow( "Super Mario Bros", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_PANTALLA, ALTO_PANTALLA, SDL_WINDOW_SHOWN );
			if( ventanaAplicacion == NULL ){
				// TODO excribir en el log que no se pudo crear una ventana de SDL --- SDL_GetError()
			}

			//Initializo la biblioteca SDL_Image
			//int imgFlags = IMG_INIT_PNG;

			if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ){
				// TODO Poner en el log que no se pudo inicializar el img init --- IMG_GetError()
			}

			renderizador = SDL_CreateRenderer( ventanaAplicacion, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( renderizador == NULL ){
				// TODO Poner en el log que no se pudo crear un renderizador --- SDL_GetError()
			}

			//Initialize renderer color
			//SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

			//	TODO  primera llamada al juego, asi se inicializa

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
