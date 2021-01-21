#ifndef SRC_MODELO_ENEMIGOS_GOOMBA_HP_
#define SRC_MODELO_ENEMIGOS_GOOMBA_HP_

#include "Enemigo.hpp"

class Goomba : public Enemigo{
	public:
		explicit Goomba(int tipoColor);
		enemigo_t serializar() override;
		~Goomba() override;
        string obtenerColisionID() override;
};

#endif /* SRC_MODELO_ENEMIGOS_GOOMBA_HP_ */
