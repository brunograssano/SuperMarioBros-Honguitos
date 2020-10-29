#include "DibujadorGanadores.h"

DibujadorGanadores::DibujadorGanadores(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla){
	this->cargadorTexturas = cargadorTexturas;
	this->renderizador= renderizador;
	this->ancho_pantalla = ancho_pantalla;
	this->alto_pantalla = alto_pantalla;
}

void DibujadorGanadores::dibujar(){
	SDL_SetRenderDrawColor( renderizador, 0, 0, 0, 255 );
	SDL_RenderClear( renderizador );

	stringstream textoFelicitaciones;
	textoFelicitaciones.str("");
	textoFelicitaciones << "GANARON EL JUEGO!";
	int ancho_textoFelicitaciones = 400;
	int alto_textoFelicitaciones = 60;
	SDL_Rect cuadradoFin = {ancho_pantalla/2 -ancho_textoFelicitaciones/2,
							alto_pantalla/2 - alto_textoFelicitaciones/2,
							ancho_textoFelicitaciones,
							alto_textoFelicitaciones}; //Los coloco en el centro.

	Juego* juego = Juego::getInstance();
	stringstream puntosJugador;
	puntosJugador.str("");
	puntosJugador << "Puntos obtenidos: " << juego->obtenerPuntuacionJugador();
	int ancho_puntosJugador = 500;
	int alto_puntosJugador = 40;
	int desfase_puntosJugador = 80;
	SDL_Rect cuadradoPuntos = {ancho_pantalla/2 -ancho_puntosJugador/2,
								alto_pantalla/2 - alto_puntosJugador/2 + desfase_puntosJugador,
								ancho_puntosJugador,
								alto_puntosJugador};

	renderizarTexto(cuadradoFin, textoFelicitaciones.str().c_str());
	renderizarTexto(cuadradoPuntos, puntosJugador.str().c_str());

	SDL_RenderPresent( renderizador );
}

DibujadorGanadores::~DibujadorGanadores(){

}
