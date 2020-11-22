#ifndef CLIENT_ESCUCHADORES_ESCUCHADORINFOPARTIDAINICIAL_HPP_
#define CLIENT_ESCUCHADORES_ESCUCHADORINFOPARTIDAINICIAL_HPP_

#include "Escuchador.hpp"

class Cliente;
#include "../Cliente.hpp"


class EscuchadorInfoPartidaInicial : public Escuchador{

	public:
		EscuchadorInfoPartidaInicial(int socket,Cliente* cliente);

		void escuchar()override;

	private:
		Cliente* cliente;
		int socket;
};



#endif /* CLIENT_ESCUCHADORES_ESCUCHADORINFOPARTIDAINICIAL_HPP_ */
