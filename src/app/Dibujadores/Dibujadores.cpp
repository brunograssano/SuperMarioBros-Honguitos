#include "Dibujadores.hpp"

Dibujadores::Dibujadores(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla, bool leidoCorrectamente){ // @suppress("Class members should be properly initialized")
	if(leidoCorrectamente){
		this->dibujadorGameOver = new DibujadorGameOver(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
		this->dibujadorInicio = new DibujadorInicio(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
		this->dibujadorGanadores = new DibujadorGanadores(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
		this->dibujadorJuego = new DibujadorJuego(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
		this->dibujadorError = nullptr;
	}
	else{
		this->dibujadorError = new DibujadorError(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
	}

}


void Dibujadores::dibujarPantallaGanadores(){
	dibujadorGanadores->dibujar();
}

void Dibujadores::dibujarInicio(){
	if(dibujadorError==nullptr){
		dibujadorInicio->dibujar();
	}
	else{
		dibujadorError->dibujar();
	}
}

void Dibujadores::dibujarGameOver(){
	dibujadorGameOver->dibujar();
}

void Dibujadores::dibujarJuego(SDL_Rect* rectanguloCamara){
	dibujadorJuego->dibujar(rectanguloCamara);
}

Dibujadores::~Dibujadores(){
	delete dibujadorGameOver;
	delete dibujadorInicio;
	delete dibujadorGanadores;
	delete dibujadorJuego;
	delete dibujadorError;
}
