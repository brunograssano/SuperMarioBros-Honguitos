#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
#include "modelo/Mario.h"
#include "modelo/Movimientos/Movimiento.h"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The window renderer
SDL_Renderer* gRenderer = NULL;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed PNG image
SDL_Surface* gPNGSurface = NULL;

bool init(){
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if( !( IMG_Init( imgFlags ) & imgFlags ) )
			{
				printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
				success = false;
			}
			else
			{
				//Get window surface
				gScreenSurface = SDL_GetWindowSurface( gWindow );
			}
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}else{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			}
		}
	}

	return success;
}

bool loadMedia(){
	//Loading success flag
	bool success = true;


	//Load PNG surface
	gPNGSurface = loadSurface( "./resources/comienzo.png" );
	if( gPNGSurface == NULL )
	{
		printf( "Failed to load PNG image!\n" );
		success = false;
	}

	return success;
}

void close(){
	//Free loaded image
	SDL_FreeSurface(gPNGSurface);
	gPNGSurface = NULL;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path){
	//The final optimized image

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	SDL_Surface* optimizedSurface = NULL;
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
		if(optimizedSurface == NULL){
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return loadedSurface;
}

int main(int argc, char* args[]){
	//Start up SDL and create window
	if(!init()){
		printf( "Failed to initialize!\n" );
		return -1;
	}
	//Load media
	if(!loadMedia()){
		cout << "Failed to load media!\n" << endl;
		close();
		return -1;
	}
	cout << "strike 2" << endl;
	//Create renderer for window
	//Main loop flag
	bool quit = false;
	bool comenzar = false;
	//Event handler
	SDL_Event e;

	//While application is running
	while(!quit || !comenzar){
		//Handle events on queue
		while(SDL_PollEvent(&e) != 0){
			//User requests quit
			if(e.type == SDL_QUIT){
				quit = true;
			}
			else if(e.key.keysym.sym  == SDLK_RETURN){
				comenzar = true;
			}
		}

		//Apply the PNG image
		SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, NULL);
		//Update the surface
		SDL_UpdateWindowSurface(gWindow);
		cout << "strike 2.5" << endl;
	}

	Mario* mario = new Mario();
	gPNGSurface = loadSurface( "./resources/marioElduro.png" );
	SDL_Rect rectanguloMario = { mario->obtenerPosicionX(), mario->obtenerPosicionY(), 40, 80};

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
						movimiento = new MovimientoArriba(50);
						mario->mover(movimiento);
					break;
					case SDLK_DOWN:
						movimiento = new MovimientoAbajo(20);
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
		//Apply the PNG image
		SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, &rectanguloMario);

		//Update the surface
		SDL_UpdateWindowSurface(gWindow);
	}
	delete mario;
	//Free resources and close SDL
	close();

	return 0;
}
