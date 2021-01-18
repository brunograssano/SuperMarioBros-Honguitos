#ifndef SRC_SERVER_SPRITES_SPRITEMONEDA_HPP_
#define SRC_SERVER_SPRITES_SPRITEMONEDA_HPP_

#include "Sprite.hpp"

class SpriteMoneda : public Sprite{

public:
		SpriteMoneda();
		~SpriteMoneda() override= default;
		void actualizarSprite()override;

};


#endif /* SRC_SERVER_SPRITES_SPRITEMONEDA_HPP_ */
