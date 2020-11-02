#ifndef SRC_SPRITES_SPRITEPEACH_HPP_
#define SRC_SPRITES_SPRITEPEACH_HPP_

#include "../Sprite.hpp"

class SpritePeachSaltando: public Sprite{

	public:
		SpritePeachSaltando();
		void actualizarSprite()override;

		SDL_Rect obtenerRectanguloActual()override;

	private:
		SDL_Rect estadosPosibles[14];
		int estadoActual;

};



#endif /* SRC_SPRITES_SPRITEPEACH_HPP_ */
