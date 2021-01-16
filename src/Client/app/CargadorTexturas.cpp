#include "CargadorTexturas.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "ManejadorSDL.hpp"
#include "../../Utils/log/Log.hpp"
#include "../../Utils/Constantes.hpp"

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

    texturas[CLAVE_TEXTURA_MONEDA] = intentarCarga("la imagen de moneda", "resources/Imagenes/Bloques/Monedas.png", renderizador);
    texturas[CLAVE_TEXTURA_FONDO_INICIO]  = intentarCarga("el fondo del inicio del juego", "resources/Imagenes/Niveles/fondoInicio.png", renderizador);
    texturas[CLAVE_TEXTURA_TITULO]  = intentarCarga("el titulo", "resources/Imagenes/Titulos/Super_Mario_Bros_Titulo.png", renderizador);
    texturas[CLAVE_TEXTURA_GAMEOVER]  = intentarCarga("el fondo del final del juego","resources/Imagenes/Niveles/fondoGameOver.png",renderizador);
    texturas[CLAVE_TEXTURA_COFFIN_MARIO]  = intentarCarga("la imagen de Coffin Mario", "resources/Imagenes/Personajes/MarioCoffinDance.png", renderizador);
    texturas[CLAVE_TEXTURA_TUBERIAS]  = intentarCarga("la imagen de las tuberias","resources/Imagenes/Bloques/Tuberias.png",renderizador);
    texturas[CLAVE_TEXTURA_CORAZON]  = intentarCarga("la imagen de un corazon","resources/Imagenes/Objetos/Corazon.png",renderizador);
    texturas[CLAVE_TEXTURA_BOLA_DE_FUEGO] = intentarCarga("la imagen de la bola de fuego", "resources/Imagenes/Objetos/BolaDeFuego.png", renderizador);
    texturas[CLAVE_TEXTURA_CHISPA] = intentarCarga("la imagen de la chispa", "resources/Imagenes/Objetos/Chispa.png", renderizador);
    texturas[CLAVE_TEXTURA_FLOR] = intentarCarga("la imagen de las flores", "resources/Imagenes/Objetos/Flores.png", renderizador);
    texturas[CLAVE_TEXTURA_MONEDA_FLOTANTE] = intentarCarga("la imagen de la moneda sorpresa", "resources/Imagenes/Objetos/MonedaFlotante.png", renderizador);
    texturas[CLAVE_TEXTURA_POZO]  = intentarCarga("la imagen de los pozos","resources/Imagenes/Bloques/Pozos.png",renderizador);
    texturas[CLAVE_TEXTURA_FONDO_POZO]  = intentarCarga("la imagen de los fondos de lospozos","resources/Imagenes/Bloques/FondoPozos.png",renderizador);


    texturas[CLAVE_TEXTURA_BLOQUES]  = intentarCarga("la imagen de los bloques","resources/Imagenes/Bloques/Bloques.png",renderizador);
    texturas[CLAVE_TEXTURA_GOOMBA]  = intentarCarga("la imagen de los Goomba","resources/Imagenes/Personajes/Goombas.png",renderizador);
    texturas[CLAVE_TEXTURA_KOOPAS]  = intentarCarga("la imagen de los Koopas","resources/Imagenes/Personajes/Koopas.png",renderizador);

    texturas[CLAVE_TEXTURA_PEACH_SALTANDO]  = intentarCarga("la imagen de Peach saltando","resources/Imagenes/PersonajesSaltando/PeachSaltando.png",renderizador);
    texturas[CLAVE_TEXTURA_TOAD_SALTANDO]  = intentarCarga("la imagen de Toad saltando","resources/Imagenes/PersonajesSaltando/HonguitoSaltando.png",renderizador);
    texturas[CLAVE_TEXTURA_YOSHI_SALTANDO]  = intentarCarga("la imagen de Yoshi saltando","resources/Imagenes/PersonajesSaltando/YoshiSaltando.png",renderizador);

    texturaDefecto = intentarCarga("la imagen por defecto","resources/Imagenes/ImagenError.png",renderizador);

    string listaParticulas[]={"resources/Imagenes/Particulas/confetiAzul.png","resources/Imagenes/Particulas/confetiAmarillo.png",
                              "resources/Imagenes/Particulas/confetiRosa.png","resources/Imagenes/Particulas/confetiVerde.png"};

    for(auto const& particula:listaParticulas){
		SDL_Texture* particulaTextura = intentarCarga("la particula", particula, renderizador);
		particulas[particula]=particulaTextura;
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

    revisarCargaCorrecta(texturas);
    revisarCargaCorrecta(particulas);

    log->mostrarMensajeDeInfo("Ha finalizado la carga de imagenes");
}

void CargadorTexturas::revisarCargaCorrecta(map<string, SDL_Texture *> texturasCargadas) {
    for(auto parClaveTextura:texturasCargadas){
        if(parClaveTextura.second==nullptr){
            parClaveTextura.second = texturaDefecto;
        }
    }
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

void CargadorTexturas::revisarSiCambioNivel(string nombreFondo) {
    nombreFondo = DIRECCION_BASE_NIVELES + nombreFondo;

	if(direccionFondoActual != nombreFondo){
		destructorDeTexturas(texturaFondoActual);
		direccionFondoActual = nombreFondo;
		texturaFondoActual = this->texturasNiveles[direccionFondoActual];
	}
}

void CargadorTexturas::cargarTexturasNiveles(map<int, string> direccionesNiveles, SDL_Renderer *renderizador,unsigned short mundo) {
	string direccion;
	SDL_Texture* texturaNueva;
	string prefijo = DIRECCION_BASE_NIVELES;

	for (auto const& parMundoDireccion : direccionesNiveles){
	  direccion = prefijo + parMundoDireccion.second;
	  texturaNueva = intentarCarga("Fondo Nivel", direccion, renderizador);
	  texturasNiveles[direccion] = texturaNueva == nullptr ? texturaDefecto : texturaNueva;
	}

	texturaFondoActual = this->texturasNiveles[prefijo + direccionesNiveles[mundo]];
	direccionFondoActual = prefijo + direccionesNiveles[mundo];
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

void CargadorTexturas::destruirTexturasEnMapa(const map<string, SDL_Texture *>& mapaDeTexturas) {
    for (auto const& parClaveTextura : mapaDeTexturas){
        destructorDeTexturas(parClaveTextura.second);
    }
}

CargadorTexturas::~CargadorTexturas(){
	destructorDeTexturas(texturaFondoActual);
	destructorDeTexturas(texturaFuenteJuego);
	destructorDeTexturas(texturaDefecto);

    destruirTexturasEnMapa(texturas);
    destruirTexturasEnMapa(texturasNiveles);
    destruirTexturasEnMapa(particulas);
    for (auto const& parClaveMario : texturasMario){
        destructorDeTexturas(parClaveMario.second);
    }

	TTF_CloseFont( fuenteJuego );
}
