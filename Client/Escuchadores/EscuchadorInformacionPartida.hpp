#ifndef CLIENT_ESCUCHADORES_ESCUCHADORINFORMACIONPARTIDA_HPP_
#define CLIENT_ESCUCHADORES_ESCUCHADORINFORMACIONPARTIDA_HPP_


class Cliente;
#include "../Cliente.hpp"

#include "Escuchador.hpp"

class EscuchadorInformacionPartida : public Escuchador{

	public:
		EscuchadorInformacionPartida(int socketCliente, Cliente* cliente);
		void escuchar() override;
		~EscuchadorInformacionPartida();
	private:
		int socket;
		Cliente* cliente;
};


#endif /* CLIENT_ESCUCHADORES_ESCUCHADORINFORMACIONPARTIDA_HPP_ */
