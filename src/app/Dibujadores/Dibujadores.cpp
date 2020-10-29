#include "Dibujadores.h"

Dibujadores::Dibujadores(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador,SpriteMario* spriteMario, int ancho_pantalla,int alto_pantalla){ // @suppress("Class members should be properly initialized")
	this->dibujadorGameOver = new DibujadorGameOver(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
	this->dibujadorInicio = new DibujadorInicio(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
	this->dibujadorGanadores = new DibujadorGanadores(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
	this->dibujadorJuego = new DibujadorJuego(cargadorTexturas, renderizador,spriteMario, ancho_pantalla, alto_pantalla);
}


void Dibujadores::dibujarPantallaGanadores(){
	dibujadorGanadores->dibujar();
}

void Dibujadores::dibujarInicio(){
	dibujadorInicio->dibujar();
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
}
