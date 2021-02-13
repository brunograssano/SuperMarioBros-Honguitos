#ifndef SRC_APP_DIBUJADOR_H_
#define SRC_APP_DIBUJADOR_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>
#include <sstream>

#include "../CargadorTexturas.hpp"


const SDL_Color colorDefault = {255, 255, 255, 255};
const int MARIO_GRIS = -1;

class Dibujador{

	public:
		virtual void dibujar() = 0;
        virtual void agregarEventoDeClick(SDL_Event eventoClick) {};
		virtual void renderizarTexto(SDL_Rect renderQuad, std::string textoAMostrar, SDL_Color color);
		virtual ~Dibujador()= default;

	protected:
		int alto_pantalla{};
		int ancho_pantalla{};
		SDL_Renderer* renderizador{};
		CargadorTexturas* cargadorTexturas{};

};

#endif /* SRC_APP_DIBUJADOR_H_ */
