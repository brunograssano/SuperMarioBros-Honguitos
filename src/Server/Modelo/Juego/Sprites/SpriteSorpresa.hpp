#ifndef SRC_SERVER_SPRITES_SPRITESORPRESA_HPP_
#define SRC_SERVER_SPRITES_SPRITESORPRESA_HPP_

#include "SpriteBloque.hpp"

class SpriteSorpresa : public SpriteBloque{
	public:

		explicit SpriteSorpresa();
		~SpriteSorpresa() override= default;
		void actualizarSprite()override;
		void usarse() override;
		bool cambioElSprite() override;

};



#endif /* SRC_SERVER_SPRITES_SPRITESORPRESA_HPP_ */
