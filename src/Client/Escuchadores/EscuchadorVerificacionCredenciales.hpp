#ifndef SRC_CLIENT_ESCUCHADORES_ESCUCHADORVERIFICACIONCREDENCIALES_HPP_
#define SRC_CLIENT_ESCUCHADORES_ESCUCHADORVERIFICACIONCREDENCIALES_HPP_


class Cliente;
#include "../Cliente.hpp"

#include "Escuchador.hpp"

class EscuchadorVerificacionCredenciales : public Escuchador{

	public:
		EscuchadorVerificacionCredenciales(int socketCliente, Cliente* cliente);
		void escuchar() override;
		~EscuchadorVerificacionCredenciales();
	private:
		int socket;
		Cliente* cliente;
};


#endif /* SRC_CLIENT_ESCUCHADORES_ESCUCHADORVERIFICACIONCREDENCIALES_HPP_ */
