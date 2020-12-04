#include "BotonConTexto.hpp"
#include "../../../Utils/log/Log.hpp"

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
		log->huboUnErrorSDL("No se pudo renderizar la superficie", SDL_GetError());
		log->huboUnErrorSDL(texto, SDL_GetError());
	}
	return texturaACargar;
}

BotonConTexto::BotonConTexto(int posicionX, int posicionY, int ancho, int alto , string texto, SDL_Renderer* renderer, TTF_Font* fuente){
	Log* log = Log::getInstance();
	this->rectangulo = {posicionX, posicionY, ancho , alto };
	this->texto = texto;
	this->fuente = fuente;
	this->renderer = renderer;
	this->texturaTexto = this->cargoTextura(texto);

}

void BotonConTexto::cambiarTexto(string texto){
	this->texto = texto;
	SDL_Texture* texturaABorrar = this->texturaTexto;
	if(!texto.empty()){
		this->texturaTexto = this->cargoTextura(texto);
	}else{
		this->texturaTexto = this->cargoTextura("...");
	}

	SDL_DestroyTexture( texturaABorrar );
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

void renderizar(int coordenadaX,int coordenadaY,int alto,int ancho,SDL_Texture* textura,SDL_Renderer* renderer){
		SDL_Rect renderQuad = { coordenadaX, coordenadaY, ancho, alto };
		SDL_Rect* clip = NULL;
		double angle = 0.0;
		SDL_Point* center = NULL;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		SDL_RenderCopyEx( renderer, textura, clip, &renderQuad, angle, center, flip );
}

void BotonConTexto::mostrarse(){

	renderizar(rectangulo.x + rectangulo.x*0.05,rectangulo.y + rectangulo.y *0.05 ,rectangulo.h * 0.7,rectangulo.w * 0.7,texturaTexto,renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF );

	SDL_RenderDrawRect(renderer, &rectangulo);
}

void BotonConTexto::mostrarseCambiandoAncho(int nuevoAncho){

	renderizar(rectangulo.x ,rectangulo.y,rectangulo.h , nuevoAncho,texturaTexto,renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF );

	SDL_RenderDrawRect(renderer, &rectangulo);
}
