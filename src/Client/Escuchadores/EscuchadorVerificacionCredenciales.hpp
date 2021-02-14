#ifndef SRC_CLIENT_ESCUCHADORES_ESCUCHADORVERIFICACIONCREDENCIALES_HPP_
#define SRC_CLIENT_ESCUCHADORES_ESCUCHADORVERIFICACIONCREDENCIALES_HPP_

class Cliente;
#include "../Cliente.hpp"
#include "src/Utils/Escuchador.hpp"
#include "src/Utils/Socket.hpp"
#include "src/Utils/Utils.hpp"

class EscuchadorVerificacionCredenciales : public Escuchador{

	public:
		EscuchadorVerificacionCredenciales(Socket* socketCliente, Cliente* cliente);
		void casoError(int resultado)override;
		void casoSocketCerrado()override;
		void casoExitoso()override;
	private:
		verificacion_t verificacion{};
		Cliente* cliente;
};


#endif /* SRC_CLIENT_ESCUCHADORES_ESCUCHADORVERIFICACIONCREDENCIALES_HPP_ */
