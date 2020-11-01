

#include "CargadorTexturas.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <sstream>

#include "../log/Log.hpp"
#include "App.hpp"



CargadorTexturas::CargadorTexturas(SDL_Renderer* renderizador){
	Log* log = Log::getInstance();

	if( TTF_Init() == -1 ){
		log->huboUnErrorSDL("No se pudo inicializar SDL_ttf ", TTF_GetError());
	}

	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
		log->huboUnError("No se pudo activar el filtrado lineal de las texturas");
	}

	texturaMario = cargarTextura("resources/Imagenes/Personajes/mario_grande.png",renderizador);
	if( texturaMario == NULL ){
		log->huboUnError("No se pudo cargar ninguna imagen de Mario en: resources/Imagenes/Personajes/mario_grande.png");

	}
	else{
		log->mostrarMensajeDeCarga("Mario", "resources/Imagenes/Personajes/mario_grande.png");
	}

	texturaMoneda = cargarTextura("resources/Imagenes/Bloques/Monedas.png",renderizador);
	if(texturaMoneda == NULL){
		log->huboUnError("No se pudo cargar ninguna imagen de las monedas en: resources/Imagenes/Bloques/Monedas.png");
	}
	else{
		log->mostrarMensajeDeCarga("Moneda", "resources/Imagenes/Bloques/Monedas.png");
	}

	texturaLadrillo = cargarTextura( "resources/Imagenes/Bloques/BloqueLadrillo.png" ,renderizador);
	if( texturaLadrillo == NULL ){
		log->huboUnError("No se pudo cargar ninguna imagen del bloque ladrillo en: resources/Imagenes/Bloques/BloqueLadrillo.png");
	}
	else{
		log->mostrarMensajeDeCarga("Ladrillo", "resources/Imagenes/Bloques/BloqueLadrillo.png");
	}

	texturaSorpresa = cargarTextura("resources/Imagenes/Bloques/BloqueSorpresa.png",renderizador);
	if(texturaSorpresa == NULL){
		log->huboUnError("No se pudo cargar ninguna imagen del bloque sorpresa en: resources/Imagenes/Bloques/BloqueSorpresa.png");
	}
	else{
		log->mostrarMensajeDeCarga("Sorpresa", "resources/Imagenes/Bloques/BloqueSorpresa.png");
	}

	texturaFondoInicio = cargarTextura("resources/Imagenes/Niveles/fondoInicio.png", renderizador);
	if(texturaFondoInicio == NULL){
		log->huboUnError("No se pudo cargar el fondo del inicio del juego en: resources/Imagenes/Niveles/fondoInicio.png");
	}
	else{
		log->mostrarMensajeDeCarga("FondoInicio", "resources/Imagenes/Niveles/fondoInicio.png");
	}

	texturaTitulo = cargarTextura("resources/Imagenes/Titulos/Super_Mario_Bros_Titulo.png", renderizador);
	if(texturaTitulo == NULL){
		log->huboUnError("No se pudo cargar el fondo del inicio del juego en: resources/Imagenes/Titulos/Super_Mario_Bros_Titulo.png");
	}
	else{
		log->mostrarMensajeDeCarga("Titulo", "resources/Imagenes/Titulos/Super_Mario_Bros_Titulo.png");
	}

	texturaFondoGameOver = cargarTextura("resources/Imagenes/Niveles/fondoGameOver.png", renderizador);
	if(texturaFondoGameOver == NULL){
		log->huboUnError("No se pudo cargar el fondo del final del juego en: resources/Imagenes/Niveles/fondoGameOver.png");
	}
	else{
		log->mostrarMensajeDeCarga("FondoGameOver", "resources/Imagenes/Niveles/fondoGameOver.png");
	}

	texturaCoffinMario = cargarTextura("resources/Imagenes/Personajes/MarioCoffinDance.png", renderizador);
	if(texturaCoffinMario == NULL){
		log->huboUnError("No se pudo cargar la imagen de Coffin Mario en: resources/Imagenes/Personajes/MarioCoffinDance.png");
	}
	else{
		log->mostrarMensajeDeCarga("CoffinMario", "resources/Imagenes/Personajes/MarioCoffinDance.png");
	}


	string listaParticulas[]={"resources/Imagenes/Particulas/confetiAzul.png","resources/Imagenes/Particulas/confetiAmarillo.png",
							  "resources/Imagenes/Particulas/confetiRosa.png","resources/Imagenes/Particulas/confetiVerde.png"};

	for(auto const& particula:listaParticulas){
		SDL_Texture* particulaTextura = cargarTextura(particula, renderizador);
		if(particulaTextura == NULL){
			log->huboUnError("No se pudo cargar la particula en: "+ particula);
		}
		else{
			log->mostrarMensajeDeCarga("Particula", particula);
		}
		particulas[particula]=particulaTextura;
	}


	string listaPersonajes[]={"resources/Imagenes/PersonajesSaltando/PeachSaltando.png",
							  "resources/Imagenes/PersonajesSaltando/HonguitoSaltando.png",
							  "resources/Imagenes/PersonajesSaltando/YoshiSaltando.png"};

	for(auto const& personaje:listaPersonajes){
		SDL_Texture* personajeTextura = cargarTextura(personaje, renderizador);
		if(personajeTextura == NULL){
			log->huboUnError("No se pudo cargar el personaje en: "+ personaje);
		}
		else{
			log->mostrarMensajeDeCarga("Personaje", personaje);
		}
		texturasPersonajes[personaje]=personajeTextura;
	}

	string listaError[]={"resources/Imagenes/Bloques/BloqueError.png"};

	for(auto const& direccionTexturaError:listaError){
			SDL_Texture* texturaError = cargarTextura(direccionTexturaError, renderizador);
			if(texturaError == NULL){
				log->huboUnError("No se pudo cargar el personaje en: "+ direccionTexturaError);
			}
			else{
				log->mostrarMensajeDeCarga("Bloque", direccionTexturaError);
			}
			texturasError[direccionTexturaError]=texturaError;
		}


	int tamanioFuente = 20;
	string direccionFuente = "resources/Fuentes/fuenteSuperMarioBros.ttf";
	fuenteJuego = TTF_OpenFont( direccionFuente.c_str(), tamanioFuente);
	if(fuenteJuego==NULL){
		log->huboUnErrorSDL("No se pudo cargar la fuente del juego en: ", "resources/Fuentes/fuenteSuperMarioBros.ttf");
	}
	else{
		log->mostrarMensajeDeCarga("Fuente de texto del juego", "resources/Fuentes/fuenteSuperMarioBros.ttf");
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
		texturaFondoActual = this->texturasNiveles[direccionFondoActual];

	}
}

