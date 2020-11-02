#ifndef SRC_APP_DIBUJADOR_H_
#define SRC_APP_DIBUJADOR_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

#include <stdio.h>
#include <string>
#include <sstream>

#include "../CargadorTexturas.hpp"

class Dibujador{

	public:

		virtual void dibujar(){}

		virtual void renderizarTexto(SDL_Rect renderQuad, string textoAMostrar ){
			SDL_Rect* clip = NULL;
			double angle = 0.0;
			SDL_Point* center = NULL;
			SDL_RendererFlip flip = SDL_FLIP_NONE;

			SDL_SetRenderDrawColor(renderizador, 0x0, 0x0, 0x0, 255);

			SDL_Texture* texto = cargadorTexturas->cargarFuenteDeTextoATextura(textoAMostrar, renderizador);

			SDL_RenderCopyEx( renderizador, texto, clip, &renderQuad, angle, center, flip );
			SDL_DestroyTexture(texto);
		};

		virtual ~Dibujador(){};

	protected:
		int alto_pantalla;
		int ancho_pantalla;
		SDL_Renderer* renderizador;
		CargadorTexturas* cargadorTexturas;

};

#endif /* SRC_APP_DIBUJADOR_H_ */
