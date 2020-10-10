

#include "CargadorTexturas.h"
#include "App.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

CargadorTexturas::CargadorTexturas(){

	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
		// TODO poner en el log que no se pudo activar el filtrado lineal de las texturas
	}

	texturaMario = cargarTextura( "comienzo.png" ); 	// NO OLVIDARSE DE LIBERAR LAS TEXTURAS QUE SE CARGUEN
	if( texturaMario == NULL ){
		// TODO escribir en el log
	}
	texturaMoneda = cargarTextura("marioElduro.png");
	if(texturaMoneda == NULL){
		// TODO escribir en el log
	}
	texturaLadrillo = cargarTextura( "comienzo.png" );
	if( texturaLadrillo == NULL ){
		// TODO escribir en el log
	}
	texturaSorpresa = cargarTextura("marioElduro.png");
	if(texturaSorpresa == NULL){
		// TODO escribir en el log
	}



}

SDL_Texture* CargadorTexturas::cargarTextura(std::string direccion){
	SDL_Texture*  texturaCargada= NULL;
	SDL_Surface* superficieImagen = IMG_Load(direccion.c_str());
	if(superficieImagen == NULL){
		// TODO poner en el log que no se pudo cargar la imagen  ---IMG_GetError()
	}
	else{
		texturaCargada = SDL_CreateTextureFromSurface( App::GetInstance()->obtenerRenderizador(), superficieImagen );
		if( texturaCargada == NULL ){
			// TODO poner en el log que no se pudo crear una textura SDL_GetError() );
		}
		SDL_FreeSurface( superficieImagen );
	}
	return texturaCargada;
}

CargadorTexturas::~CargadorTexturas(){
	SDL_DestroyTexture( texturaMario );
	SDL_DestroyTexture( texturaMoneda );
	SDL_DestroyTexture( texturaLadrillo );
	SDL_DestroyTexture( texturaSorpresa );
}
