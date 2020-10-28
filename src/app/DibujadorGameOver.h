#ifndef SRC_APP_DIBUJADORGAMEOVER_H_
#define SRC_APP_DIBUJADORGAMEOVER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string>
#include <sstream>

#include "CargadorTexturas.h"
#include "../sprites/SpriteCoffinMario.h"
#include "../sprites/Sprite.h"

class DibujadorGameOver{

	public:
		DibujadorGameOver(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla);
		void dibujar();
		~DibujadorGameOver();

	private:
		void renderizarTexto(SDL_Rect renderQuad, string textoAMostrar );
		int alto_pantalla;
		int ancho_pantalla;
		CargadorTexturas* cargadorTexturas;
		SDL_Renderer* renderizador;
		SpriteCoffinMario* spriteCoffinMario;
};



#endif /* SRC_APP_DIBUJADORGAMEOVER_H_ */
