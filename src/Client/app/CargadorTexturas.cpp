#include "CargadorTexturas.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "ManejadorSDL.hpp"
#include "../../Utils/log/Log.hpp"

CargadorTexturas::CargadorTexturas(SDL_Renderer* renderizador){
	Log* log = Log::getInstance();

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

    texturas["Moneda"] = intentarCarga("la imagen de moneda", "resources/Imagenes/Bloques/Monedas.png", renderizador);
    texturas["FondoInicio"]  = intentarCarga("el fondo del inicio del juego", "resources/Imagenes/Niveles/fondoInicio.png", renderizador);
    texturas["Titulo"]  = intentarCarga("el titulo", "resources/Imagenes/Titulos/Super_Mario_Bros_Titulo.png", renderizador);
    texturas["FondoGameOver"]  = intentarCarga("el fondo del final del juego","resources/Imagenes/Niveles/fondoGameOver.png",renderizador);
    texturas["Coffin"]  = intentarCarga("la imagen de Coffin Mario", "resources/Imagenes/Personajes/MarioCoffinDance.png", renderizador);
    texturas["Tuberia"]  = intentarCarga("la imagen de las tuberias","resources/Imagenes/Bloques/Tuberias.png",renderizador);
    texturas["Corazon"]  = intentarCarga("la imagen de un corazon","resources/Imagenes/Objetos/Corazon.png",renderizador);
    texturas["BolaDeFuego"] = intentarCarga("la imagen de la bola de fuego", "resources/Imagenes/Objetos/BolaDeFuego.png", renderizador);
    texturas["Bloques"]  = intentarCarga("la imagen de los bloques","resources/Imagenes/Bloques/Bloques.png",renderizador);
    texturas["Goombas"]  = intentarCarga("la imagen de los Goomba","resources/Imagenes/Personajes/Goombas.png",renderizador);
    texturas["Koopas"]  = intentarCarga("la imagen de los Koopas","resources/Imagenes/Personajes/Koopas.png",renderizador);
    texturaDefecto = cargarTextura("resources/Imagenes/ImagenError.png", renderizador);

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

	int tamanioFuente = 20;

	string direccionFuente = "resources/Fuentes/fuenteSuperMarioBros.ttf";
	fuenteJuego = TTF_OpenFont( direccionFuente.c_str(), tamanioFuente);
	if(fuenteJuego== nullptr){
		log->huboUnErrorSDL("No se pudo cargar la fuente del juego en: ", "resources/Fuentes/fuenteSuperMarioBros.ttf");
	}
	else{
		log->mostrarMensajeDeCarga("Fuente de texto del juego", "resources/Fuentes/fuenteSuperMarioBros.ttf");
	}

	log->mostrarMensajeDeInfo("Ha finalizado la carga de imagenes");
}

SDL_Texture* CargadorTexturas::cargarFuenteDeTextoATextura(const string& textoAMostrar, SDL_Renderer* renderizador, SDL_Color colorTexto){
	Log* log = Log::getInstance();

	SDL_Surface* superficeDeTexto = TTF_RenderText_Solid( fuenteJuego, textoAMostrar.c_str(), colorTexto );
	if( superficeDeTexto == nullptr ){
		log->huboUnErrorSDL("No se pudo convertir el mensaje a superficie : "+ textoAMostrar +" a una superficie.", TTF_GetError());
		return nullptr;
	}

	SDL_Texture* texturaCargada = SDL_CreateTextureFromSurface( renderizador, superficeDeTexto );
	if( texturaCargada == nullptr ){
		log->huboUnErrorSDL( "No se pudo crear una textura a partir de un texto renderizado. ", SDL_GetError() );
	}

	SDL_FreeSurface( superficeDeTexto );

	return texturaCargada;
}

