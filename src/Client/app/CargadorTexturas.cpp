

#include "CargadorTexturas.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <sstream>

#include "../../Utils/log/Log.hpp"
#include "AplicacionCliente.hpp"



CargadorTexturas::CargadorTexturas(SDL_Renderer* renderizador){
	Log* log = Log::getInstance();

	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
		log->huboUnError("No se pudo activar el filtrado lineal de las texturas");
	}

	string listaMarios[]={"resources/Imagenes/Personajes/MarioRojo.png","resources/Imagenes/Personajes/MarioVerde.png",
						"resources/Imagenes/Personajes/MarioVioleta.png","resources/Imagenes/Personajes/MarioCeleste.png",
						"resources/Imagenes/Personajes/MarioGrisPerdioConexion.png"};
	int i = 0;
	for(auto const& dirMario:listaMarios){
		if(i==4){
			i=-1; // Asi el mario gris concuerda con el valor que nos mandan
		}
		SDL_Texture* texturaMario = intentarCarga("la imagen de mario", dirMario, renderizador);
		texturasMario[i]=texturaMario;
		i++;
	}

	texturaMoneda = intentarCarga("la imagen de moneda", "resources/Imagenes/Bloques/Monedas.png", renderizador);

	texturaLadrillo = intentarCarga("imagen del bloque ladrillo", "resources/Imagenes/Bloques/BloqueLadrillo.png", renderizador);

	texturaSorpresa = intentarCarga("la textura sorpresa", "resources/Imagenes/Bloques/BloqueSorpresa.png", renderizador);

	texturaFondoInicio = intentarCarga("el fondo del inicio del juego", "resources/Imagenes/Niveles/fondoInicio.png", renderizador);

	texturaTitulo = intentarCarga("el titulo", "resources/Imagenes/Titulos/Super_Mario_Bros_Titulo.png", renderizador);

	texturaFondoGameOver = intentarCarga("el fondo del final del juego","resources/Imagenes/Niveles/fondoGameOver.png",renderizador);

	texturaCoffinMario = intentarCarga("la imagen de Coffin Mario", "resources/Imagenes/Personajes/MarioCoffinDance.png", renderizador);

	string listaParticulas[]={"resources/Imagenes/Particulas/confetiAzul.png","resources/Imagenes/Particulas/confetiAmarillo.png",
							  "resources/Imagenes/Particulas/confetiRosa.png","resources/Imagenes/Particulas/confetiVerde.png"};

	texturaDefecto = cargarTextura("resources/Imagenes/ImagenError.png", renderizador);

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

void CargadorTexturas::cargarTexturasNiveles(string direccionesNiveles[MAX_IMAGEN_NIVELES],int cantidadFondosNiveles, SDL_Renderer* renderizador){

	for(int i=0;i<cantidadFondosNiveles;i++){
		direccionesNiveles[i] = "resources/Imagenes/Niveles/" + direccionesNiveles[i];
		SDL_Texture* texturaNueva = intentarCarga("Fondo Nivel", direccionesNiveles[i], renderizador);
		texturasNiveles[direccionesNiveles[i]] = texturaNueva;
	}

	texturaFondoActual = this->texturasNiveles[direccionesNiveles[0]];
	direccionFondoActual = direccionesNiveles[0];

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
		texturaCargada = texturaDefecto;
		Log::getInstance()->huboUnError("No se pudo cargar " + descripcion +" en: "+ direccion + ". Se cargo la textura por defecto.");
	}else{
		Log::getInstance()->mostrarMensajeDeCarga(descripcion, direccion);
	}
	return texturaCargada;
}

bool CargadorTexturas::tengoTexturaCargadaEnMemoria(string spriteDireccion, map<string,SDL_Texture*> texturas){
	try{
		texturas.at(spriteDireccion);
	}
	catch(std::out_of_range&){
		return false;
	}
	return true;
}

SDL_Texture* CargadorTexturas::obtenerTexturaEnemigo(string spriteEnemigoDireccion,SDL_Renderer* renderizador){

	if(!tengoTexturaCargadaEnMemoria(spriteEnemigoDireccion,texturasEnemigos)){
		SDL_Texture* texturaNueva = intentarCarga("un enemigo", spriteEnemigoDireccion,renderizador);
		texturasEnemigos[spriteEnemigoDireccion]=texturaNueva;
	}
	return texturasEnemigos[spriteEnemigoDireccion];
}



SDL_Texture* CargadorTexturas::obtenerTexturaPersonaje(string personaje){
	return texturasPersonajes[personaje];
}

SDL_Texture* CargadorTexturas::obtenerTexturaBloque(string spriteDireccionBloque,SDL_Renderer* renderizador){

	if(!tengoTexturaCargadaEnMemoria(spriteDireccionBloque,texturasBloques)){
		SDL_Texture* texturaNueva = intentarCarga("un bloque", spriteDireccionBloque, renderizador);
		texturasBloques[spriteDireccionBloque]=texturaNueva;
	}
	return texturasBloques[spriteDireccionBloque];
}


SDL_Texture* CargadorTexturas::obtenerParticula(string particulaAsociada){
	return particulas[particulaAsociada];
}


////----------------GETTERS--------------////

SDL_Texture* CargadorTexturas::obtenerTexturaMario(int idMario){
	return texturasMario[idMario];
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

	SDL_DestroyTexture( texturaMoneda );
	SDL_DestroyTexture( texturaLadrillo );
	SDL_DestroyTexture( texturaSorpresa );
	SDL_DestroyTexture( texturaFondoActual );
	SDL_DestroyTexture( texturaFuenteJuego );
	SDL_DestroyTexture( texturaCoffinMario );
	SDL_DestroyTexture( texturaDefecto);

	for (auto const& parClaveMario : texturasMario){
		SDL_DestroyTexture( parClaveMario.second );
	}

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
