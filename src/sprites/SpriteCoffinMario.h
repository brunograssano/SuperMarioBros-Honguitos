#ifndef SRC_SPRITES_SPRITECOFFINMARIO_H_
#define SRC_SPRITES_SPRITECOFFINMARIO_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../modelo/Juego.h"
#include "../app/CargadorTexturas.h"
#include "Sprite.h"

class SpriteCoffinMario : public Sprite{

	public:

		SpriteCoffinMario();

		SDL_Rect obtenerRectanguloActual()override;

		int obtenerPosicionX();

		void actualizarSprite();

	private:
		SDL_Rect estadosPosibles[3];
		int estadoActual;
		int ciclos;
		int posicionX;
};


#endif /* SRC_SPRITES_SPRITECOFFINMARIO_H_ */
