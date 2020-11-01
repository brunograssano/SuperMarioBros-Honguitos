

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

	texturaMario = intentarCarga("la imagen de Mario", "resources/Imagenes/Personajes/mario_grande.png",renderizador);

	texturaMoneda = intentarCarga("la imagen de moneda", "resources/Imagenes/Bloques/Monedas.png", renderizador);

	texturaLadrillo = intentarCarga("imagen del bloque ladrillo", "resources/Imagenes/Bloques/BloqueLadrillo.png", renderizador);

	texturaSorpresa = intentarCarga("la textura sorpresa", "resources/Imagenes/Bloques/BloqueSorpresa.png", renderizador);

	texturaFondoInicio = intentarCarga("el fondo del inicio del juego", "resources/Imagenes/Niveles/fondoInicio.png", renderizador);

	texturaTitulo = intentarCarga("el titulo", "resources/Imagenes/Titulos/Super_Mario_Bros_Titulo.png", renderizador);

	texturaFondoGameOver = intentarCarga("el fondo del final del juego","resources/Imagenes/Niveles/fondoGameOver.png",renderizador);

	texturaCoffinMario = intentarCarga("la imagen de Coffin Mario", "resources/Imagenes/Personajes/MarioCoffinDance.png", renderizador);

	string listaParticulas[]={"resources/Imagenes/Particulas/confetiAzul.png","resources/Imagenes/Particulas/confetiAmarillo.png",
							  "resources/Imagenes/Particulas/confetiRosa.png","resources/Imagenes/Particulas/confetiVerde.png"};

	for(auto const& particula:listaParticulas){
		SDL_Texture* particulaTextura = intentarCarga("la particula", particula, renderizador);
		particulas[particula]=particulaTextura;
	}


	string listaPersonajes[]={"resources/Imagenes/PersonajesSaltando/PeachSaltando.png",
							  "resources/Imagenes/PersonajesSaltando/HonguitoSaltando.png",
							  "resources/Imagenes/PersonajesSaltando/YoshiSaltando.png"};

	for(auto const& personaje:listaPersonajes){
		SDL_Texture* personajeTextura = intentarCarga("el personaje", personaje, renderizador);
		texturasPersonajes[personaje]=personajeTextura;
	}

	string listaError[]={"resources/Imagenes/Bloques/BloqueError.png",
						 "resources/Imagenes/Personajes/EnemigoError.png"};

	for(auto const& direccionTexturaError:listaError){
		SDL_Texture* texturaError = intentarCarga("Una textura de error", direccionTexturaError, renderizador);
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

SDL_Texture* CargadorTexturas::intentarCarga(std::string descripcion, std::string direccion, SDL_Renderer* renderizador){
	SDL_Texture* texturaCargada =  cargarTextura(direccion, renderizador);
		if(texturaCargada == NULL){
			Log::getInstance()->huboUnError("No se pudo cargar " + descripcion +" en: "+ direccion);
		}else{
			Log::getInstance()->mostrarMensajeDeCarga(descripcion, direccion);
		}
	return texturaCargada;
}


SDL_Texture* CargadorTexturas::obtenerTexturaEnemigo(Sprite* spriteEnemigo,SDL_Renderer* renderizador){

	if(!tengoTexturaCargadaEnMemoria(spriteEnemigo,texturasEnemigos)){
		SDL_Texture* texturaNueva = intentarCarga("un enemigo", spriteEnemigo->direccionImagen(),renderizador);
		if(texturaNueva == NULL){
			texturasEnemigos[spriteEnemigo->direccionImagen()]=texturasError["resources/Imagenes/Personajes/EnemigoError.png"];
		}else{
			texturasEnemigos[spriteEnemigo->direccionImagen()]=texturaNueva;
		}
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
		SDL_Texture* texturaNueva = intentarCarga("un bloque", spriteBloque->direccionImagen(), renderizador);
		if(texturaNueva == NULL){
			texturasBloques[spriteBloque->direccionImagen()] = texturasError["resources/Imagenes/Bloques/BloqueError.png"];
			Log::getInstance()->mostrarMensajeDeCarga("un bloque de error", "resources/Imagenes/Bloques/BloqueError.png");
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
