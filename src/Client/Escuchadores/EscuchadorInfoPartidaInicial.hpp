#ifndef SRC_CLIENT_ESCUCHADORES_ESCUCHADORINFOPARTIDAINICIAL_HPP_
#define SRC_CLIENT_ESCUCHADORES_ESCUCHADORINFOPARTIDAINICIAL_HPP_

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



#endif /* SRC_CLIENT_ESCUCHADORES_ESCUCHADORINFOPARTIDAINICIAL_HPP_ */
