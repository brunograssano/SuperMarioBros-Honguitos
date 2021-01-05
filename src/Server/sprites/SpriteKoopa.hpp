#ifndef SRC_SERVER_SPRITES_SPRITEKOOPA_HPP_
#define SRC_SERVER_SPRITES_SPRITEKOOPA_HPP_

#include <SDL2/SDL.h>
#include "SpriteEnemigo.hpp"

class SpriteKoopa : public SpriteEnemigo{
	public:

		explicit SpriteKoopa(int tipo);
		~SpriteKoopa() override= default;
		SDL_Rect obtenerRectanguloActual()override;
        void morir() override;
		void actualizarSprite()override;

	private:
		SDL_Rect estadosPosibles[6]{};
};

#endif /* SRC_SERVER_SPRITES_SPRITEKOOPA_HPP_ */
