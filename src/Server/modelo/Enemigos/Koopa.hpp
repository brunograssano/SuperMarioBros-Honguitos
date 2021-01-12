#ifndef SRC_SERVER_MODELO_ENEMIGOS_KOOPA_HPP_
#define SRC_SERVER_MODELO_ENEMIGOS_KOOPA_HPP_

using namespace std;
#include "Enemigo.hpp"

class Koopa : public Enemigo{
	public:
		explicit Koopa(int tipoColor);
		~Koopa() override;
		enemigo_t serializar() override;
        string obtenerColisionID() override;
    private:
        void inicializarMapasDeColision() override;
};

#endif /* SRC_SERVER_MODELO_ENEMIGOS_KOOPA_HPP_ */
