
#ifndef SRC_SPRITES_SPRITELADRILLO_H_
#define SRC_SPRITES_SPRITELADRILLO_H_

#include "Sprite.h"
#include <SDL2/SDL.h>

class SpriteLadrillo : public Sprite{
	public:

		SpriteLadrillo();
		~SpriteLadrillo(){};

		SDL_Rect obtenerRectanguloActual()override;

		int obtenerPosicionXRectangulo()override;

		void actualizarSprite()override;

		string obtenerDireccionSprite();

	private:

		SDL_Rect rectanguloLadrillo;

};


#endif /* SRC_SPRITES_SPRITELADRILLO_H_ */
