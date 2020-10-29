#ifndef SRC_APP_DIBUJADORGANADORES_H_
#define SRC_APP_DIBUJADORGANADORES_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>

#include "CargadorTexturas.h"
#include "../modelo/Juego.h"

class DibujadorGanadores{
	public:
		DibujadorGanadores(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla);
		void dibujar();
		~DibujadorGanadores();

	private:
		CargadorTexturas* cargadorTexturas;
		SDL_Renderer* renderizador;
		int ancho_pantalla;
		int alto_pantalla;
		void renderizarTexto(SDL_Rect renderQuad, string textoAMostrar);
};


#endif /* SRC_APP_DIBUJADORGANADORES_H_ */
