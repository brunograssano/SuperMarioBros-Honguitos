#include "Dibujador.h"
#include "App.h"

Dibujador::Dibujador(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador,SpriteMario* spriteMario, int ancho_pantalla,int alto_pantalla){ // @suppress("Class members should be properly initialized")
	this->dibujadorGameOver = new DibujadorGameOver(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
	this->dibujadorInicio = new DibujadorInicio(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
	this->dibujadorGanadores = new DibujadorGanadores(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
	this->dibujadorJuego = new DibujadorJuego(cargadorTexturas, renderizador,spriteMario, ancho_pantalla, alto_pantalla);
}


void Dibujador::dibujarPantallaGanadores(){
	dibujadorGanadores->dibujar();
}

void Dibujador::dibujarInicio(){
	dibujadorInicio->dibujar();
}

void Dibujador::dibujarGameOver(){
	dibujadorGameOver->dibujar();
}

void Dibujador::dibujarJuego(SDL_Rect* rectanguloCamara){
	dibujadorJuego->dibujar(rectanguloCamara);
}

Dibujador::~Dibujador(){
	delete dibujadorGameOver;
	delete dibujadorInicio;
	delete dibujadorGanadores;
	delete dibujadorJuego;
}
