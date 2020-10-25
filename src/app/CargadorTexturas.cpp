

#include "CargadorTexturas.h"
#include "App.h"
#include "../log/Log.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <sstream>



CargadorTexturas::CargadorTexturas(SDL_Renderer* renderizador){
	Log* log = Log::getInstance();

	if( TTF_Init() == -1 ){
		log->huboUnErrorSDL("No se pudo inicializar SDL_ttf ", TTF_GetError());
	}

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

	texturaMoneda = cargarTextura("resources/Monedas.png",renderizador);
	if(texturaMoneda == NULL){
		log->huboUnError("No se pudo cargar ninguna imagen de las monedas en: resources/Monedas.png");
	}
	else{
		log->mostrarMensajeDeCarga("Moneda", "resources/Monedas.png");
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

	int tamanioFuente = 20;
	string direccionFuente = "resources/fuenteSuperMarioBros.ttf";
	fuenteJuego = TTF_OpenFont( direccionFuente.c_str(), tamanioFuente);
	if(fuenteJuego==NULL){
		log->huboUnErrorSDL("No se pudo cargar la fuente del juego en: ", "resources/fuenteSuperMarioBros.ttf");
	}
	else{
		log->mostrarMensajeDeCarga("Fuente de texto del juego", "resources/fuenteSuperMarioBros.ttf");
	}

	log->mostrarMensajeDeInfo("Ha finalizado la carga de imagenes no configurables por el usuario");
}


SDL_Texture* CargadorTexturas::cargarFuenteDeTextoATextura(string textoAMostrar, SDL_Renderer* renderizador){
	Log* log = Log::getInstance();
	SDL_Color colorTexto= { 255, 255, 255, 255 };


	SDL_Surface* superficeDeTexto = TTF_RenderText_Solid( fuenteJuego, textoAMostrar.c_str(), colorTexto );
	if( superficeDeTexto == NULL ){
		log->huboUnErrorSDL("No se pudo convertir el mensaje a superficie : "+ textoAMostrar +" a una superficie.", TTF_GetError());
		return NULL;
	}

	SDL_Texture* texturaCargada = SDL_CreateTextureFromSurface( renderizador, superficeDeTexto );
	if( texturaCargada == NULL ){
		log->huboUnErrorSDL( "No se pudo crear una textura a partir de un texto renderizado. ", SDL_GetError() );
	}

	SDL_FreeSurface( superficeDeTexto );

	return texturaCargada;
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




bool CargadorTexturas::tengoTexturaEnemigoCargadaEnMemoria(Sprite* spriteEnemigo){ // No me esta tomando el contains del map (c++ 20))
	try{
		texturasEnemigos.at(spriteEnemigo->direccionImagen());
	}
	catch(std::out_of_range&){
		return false;
	}
	return true;
}


SDL_Texture* CargadorTexturas::obtenerTexturaEnemigo(Sprite* spriteEnemigo,SDL_Renderer* renderizador){
	if(!tengoTexturaEnemigoCargadaEnMemoria(spriteEnemigo)){
		SDL_Texture* texturaNueva = cargarTextura(spriteEnemigo->direccionImagen(),renderizador);
		texturasEnemigos[spriteEnemigo->direccionImagen()]=texturaNueva;
	}
	return texturasEnemigos[spriteEnemigo->direccionImagen()];
}

bool CargadorTexturas::tengoTexturaBloqueCargadaEnMemoria(Sprite* spriteBloque){ // No me esta tomando el contains del map (c++ 20))
	try{
		texturasBloques.at(spriteBloque->direccionImagen());
	}
	catch(std::out_of_range&){
		return false;
	}
	return true;
}


SDL_Texture* CargadorTexturas::obtenerTexturaBloque(Sprite* spriteBloque,SDL_Renderer* renderizador){
	if(!tengoTexturaBloqueCargadaEnMemoria(spriteBloque)){
		SDL_Texture* texturaNueva = cargarTextura(spriteBloque->direccionImagen(),renderizador);
		texturasBloques[spriteBloque->direccionImagen()]=texturaNueva;
	}
	return texturasBloques[spriteBloque->direccionImagen()];
}


////----------------GETTERS--------------////

SDL_Texture* CargadorTexturas::obtenerTexturaMario(){
	return texturaMario;
}

SDL_Texture* CargadorTexturas::obtenerTexturaMoneda(){
	return texturaMoneda;
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

SDL_Texture* CargadorTexturas::obtenerTexturaFuente(){
	return texturaFuenteJuego;
}


CargadorTexturas::~CargadorTexturas(){
	SDL_DestroyTexture( texturaMario );
	SDL_DestroyTexture( texturaMoneda );
	SDL_DestroyTexture( texturaLadrillo );
	SDL_DestroyTexture( texturaSorpresa );
	SDL_DestroyTexture( texturaFondoActual );
	SDL_DestroyTexture( texturaFuenteJuego );

	for (auto const& parClaveEnemigo : texturasEnemigos){
		SDL_DestroyTexture( parClaveEnemigo.second );
	}

	for (auto const& parClaveBloque : texturasBloques){
		SDL_DestroyTexture( parClaveBloque.second );
	}


	TTF_CloseFont( fuenteJuego );
	TTF_Quit();
}
