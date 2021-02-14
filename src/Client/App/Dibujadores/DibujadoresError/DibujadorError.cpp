
#include "DibujadorError.hpp"

DibujadorError::DibujadorError(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla){
	this->alto_pantalla = alto_pantalla;
	this->ancho_pantalla = ancho_pantalla;
	this->cargadorTexturas = cargadorTexturas;
	this->renderizador = renderizador;
}

void DibujadorError::dibujar(){
	SDL_SetRenderDrawColor( renderizador, 0, 0, 0, 255 );
	SDL_RenderClear( renderizador );

    std::stringstream textoError;
	textoError.str("");
	textoError << "Ocurrio un error, revise que tenga bien la configuracion default. Para mas detalles ver el log";
	int ancho_textoError = 770;
	int alto_textoError = 40;
	SDL_Rect cuadradoFin = {20,
							alto_pantalla/2 - alto_textoError/2,
							ancho_textoError,
							alto_textoError};



	renderizarTexto(cuadradoFin, textoError.str(), colorDefault);

	SDL_RenderPresent( renderizador );
}
