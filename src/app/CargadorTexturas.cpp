

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

	texturaMario = cargarTextura("resources/mario_grande.png",renderizador);
	if( texturaMario == NULL ){
		log->huboUnError("No se pudo cargar ninguna imagen de Mario en: resources/resources/mario_grande.png.png");

	}
	else{
		log->mostrarMensajeDeCarga("Mario", "resources/resources/mario_grande.png.png");
	}

	// LA CARGO ACA PARA PROBAR AL GOOMBA
	texturaMoneda = cargarTextura("resources/Monedas.png",renderizador);
	if(texturaMoneda == NULL){
		log->huboUnError("No se pudo cargar ninguna imagen de las monedas en: resources/Monedas.png");
	}
	else{
		log->mostrarMensajeDeCarga("Mario", "resources/Monedas.png");
	}

	texturaLadrillo = cargarTextura( "resources/BloqueLadrillo.png" ,renderizador);
	if( texturaLadrillo == NULL ){
		log->huboUnError("No se pudo cargar ninguna imagen del bloque ladrillo en: resources/BloqueLadrillo.png");
	}
	else{
		log->mostrarMensajeDeCarga("Ladrillo", "resources/BloqueLadrillo.png");
	}

	texturaSorpresa = cargarTextura("resources/BloqueSorpresa.png",renderizador);
	if(texturaSorpresa == NULL){
		log->huboUnError("No se pudo cargar ninguna imagen del bloque sorpresa en: resources/BloqueSorpresa.png");
	}
	else{
		log->mostrarMensajeDeCarga("Sorpresa", "resources/BloqueSorpresa.png");
	}

	/*
	texturaFondo = cargarTextura("resources/MapaNivel1Base.png", renderizador);
	if(texturaSorpresa == NULL){
		log->huboUnError("No se pudo cargar el fondo"); // la cargas de la textura del fondo esta de forma temporal por ahora
	}
	else{
		log->mostrarMensajeDeCarga("Mario", "resources/sprite_mario_grande/mario_grande_quieto_der.png");
	}
	*/
	// NO OLVIDARSE DE LIBERAR LAS TEXTURAS QUE SE CARGUEN
}

SDL_Texture* CargadorTexturas::obtenerTexturaLadrillo(){
	return texturaLadrillo;
}

SDL_Texture* CargadorTexturas::obtenerTexturaSorpresa(){
	return this->texturaSorpresa;
}

SDL_Texture* CargadorTexturas::obtenerTexturaFondo(){
	return texturaFondoActual;
}


void CargadorTexturas::actualizarSpriteMario(std::string direccion, SDL_Renderer* renderizador){
        texturaMario = cargarTextura( direccion ,renderizador);
}

void CargadorTexturas::revisarSiCambioNivel(SDL_Renderer* renderizador){
	string direccionDelNivel = Juego::getInstance()->obtenerDireccionFondoNivelActual();
	if(direccionFondoActual != direccionDelNivel){
		SDL_DestroyTexture( texturaFondoActual );
		direccionFondoActual = direccionDelNivel;
		texturaFondoActual = cargarTextura(direccionDelNivel,renderizador);
	}
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

bool CargadorTexturas::tengoTexturaCargadaEnMemoria(Sprite* spriteEnemigo){ // No me esta tomando el contains del map (c++ 20))
	try{
		texturasEnemigos.at(spriteEnemigo->direccionImagen());
	}
	catch(std::out_of_range&){
		return false;
	}
	return true;
}


SDL_Texture* CargadorTexturas::obtenerTexturaEnemigo(Sprite* spriteEnemigo,SDL_Renderer* renderizador){
	if(!tengoTexturaCargadaEnMemoria(spriteEnemigo)){
		SDL_Texture* texturaNueva = cargarTextura(spriteEnemigo->direccionImagen(),renderizador);
		texturasEnemigos[spriteEnemigo->direccionImagen()]=texturaNueva;
	}
	return texturasEnemigos[spriteEnemigo->direccionImagen()];
}

CargadorTexturas::~CargadorTexturas(){
	SDL_DestroyTexture( texturaMario );
	SDL_DestroyTexture( texturaMoneda );
	SDL_DestroyTexture( texturaLadrillo );
	SDL_DestroyTexture( texturaSorpresa );
	SDL_DestroyTexture( texturaFondoActual );
}
