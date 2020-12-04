#ifndef SRC_CLIENT_ESCUCHADORES_ESCUCHADORINFORMACIONPARTIDA_HPP_
#define SRC_CLIENT_ESCUCHADORES_ESCUCHADORINFORMACIONPARTIDA_HPP_

class Cliente;
#include "../Cliente.hpp"

#include "../../Utils/Escuchador.hpp"

class EscuchadorInformacionPartida : public Escuchador{

	public:
		EscuchadorInformacionPartida(int socketCliente, Cliente* cliente);
		virtual ~EscuchadorInformacionPartida();
		void escuchar();
		void casoError(int resultado)override;
		void casoSocketCerrado()override;
		void casoExitoso()override;
	private:
		info_inicio_t info;
		Cliente* cliente;
};


#endif /* SRC_CLIENT_ESCUCHADORES_ESCUCHADORINFORMACIONPARTIDA_HPP_ */
