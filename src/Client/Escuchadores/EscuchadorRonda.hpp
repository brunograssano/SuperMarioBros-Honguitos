#ifndef SRC_CLIENT_ESCUCHADORES_ESCUCHADORRONDA_HPP_
#define SRC_CLIENT_ESCUCHADORES_ESCUCHADORRONDA_HPP_


class Cliente;
#include "../Cliente.hpp"

#include "Escuchador.hpp"

class EscuchadorRonda: public Escuchador{

	public:
		EscuchadorRonda(int socketCliente, Cliente* cliente);
		void escuchar() override;
		~EscuchadorRonda();
	private:
		int socket;
		Cliente* cliente;
};



#endif /* SRC_CLIENT_ESCUCHADORES_ESCUCHADORRONDA_HPP_ */
