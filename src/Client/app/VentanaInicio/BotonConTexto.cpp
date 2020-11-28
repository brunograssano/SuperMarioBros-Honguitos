#include "BotonConTexto.hpp"


BotonConTexto::BotonConTexto(int posicionX, int posicionY, int ancho, int alto , SDL_Texture* texto){
	this->rectangulo = {posicionX, posicionY, ancho , alto };
	this->texto = texto;
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

void BotonConTexto::mostrarse(SDL_Renderer* renderer){

	renderizar(rectangulo.x + rectangulo.x*0.05,rectangulo.y + rectangulo.y *0.05 ,rectangulo.h * 0.7,rectangulo.w * 0.7,texto,renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF );

	SDL_RenderDrawRect(renderer, &rectangulo);
}