void CargadorTexturas::revisarSiCambioNivel(string direccionFondo) {
	direccionFondo = "resources/Imagenes/Niveles/" + direccionFondo;

	if(direccionFondoActual != direccionFondo){
		destructorDeTexturas(texturaFondoActual);
		direccionFondoActual = direccionFondo;
		texturaFondoActual = this->texturasNiveles[direccionFondoActual];
	}
}

void CargadorTexturas::cargarTexturasNiveles(map<int, string> direccionesNiveles, SDL_Renderer *renderizador,unsigned short mundo) {
	string direccion;
	SDL_Texture* texturaNueva;
	string prefijo = "resources/Imagenes/Niveles/";

	for (auto const& parMundoDireccion : direccionesNiveles){
	  direccion = prefijo + parMundoDireccion.second;
	  texturaNueva = intentarCarga("Fondo Nivel", direccion, renderizador);
	  texturasNiveles[direccion] = texturaNueva;
	}

	texturaFondoActual = this->texturasNiveles[prefijo + direccionesNiveles[mundo]];
	direccionFondoActual = prefijo + direccionesNiveles[mundo];
}

SDL_Texture* CargadorTexturas::cargarTextura(const std::string& direccion, SDL_Renderer* renderizador){
	SDL_Texture*  texturaCargada= nullptr;
	SDL_Surface* superficieImagen = IMG_Load(direccion.c_str());
	if(superficieImagen == nullptr){
		Log::getInstance()->huboUnErrorSDL("No se pudo cargar una imagen en " + direccion, IMG_GetError());
	}
	else{
		texturaCargada = SDL_CreateTextureFromSurface( renderizador, superficieImagen );
		if( texturaCargada == nullptr ){
			Log::getInstance()->huboUnErrorSDL("No se pudo crear una textura a partir de la imagen en " + direccion, SDL_GetError());
		}
		SDL_FreeSurface( superficieImagen );
	}
	return texturaCargada;
}

SDL_Texture* CargadorTexturas::intentarCarga(const std::string& descripcion, const std::string& direccion, SDL_Renderer* renderizador){
	SDL_Texture* texturaCargada =  cargarTextura(direccion, renderizador);
	if(texturaCargada == nullptr){
		texturaCargada = texturaDefecto;
		Log::getInstance()->huboUnError("No se pudo cargar " + descripcion +" en: "+ direccion + ". Se cargo la textura por defecto.");
	}else{
		Log::getInstance()->mostrarMensajeDeCarga(descripcion, direccion);
	}
	return texturaCargada;
}

SDL_Texture* CargadorTexturas::obtenerTexturaPersonaje(const string& personaje){
	return texturasPersonajes[personaje];
}

SDL_Texture* CargadorTexturas::obtenerParticula(const string& particulaAsociada){
	return particulas[particulaAsociada];
}

////----------------GETTERS--------------////

SDL_Texture* CargadorTexturas::obtenerTexturaMario(int idMario){
	return texturasMario[idMario];
}

SDL_Texture* CargadorTexturas::obtenerTextura(const string& clave){
    return texturas[clave];
}

SDL_Texture* CargadorTexturas::obtenerTexturaFondo(){
	return texturasNiveles[direccionFondoActual];
}

CargadorTexturas::~CargadorTexturas(){
	destructorDeTexturas(texturaFondoActual);
	destructorDeTexturas(texturaFuenteJuego);
	destructorDeTexturas(texturaDefecto);

    for (auto const& parClaveTextura : texturas){
        destructorDeTexturas(parClaveTextura.second);
    }

	for (auto const& parClaveMario : texturasMario){
		destructorDeTexturas(parClaveMario.second);
	}

	for (auto const& parClaveNivel : texturasNiveles){
		destructorDeTexturas(parClaveNivel.second);
	}

	for (auto const& parClaveParticula : particulas){
		destructorDeTexturas(parClaveParticula.second);
	}

	for (auto const& parClavePesonaje : texturasPersonajes){
		destructorDeTexturas(parClavePesonaje.second);
	}

	TTF_CloseFont( fuenteJuego );
}
