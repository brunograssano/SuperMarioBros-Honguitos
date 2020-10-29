#ifndef SRC_APP_DIBUJADORJUEGO_H_
#define SRC_APP_DIBUJADORJUEGO_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

#include "../modelo/Juego.h"
#include "CargadorTexturas.h"
#include "../sprites/SpriteMario.h"


class DibujadorJuego{
	public:
		DibujadorJuego(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador,SpriteMario* spriteMario, int ancho_pantalla,int alto_pantalla);
		void dibujar(SDL_Rect* rectanguloCamara);
		~DibujadorJuego();
	private:
		Uint32 tiempoDeInicio = 0;
		stringstream textoDeTiempo;
		stringstream textoDeNivel;
		stringstream textoDePuntos;

		int alto_pantalla;
		int ancho_pantalla;
		CargadorTexturas* cargadorTexturas;
		SDL_Renderer* renderizador;
		SDL_Rect rectanguloCamara;
		Juego* juego;
		SpriteMario* spriteMario;

		void dibujarEnemigos(SDL_Rect* rectanguloCamara);
		void dibujarPlataformas(SDL_Rect* rectanguloCamara);
		void dibujarMonedas(SDL_Rect* rectanguloCamara);
		void dibujarMario(SDL_Rect* rectanguloCamara);
		void dibujarTexto();
		void renderizarTexto(SDL_Rect renderQuad,string textoAMostrar );

};

#endif /* SRC_APP_DIBUJADORJUEGO_H_ */
