//#include <SDL.h>
#include <SDL2/SDL.h>
#include <stdio.h>

const int ANCHO_VENTANA = 1024;
const int ALTO_VENTANA = 720;

SDL_Window* inicializarSDL(SDL_Window *ventanaPrincipal) {

	SDL_Surface *superficieVentana = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("No se pudo inicializar SDL! SDL_Error: %s\n", SDL_GetError());
	}
	else{

		ventanaPrincipal = SDL_CreateWindow("Super Mario Bros",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_VENTANA, ALTO_VENTANA, SDL_WINDOW_SHOWN);

		if (ventanaPrincipal == NULL) {
			printf("No se pudo crear la ventana! SDL_Error: %s\n",SDL_GetError());
		}
		else {
			//superficieVentana = SDL_GetWindowSurface(ventanaPrincipal);
			//SDL_FillRect(superficieVentana, NULL,SDL_MapRGB(superficieVentana->format, 0x23, 0x4F, 0xFd));

			superficieVentana = SDL_GetWindowSurface( ventanaPrincipal ); //Agarramos la superficie de la ventana principal


			SDL_Surface* imagenDeFondo = SDL_LoadBMP( "./resources/fondo_inicio.bmp" );
		    if( imagenDeFondo == NULL ){
		        printf( "No se pudo cargar la imagen! %s\n", SDL_GetError() );
		    }
		    else{
		    	SDL_BlitSurface( imagenDeFondo, NULL, superficieVentana, NULL );
		    	SDL_UpdateWindowSurface(ventanaPrincipal);
		    	SDL_Delay(2000);
		    	SDL_FreeSurface( imagenDeFondo ); // Se libera la memoria de la imagen
		    }
		}
	}
	return ventanaPrincipal;
}
/*
int main( int argc, char* args[] ){

	SDL_Window* ventanaPrincipal = NULL;

	ventanaPrincipal = inicializarSDL(ventanaPrincipal);



	SDL_DestroyWindow( ventanaPrincipal );

	SDL_Quit();

	return 0;
}*/
