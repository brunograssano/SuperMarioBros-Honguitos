

#ifndef SRC_SPRITES_SPRITESPERSONAJESSALTANDO_SPRITETOADSALTANDO_HPP_
#define SRC_SPRITES_SPRITESPERSONAJESSALTANDO_SPRITETOADSALTANDO_HPP_

#include "../Sprite.hpp"

class SpriteToadSaltando: public Sprite{

	public:
		SpriteToadSaltando();
		void actualizarSprite()override;

		SDL_Rect obtenerRectanguloActual()override;

	private:
		SDL_Rect estadosPosibles[12];
		int estadoActual;

};



#endif /* SRC_SPRITES_SPRITESPERSONAJESSALTANDO_SPRITETOADSALTANDO_HPP_ */
