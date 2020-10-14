

#include "CargadorTexturas.h"
#include "App.h"
#include "../log/Log.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <sstream>

CargadorTexturas::CargadorTexturas(SDL_Renderer* renderizador){
	Log* log = Log::getInstance();
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
		log->huboUnError("No se pudo activar el filtrado lineal de las texturas");
	}

	texturaMario = cargarTextura("resources/sprite_mario_grande/mario_grande_quieto_der.png",renderizador);
	if( texturaMario == NULL ){
		log->huboUnError("No se pudo cargar ninguna imagen de Mario");

	}
	else{
		log->mostrarMensajeDeCarga("Mario", "resources/sprite_mario_grande/mario_grande_quieto_der.png");
	}

	// LA CARGO ACA PARA PROBAR AL GOOMBA
	texturaMoneda = cargarTextura("resources/goomba.resized.png",renderizador);
	if(texturaMoneda == NULL){
		log->huboUnError("No se pudo cargar ninguna imagen de las monedas");
	}
	else{
		log->mostrarMensajeDeCarga("Mario", "resources/goomba.resized.png");
	}

	texturaLadrillo = cargarTextura( "comienzo.png" ,renderizador);
	if( texturaLadrillo == NULL ){
		log->huboUnError("No se pudo cargar ninguna imagen del bloque: ladrillo");
	}
	else{
		log->mostrarMensajeDeCarga("Ladrillo", "DIRECCION");
	}

	texturaSorpresa = cargarTextura("marioElduro.png",renderizador);
	if(texturaSorpresa == NULL){
		log->huboUnError("No se pudo cargar ninguna imagen del bloque: sorpresa");
	}
	else{
		log->mostrarMensajeDeCarga("Sorpresa", "DIRECCION");
	}

	texturaFondo = cargarTextura("resources/MapaNivel1Base.png", renderizador);
	if(texturaSorpresa == NULL){
		log->huboUnError("No se pudo cargar el fondo"); // la cargas de la textura del fondo esta de forma temporal por ahora
	}
	else{
		log->mostrarMensajeDeCarga("Mario", "resources/sprite_mario_grande/mario_grande_quieto_der.png");
	}
	// NO OLVIDARSE DE LIBERAR LAS TEXTURAS QUE SE CARGUEN
}

SDL_Texture* CargadorTexturas::obtenerTexturaFondo(){
	return this->texturaFondo;
}

void CargadorTexturas::actualizarSpriteMario(std::string direccion, SDL_Renderer* renderizador){
        texturaMario = cargarTextura( direccion ,renderizador);
}

SDL_Texture* CargadorTexturas::cargarTextura(std::string direccion, SDL_Renderer* renderizador){
	SDL_Texture*  texturaCargada= NULL;
	SDL_Surface* superficieImagen = IMG_Load(direccion.c_str());
	if(superficieImagen == NULL){
		Log::getInstance()->huboUnErrorSDL("No se pudo cargar una imagen en " + direccion, IMG_GetError());
	}
	else{
		texturaCargada = SDL_CreateTextureFromSurface( renderizador, superficieImagen );
		if( texturaCargada == NULL ){
			Log::getInstance()->huboUnErrorSDL("No se pudo crear una texturea a partir de la imagen en " + direccion, SDL_GetError());
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
	SDL_DestroyTexture( texturaFondo );
}
