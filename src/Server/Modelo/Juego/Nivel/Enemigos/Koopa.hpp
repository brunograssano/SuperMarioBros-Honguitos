#ifndef SRC_SERVER_MODELO_ENEMIGOS_KOOPA_HPP_
#define SRC_SERVER_MODELO_ENEMIGOS_KOOPA_HPP_

#include "Enemigo.hpp"
#include "src/Utils/Utils.hpp"

class Koopa : public Enemigo{
	public:
		explicit Koopa(int tipoColor);
		~Koopa() override;
        entidad_t serializar() override;
        std::string obtenerColisionID() override;
        bool estaEnElAire();
};

#endif /* SRC_SERVER_MODELO_ENEMIGOS_KOOPA_HPP_ */
