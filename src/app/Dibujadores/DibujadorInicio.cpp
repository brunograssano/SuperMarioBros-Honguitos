#include "DibujadorInicio.hpp"

DibujadorInicio::DibujadorInicio(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla){
	this->cargadorTexturas = cargadorTexturas;
	this->renderizador= renderizador;
	this->ancho_pantalla = ancho_pantalla;
	this->alto_pantalla = alto_pantalla;
}



void DibujadorInicio::dibujar(){
	SDL_SetRenderDrawColor( renderizador, 120, 120, 200, 255 );
	SDL_RenderClear( renderizador );
	stringstream titulo;
	titulo.str("");
	titulo << "Mario Bros 75.42";
	int ancho_textoGameOver = 450;
	int alto_textoGameOver = 80;
	SDL_Rect cuadradoGameOver = {ancho_pantalla/2 -ancho_textoGameOver/2,
							alto_pantalla/2 - alto_textoGameOver/2,
							ancho_textoGameOver,
							alto_textoGameOver}; //Los coloco en el centro.


	stringstream indicacion;
	indicacion.str("");
	indicacion << "Pulse Enter para comenzar";
	int ancho_indicacion= 500;
	int alto_indicacion= 40;
	int desfase_alto_indicacion = 80;
	SDL_Rect cuadradoIndicacion = {ancho_pantalla/2 -ancho_indicacion/2,
								alto_pantalla/2 - alto_indicacion/2 + desfase_alto_indicacion,
								ancho_indicacion,
								alto_indicacion};

	renderizarTexto(cuadradoGameOver, titulo.str().c_str());
	renderizarTexto(cuadradoIndicacion, indicacion.str().c_str());
	SDL_RenderPresent(renderizador);
}


DibujadorInicio::~DibujadorInicio(){

}
