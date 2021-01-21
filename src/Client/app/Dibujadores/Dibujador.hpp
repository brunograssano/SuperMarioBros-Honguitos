#ifndef SRC_APP_DIBUJADOR_H_
#define SRC_APP_DIBUJADOR_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

#include <cstdio>
#include <string>
#include <sstream>

#include "../CargadorTexturas.hpp"
#include "../ManejadorSDL.hpp"

const SDL_Color colorDefault = {255, 255, 255, 255};
const int MARIO_GRIS = -1;

class Dibujador{

	public:

		virtual void dibujar(){}

		virtual void renderizarTexto(SDL_Rect renderQuad, string textoAMostrar, SDL_Color color){
			SDL_Rect* clip = nullptr;
			double angle = 0.0;
			SDL_Point* center = nullptr;
			SDL_RendererFlip flip = SDL_FLIP_NONE;

			SDL_SetRenderDrawColor(renderizador, colorDefault.r, colorDefault.g, colorDefault.b, colorDefault.a);

			SDL_Texture* texto = cargadorTexturas->cargarFuenteDeTextoATextura(textoAMostrar, renderizador, color);

			SDL_RenderCopyEx( renderizador, texto, clip, &renderQuad, angle, center, flip );
			destructorDeTexturas(texto);

		};

		virtual ~Dibujador()= default;;

	protected:
		int alto_pantalla{};
		int ancho_pantalla{};
		SDL_Renderer* renderizador{};
		CargadorTexturas* cargadorTexturas{};

};

#endif /* SRC_APP_DIBUJADOR_H_ */
