#include "BotonConTexto.hpp"
#include "../../../Utils/log/Log.hpp"
#include "../ManejadorSDL.hpp"
#define ANCHO_MAXIMO_TEXTO 270

SDL_Texture* BotonConTexto::cargoTextura(string texto){
	Log* log = Log::getInstance();
	SDL_Color color = { 255, 255, 255, 0xFF };
	SDL_Texture* texturaACargar;
	SDL_Surface* textSurface = TTF_RenderText_Solid( this->fuente, texto.c_str(), color );
	if( textSurface != NULL ){
		texturaACargar = SDL_CreateTextureFromSurface( this->renderer, textSurface );
		if( texturaACargar == NULL ){
			log->huboUnErrorSDL("No se pudo crear la textura", SDL_GetError());
		}

		SDL_FreeSurface( textSurface );
	}
	else{
		log->huboUnErrorSDL("No se pudo renderizar la superficie para el texto: " + texto, SDL_GetError());
	}
	return texturaACargar;
}

BotonConTexto::BotonConTexto(int posicionX, int posicionY, int ancho, int alto , string texto, SDL_Renderer* renderer, TTF_Font* fuente){
	this->rectangulo = {posicionX, posicionY, ancho , alto };
	this->texto = texto;
	this->fuente = fuente;
	this->renderer = renderer;
	this->texturaTexto = this->cargoTextura(texto);
	clickeado = false;
	ocultadorDeTexto = new OcultadorDeTextoNulo();
}

void BotonConTexto::ocultaTexto(){
	delete ocultadorDeTexto;
	ocultadorDeTexto = new OcultadorDeTextoAstericos();
}

void BotonConTexto::cambiarTexto(string texto){
	this->texto = texto;
	SDL_Texture* texturaABorrar = this->texturaTexto;
	if(!texto.empty()){
		this->texturaTexto = this->cargoTextura(ocultadorDeTexto->ocultar(texto));
	}else{
		if(clickeado){
			this->texturaTexto = this->cargoTextura(" ");
		}else{
			this->texturaTexto = this->cargoTextura("...");
		}
	}
	destructorDeTexturas(texturaABorrar);
}

bool BotonConTexto::botonClickeado(SDL_Event evento){
    //If a mouse button was pressed
    if( evento.type == SDL_MOUSEBUTTONDOWN ){
        //If the left mouse button was pressed
        if( evento.button.button == SDL_BUTTON_LEFT )
        {
            int posicionXClick = evento.button.x;
            int posicionYClick = evento.button.y;
            return ( ( posicionXClick > rectangulo.x ) && ( posicionXClick < rectangulo.x + rectangulo.w ) && ( posicionYClick > rectangulo.y ) && ( posicionYClick < rectangulo.y + rectangulo.h ) );
        }
    }
    return false;
}

void BotonConTexto::seleccionarCajaTexto(){
	clickeado = true;
}

void BotonConTexto::deseleccionarCajaTexto(){
	clickeado = false;
}

void BotonConTexto::mostrarse(){

	if(clickeado){
		SDL_SetRenderDrawColor(renderer, 50, 65, 93, 0xFF );
	}else{
		SDL_SetRenderDrawColor(renderer, 109, 132, 176, 0xFF );
	}
	SDL_RenderFillRect(renderer, &rectangulo);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF );
	SDL_RenderDrawRect(renderer, &rectangulo);
	renderizar(rectangulo.x + 5,rectangulo.y + rectangulo.y *0.05 ,rectangulo.h * 0.7,rectangulo.w * 0.9,texturaTexto,renderer);
}

void BotonConTexto::mostrarseCambiandoAncho(){
    int nuevoAncho = texto.length()*10;
    if(texto.empty()){
        nuevoAncho = 30;
    }

    if(nuevoAncho>ANCHO_MAXIMO_TEXTO){
        nuevoAncho = ANCHO_MAXIMO_TEXTO;
    }

	if(clickeado){
		SDL_SetRenderDrawColor(renderer, 50, 65, 93, 0xFF );
	}else{
		SDL_SetRenderDrawColor(renderer, 109, 132, 176, 0xFF );
	}
	SDL_RenderFillRect(renderer, &rectangulo);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF );
	SDL_RenderDrawRect(renderer, &rectangulo);
	renderizar(rectangulo.x ,rectangulo.y,rectangulo.h ,nuevoAncho ,texturaTexto,renderer);
}

BotonConTexto::~BotonConTexto(){
	delete ocultadorDeTexto;
}
