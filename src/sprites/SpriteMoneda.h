
#ifndef SRC_SPRITES_SPRITEMONEDA_H_
#define SRC_SPRITES_SPRITEMONEDA_H_

#include "Sprite.h"
#include <SDL2/SDL.h>

class SpriteMoneda : public Sprite{
	public:

		SpriteMoneda();
		~SpriteMoneda(){};

		SDL_Rect obtenerRectanguloActual()override;

		void actualizarSprite()override;

	private:

		int ciclos;
		int estadoActual;
		SDL_Rect estadosPosibles[4];
};


#endif /* SRC_SPRITES_SPRITEMONEDA_H_ */
