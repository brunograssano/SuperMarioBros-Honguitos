#ifndef SRC_CLIENT_ESCUCHADORES_ESCUCHADORRONDA_HPP_
#define SRC_CLIENT_ESCUCHADORES_ESCUCHADORRONDA_HPP_


class Cliente;
#include "../Cliente.hpp"

#include "../../Utils/Escuchador.hpp"

class EscuchadorRonda: public Escuchador{

	public:
		EscuchadorRonda(int socketCliente, Cliente* cliente);
		virtual ~EscuchadorRonda();
		void escuchar();
		void casoError(int resultado)override;
		void casoSocketCerrado()override;
		void casoExitoso()override;

	private:
		Cliente* cliente;
		info_ronda_t info_ronda;
};



#endif /* SRC_CLIENT_ESCUCHADORES_ESCUCHADORRONDA_HPP_ */
