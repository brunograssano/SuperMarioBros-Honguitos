#include "SpriteEnemigo.hpp"

class SpriteGoomba : public SpriteEnemigo{
	public:

		SpriteGoomba();
		~SpriteGoomba() override= default;
        void morir() override;
		void actualizarSprite()override;
        bool seMostroElTiempoSuficienteEnPantalla()override;

};
