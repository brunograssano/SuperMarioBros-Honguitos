/*//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
using namespace std;
#include <iostream>
#include <string>
#include "../modelo/Mario.h"
#include "../modelo/Movimientos/Movimiento.h"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


//Starts up SDL
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed PNG image
SDL_Surface* gPNGSurface = NULL;

bool init(){

	//Initialization flag
	bool success = true;

	//Inicializa SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return !success;
	}

	//Crea una ventana
	gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

	if( gWindow == NULL ){
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return !success;
	}

	//Initializo la biblioteca SDL_Image
	int imgFlags = IMG_INIT_PNG;

	if( !( IMG_Init( imgFlags ) & imgFlags ) ){
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return !success;
	}

	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	if( gRenderer == NULL ){
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return !success;
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );



	//Obtengo la (Surface) superficie de la ventana
	gScreenSurface = SDL_GetWindowSurface( gWindow );

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Cargo la imagen png
	gPNGSurface = loadSurface( "./resources/comienzo.png" );

	if( gPNGSurface == NULL ){
		printf( "Failed to load PNG image!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Libero la imagen cargada
	SDL_FreeSurface( gPNGSurface );
	gPNGSurface = NULL;

	//Destruyo el renderer
	SDL_DestroyRenderer( gRenderer );

	//Destruyo la ventanta
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quiteo los subsistemas de SDL
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Cargo la imagen que se encuentra en el path especificado
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ){
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}else{
		//Convierto la Surface al formato del Screen
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
		if( optimizedSurface == NULL ){
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Me deshago de la Surface viejo
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}

int main(int argc, char* args[]){
	//Inicializa SDL y crea una ventana
	if( !init() ){
		printf( "Ha fallado la inicializacion de SDL\n" );
		close();
		return -1;
	}

	//Load media, se carga una imagen inicial en la ventana
	if( !loadMedia() ){
		printf( "Ha fallado la carga de imagenes incial" );
		close();
		return -1;
	}

	//Main loop flag
	bool quit = false;
	bool comenzar = false;
	//Event handler
	SDL_Event e;

	//While application is running
	while(!quit && !comenzar){

		//Aplicar la imagen PNG
		SDL_BlitSurface( gPNGSurface, NULL, gScreenSurface, NULL );

		//Actualizar surface
		SDL_UpdateWindowSurface( gWindow );

		//Handle events on queue
		while(SDL_PollEvent(&e) != 0){
			//User requests quit
			if(e.type == SDL_QUIT){
				quit = true;
				printf("Se ha cerrado la aplicacion");
			}else if(e.key.keysym.sym  == SDLK_RETURN){
				comenzar = true;
				printf("Se ha comenzado la aplicacion");
			}
		}

	}

	// Si se comenzo: comenzar == true; si se quiteo: quit == true


	Mario* mario = new Mario();
	gPNGSurface = loadSurface( "./resources/marioElduro.png" );
	SDL_Rect rectanguloMario = { mario->obtenerPosicionX(), mario->obtenerPosicionY(), 40, 80};

	SDL_Renderer* gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_Surface* surfaceMario = loadSurface("./resources/marioElduro.png");
	SDL_Texture* textureMario = SDL_CreateTextureFromSurface( gRenderer, surfaceMario );
	SDL_FreeSurface( surfaceMario );
	//SDL_Rect rectanguloMario = SDL_FillRect(gPNGSurface, NULL, SDL_MapRGB(gPNGSurface->format, 0, 0, 0));


	while(!quit){
		//Handle events on queue
		while(SDL_PollEvent(&e) != 0){
			//User requests quit
			if(e.type == SDL_QUIT){
				quit = true;
			}
			else if(e.type == SDL_KEYDOWN){
				//Select surfaces based on key press
				Movimiento* movimiento;
				switch(e.key.keysym.sym){
					case SDLK_UP:
						movimiento = new MovimientoAbajo(50);
						mario->mover(movimiento);
					break;
					case SDLK_DOWN:
						movimiento = new MovimientoArriba(20);
						mario->mover(movimiento);
					break;

					case SDLK_LEFT:
						movimiento = new MovimientoIzquierda(50);
						mario->mover(movimiento);
					break;

					case SDLK_RIGHT:
						movimiento = new MovimientoDerecha(20);
						mario->mover(movimiento);
					break;

					default:

					break;
				}
				delete movimiento;
				rectanguloMario.x = mario->obtenerPosicionX();
				rectanguloMario.y = mario->obtenerPosicionY();
			}
		}

		SDL_RenderClear( gRenderer );

		//Render texture to screen
		SDL_RenderCopy( gRenderer, textureMario, NULL, NULL);

		//Update screen
		SDL_RenderPresent( gRenderer );

	}

	//Liberar recursos y cerrar SDL
	close();
	delete mario;

	return 0;
}
*/
