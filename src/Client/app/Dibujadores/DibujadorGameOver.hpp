#ifndef SRC_APP_DIBUJADORGAMEOVER_H_
#define SRC_APP_DIBUJADORGAMEOVER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string>
#include <sstream>

#include "Dibujador.hpp"
#include "../../../Server/sprites/Sprite.hpp"
#include "../../../Server/sprites/SpriteCoffinMario.hpp"

class DibujadorGameOver : public Dibujador{

	public:
		DibujadorGameOver(CargadorTexturas* cargadorTexturas, SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla);
		void dibujar() override;
		~DibujadorGameOver() override;

	private:
		SpriteCoffinMario* spriteCoffinMario;
};



#endif /* SRC_APP_DIBUJADORGAMEOVER_H_ */
