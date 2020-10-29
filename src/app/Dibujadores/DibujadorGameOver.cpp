#include "DibujadorGameOver.hpp"


DibujadorGameOver::DibujadorGameOver(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla){
	this->alto_pantalla = alto_pantalla;
	this->ancho_pantalla = ancho_pantalla;
	this->cargadorTexturas = cargadorTexturas;
	this->renderizador = renderizador;
	this->spriteCoffinMario = new SpriteCoffinMario();
}


void DibujadorGameOver::dibujar(){
	SDL_RenderClear( renderizador );

	SDL_Rect rectanguloCamara = {0, 0, alto_pantalla, ancho_pantalla};
	this->spriteCoffinMario->actualizarSprite();
	int posicionXCoffinMario = this->spriteCoffinMario->obtenerPosicionX();
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaFondoGameOver(), &rectanguloCamara, NULL);

	stringstream textoGameOver;
	textoGameOver.str("");
	textoGameOver << "GAME OVER";
	int ancho_textoGameOver = 450;
	int alto_textoGameOver = 80;
	SDL_Rect cuadradoGameOver = {ancho_pantalla/2 -ancho_textoGameOver/2,
							alto_pantalla/2 - alto_textoGameOver/2,
							ancho_textoGameOver,
							alto_textoGameOver}; //Los coloco en el centro.

	renderizarTexto(cuadradoGameOver, textoGameOver.str().c_str());
	int piso = 440;
	SDL_Rect rectanguloCoffinMario = {posicionXCoffinMario, piso, 3*70, 3*32};
	SDL_Rect recorteCoffinMario = this->spriteCoffinMario->obtenerRectanguloActual();
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaCoffinMario(), &recorteCoffinMario , &rectanguloCoffinMario);

	SDL_RenderPresent(renderizador);
}

DibujadorGameOver::~DibujadorGameOver(){
	delete this->spriteCoffinMario;
}
