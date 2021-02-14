#ifndef SRC_SERVER_SPRITES_SPRITELADRILLO_HPP_
#define SRC_SERVER_SPRITES_SPRITELADRILLO_HPP_

#include "SpriteBloque.hpp"

class SpriteLadrillo : public SpriteBloque{
	public:
		SpriteLadrillo();
		~SpriteLadrillo() override = default;
		void actualizarSprite()override;
		void usarse() override;
		bool cambioElSprite() override;

    private:
        int estadoAnterior;

};


#endif /* SRC_SERVER_SPRITES_SPRITELADRILLO_HPP_ */
