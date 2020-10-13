

#include "CargadorTexturas.h"
#include "App.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <sstream>

CargadorTexturas::CargadorTexturas(SDL_Renderer* renderizador){

	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
		// TODO poner en el log que no se pudo activar el filtrado lineal de las texturas
	}

	texturaMario = cargarTextura("resources/sprite_mario_grande/mario_grande_quieto_der.png",renderizador); 	// NO OLVIDARSE DE LIBERAR LAS TEXTURAS QUE SE CARGUEN
	if( texturaMario == NULL ){
		// TODO escribir en el log

	}								// LA CARGO ACA PARA PROBAR AL GOOMBA
	texturaMoneda = cargarTextura("resources/goomba.resized.png",renderizador);
	if(texturaMoneda == NULL){
		// TODO escribir en el log
	}
	texturaLadrillo = cargarTextura( "comienzo.png" ,renderizador);
	if( texturaLadrillo == NULL ){
		// TODO escribir en el log
	}
	texturaSorpresa = cargarTextura("marioElduro.png",renderizador);
	if(texturaSorpresa == NULL){
		// TODO escribir en el log
	}



}

void CargadorTexturas::actualizarSpriteMario(std::string direccion, SDL_Renderer* renderizador){
        texturaMario = cargarTextura( direccion ,renderizador);
}

SDL_Texture* CargadorTexturas::cargarTextura(std::string direccion, SDL_Renderer* renderizador){
	SDL_Texture*  texturaCargada= NULL;
	SDL_Surface* superficieImagen = IMG_Load(direccion.c_str());
	if(superficieImagen == NULL){
		// TODO poner en el log que no se pudo cargar la imagen  ---IMG_GetError()
		std::cout<< "No la encontro"<<endl;
	}
	else{
		texturaCargada = SDL_CreateTextureFromSurface( renderizador, superficieImagen );
		if( texturaCargada == NULL ){ // creo que este no es necesario, si es que ya lo verificamos arriba si es null
			// TODO poner en el log que no se pudo crear una textura SDL_GetError() );
			std::cout<< "No la encontro la textura"<<endl;
		}
		SDL_FreeSurface( superficieImagen );
	}
	return texturaCargada;
}

SDL_Texture* CargadorTexturas::obtenerTexturaMario(){
	return texturaMario;
}

SDL_Texture* CargadorTexturas::obtenerTexturaMoneda(){
	return texturaMoneda;
}

CargadorTexturas::~CargadorTexturas(){
	SDL_DestroyTexture( texturaMario );
	SDL_DestroyTexture( texturaMoneda );
	SDL_DestroyTexture( texturaLadrillo );
	SDL_DestroyTexture( texturaSorpresa );
}
