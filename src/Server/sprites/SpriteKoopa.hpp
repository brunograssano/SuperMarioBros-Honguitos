#ifndef SRC_SERVER_SPRITES_SPRITEKOOPA_HPP_
#define SRC_SERVER_SPRITES_SPRITEKOOPA_HPP_

#include "SpriteEnemigo.hpp"

class SpriteKoopa : public SpriteEnemigo{
	public:

		explicit SpriteKoopa();
		~SpriteKoopa() override= default;
        void morir() override;
		void actualizarSprite()override;
        bool seMostroElTiempoSuficienteEnPantalla()override;

};

#endif /* SRC_SERVER_SPRITES_SPRITEKOOPA_HPP_ */
