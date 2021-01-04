
#ifndef SRC_MODELO_ENEMIGOS_GOOMBA_HP_
#define SRC_MODELO_ENEMIGOS_GOOMBA_HP_

using namespace std;

#include "Enemigo.hpp"
#include "../../sprites/SpriteGoomba.hpp"

class Goomba : public Enemigo{
	public:
		explicit Goomba(int tipoColor);
		enemigo_t serializar() override;
		~Goomba() override;
};

#endif /* SRC_MODELO_ENEMIGOS_GOOMBA_HP_ */
