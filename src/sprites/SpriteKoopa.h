#ifndef SRC_SPRITES_SPRITEKOOPA_H_
#define SRC_SPRITES_SPRITEKOOPA_H_

#include "Sprite.h"
#include <SDL2/SDL.h>

class SpriteKoopa : public Sprite{
	public:

		SpriteKoopa(string direccionImagen);
		~SpriteKoopa(){};

		SDL_Rect obtenerRectanguloActual()override;

		void actualizarSprite()override;

	private:
		int ciclos;
		int estadoActual;
		SDL_Rect estadosPosibles[6];
};

#endif /* SRC_SPRITES_SPRITEKOOPA_H_ */
