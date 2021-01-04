
#ifndef SRC_SERVER_SPRITES_SPRITESPERSONAJESSALTANDO_SPRITEYOSHISALTANDO_HPP_
#define SRC_SERVER_SPRITES_SPRITESPERSONAJESSALTANDO_SPRITEYOSHISALTANDO_HPP_


#include "../Sprite.hpp"

class SpriteYoshiSaltando: public Sprite{

	public:
		SpriteYoshiSaltando();
		void actualizarSprite()override;

		SDL_Rect obtenerRectanguloActual()override;

	private:
		SDL_Rect estadosPosibles[16]{};
		int estadoActual;

};




#endif /* SRC_SERVER_SPRITES_SPRITESPERSONAJESSALTANDO_SPRITEYOSHISALTANDO_HPP_ */
