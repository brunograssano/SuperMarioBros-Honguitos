#ifndef SRC_SERVER_SPRITES_SPRITEKOOPA_HPP_
#define SRC_SERVER_SPRITES_SPRITEKOOPA_HPP_

#include "SpriteEnemigo.hpp"
class Koopa;

class SpriteKoopa : public SpriteEnemigo{
	public:

		explicit SpriteKoopa(bool estaEspejado, Koopa* koopaAsociado);
		~SpriteKoopa() override= default;
        void morir() override;
		void actualizarSprite()override;
        bool seMostroElTiempoSuficienteEnPantalla()override;
    private:
        void actualizarSpriteAire();
        void actualizarSpriteTierra();
        Koopa* koopa;
};

#endif /* SRC_SERVER_SPRITES_SPRITEKOOPA_HPP_ */