void CargadorTexturas::cargarTexturasNiveles(list<Nivel*> niveles, SDL_Renderer* renderizador){

	for(auto const& nivel : niveles){
		int altoNivel = 0;
		int largoNivel = 0;
		SDL_Texture* texturaNueva = cargarTextura(nivel->obtenerDireccionFondoActual() , renderizador);
		texturasNiveles[nivel->obtenerDireccionFondoActual()] = texturaNueva;
		SDL_QueryTexture(texturaNueva, NULL, NULL, &largoNivel, &altoNivel);
		nivel->definirDimesionesDelNivel(largoNivel, altoNivel);
	}

	texturaFondoActual = this->texturasNiveles[niveles.front()->obtenerDireccionFondoActual()];
	direccionFondoActual = niveles.front()->obtenerDireccionFondoActual();

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
			Log::getInstance()->huboUnErrorSDL("No se pudo crear una textura a partir de la imagen en " + direccion, SDL_GetError());
		}
		SDL_FreeSurface( superficieImagen );
	}
	return texturaCargada;
}


SDL_Texture* CargadorTexturas::obtenerTexturaEnemigo(Sprite* spriteEnemigo,SDL_Renderer* renderizador){
	if(!tengoTexturaCargadaEnMemoria(spriteEnemigo,texturasEnemigos)){
		SDL_Texture* texturaNueva = cargarTextura(spriteEnemigo->direccionImagen(),renderizador);
		texturasEnemigos[spriteEnemigo->direccionImagen()]=texturaNueva;
	}
	return texturasEnemigos[spriteEnemigo->direccionImagen()];
}

bool CargadorTexturas::tengoTexturaCargadaEnMemoria(Sprite* spriteBloque, map<string,SDL_Texture*> texturas){
	try{
		texturas.at(spriteBloque->direccionImagen());
	}
	catch(std::out_of_range&){
		return false;
	}
	return true;
}

SDL_Texture* CargadorTexturas::obtenerTexturaPersonaje(string personaje){
	return texturasPersonajes[personaje];
}

SDL_Texture* CargadorTexturas::obtenerTexturaBloque(Sprite* spriteBloque,SDL_Renderer* renderizador){

	if(!tengoTexturaCargadaEnMemoria(spriteBloque,texturasBloques)){
		SDL_Texture* texturaNueva = cargarTextura(spriteBloque->direccionImagen(),renderizador);
		if(texturaNueva == NULL){
			texturasBloques[spriteBloque->direccionImagen()] = texturasError["resources/Imagenes/Bloques/BloqueError.png"];

		}else{
			texturasBloques[spriteBloque->direccionImagen()]=texturaNueva;
		}
	}
	return texturasBloques[spriteBloque->direccionImagen()];
}


SDL_Texture* CargadorTexturas::obtenerParticula(string particulaAsociada){
	return particulas[particulaAsociada];
}


////----------------GETTERS--------------////

SDL_Texture* CargadorTexturas::obtenerTexturaMario(){
	return texturaMario;
}

SDL_Texture* CargadorTexturas::obtenerTexturaCoffinMario(){
	return texturaCoffinMario;
}

SDL_Texture* CargadorTexturas::obtenerTexturaFondoInicio(){
	return texturaFondoInicio;
}
SDL_Texture* CargadorTexturas::obtenerTexturaTitulo(){
	return texturaTitulo;
}
SDL_Texture* CargadorTexturas::obtenerTexturaFondoGameOver(){
	return texturaFondoGameOver;
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

	return this->texturasNiveles[this->direccionFondoActual];
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
	SDL_DestroyTexture( texturaCoffinMario );

	for (auto const& parClaveEnemigo : texturasEnemigos){
		SDL_DestroyTexture( parClaveEnemigo.second );
	}

	for (auto const& parClaveBloque : texturasBloques){
		SDL_DestroyTexture( parClaveBloque.second );
	}

	for (auto const& parClaveNivel : texturasNiveles){
		SDL_DestroyTexture( parClaveNivel.second );
	}

	for (auto const& parClaveParticula : particulas){
		SDL_DestroyTexture( parClaveParticula.second );
	}

	for (auto const& parClavePesonaje : texturasPersonajes){
		SDL_DestroyTexture( parClavePesonaje.second );
	}

	TTF_CloseFont( fuenteJuego );
	TTF_Quit();
}
