#include "Dibujadores.hpp"

Dibujadores::Dibujadores(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla, bool leidoCorrectamente){ // @suppress("Class members should be properly initialized")
	archivoBienLeido = leidoCorrectamente;
	this->dibujadorGameOver = new DibujadorGameOver(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
	this->dibujadorInicio = new DibujadorInicio(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
	this->dibujadorGanadores = new DibujadorGanadores(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
	this->dibujadorJuego = new DibujadorJuego(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
	this->dibujadorError = nullptr;
	this->dibujadorError = new DibujadorError(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
	this->dibujadorErrorServidor = new DibujadorErrorServidor(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
    this->dibujadorFinNivel = new DibujadorFinNivel(cargadorTexturas, renderizador, ancho_pantalla, alto_pantalla);
}

void Dibujadores::dibujarPantallaGanadores(JuegoCliente* juegoCliente){
	dibujadorGanadores->dibujar(juegoCliente);
}

void Dibujadores::dibujarInicio(){
	if(archivoBienLeido){
		dibujadorInicio->dibujar();
	}
	else{
		dibujadorError->dibujar();
	}
}

void Dibujadores::dibujarPantallaFinNivel(JuegoCliente* juegoCliente){
    dibujadorFinNivel->dibujar(juegoCliente);
}


void Dibujadores::dibujarGameOver(){
	dibujadorGameOver->dibujar();
}

void Dibujadores::dibujarErrorServidor(){
	dibujadorErrorServidor->dibujar();
}

void Dibujadores::dibujarJuego(SDL_Rect* rectanguloCamara,JuegoCliente* juegoCliente){
	dibujadorJuego->dibujar(rectanguloCamara,juegoCliente);
}

void Dibujadores::agregarEventoADibujadores(SDL_Event eventoClick){
    dibujadorGanadores->agregarEventoDeClick(eventoClick);
}

Dibujadores::~Dibujadores(){
	delete dibujadorGameOver;
	delete dibujadorInicio;
	delete dibujadorGanadores;
	delete dibujadorJuego;
	delete dibujadorError;
}
