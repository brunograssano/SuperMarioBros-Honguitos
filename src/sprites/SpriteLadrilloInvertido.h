#ifndef SRC_SPRITES_SPRITELADRILLOINVERTIDO_H_
#define SRC_SPRITES_SPRITELADRILLOINVERTIDO_H_

#include "Sprite.h"
#include <SDL2/SDL.h>

class SpriteLadrilloInvertido : public Sprite{
	public:

		SpriteLadrilloInvertido();
		~SpriteLadrilloInvertido(){};

		SDL_Rect obtenerRectanguloActual()override;

		void actualizarSprite()override;

	private:

		SDL_Rect rectanguloLadrillo;

};


#endif /* SRC_SPRITES_SPRITELADRILLOINVERTIDO_H_ */
