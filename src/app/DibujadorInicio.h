#ifndef SRC_APP_DIBUJADORINICIO_H_
#define SRC_APP_DIBUJADORINICIO_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>

#include "CargadorTexturas.h"


class DibujadorInicio{

	public:
		DibujadorInicio(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla, int alto_pantalla);
		void dibujar();
		~DibujadorInicio();

	private:
		CargadorTexturas* cargadorTexturas;
		SDL_Renderer* renderizador;
		int ancho_pantalla;
		int alto_pantalla;
		void renderizarTexto(SDL_Rect renderQuad, string textoAMostrar);
};

#endif /* SRC_APP_DIBUJADORINICIO_H_ */
