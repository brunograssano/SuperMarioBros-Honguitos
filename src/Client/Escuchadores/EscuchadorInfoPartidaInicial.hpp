#ifndef SRC_CLIENT_ESCUCHADORES_ESCUCHADORINFOPARTIDAINICIAL_HPP_
#define SRC_CLIENT_ESCUCHADORES_ESCUCHADORINFOPARTIDAINICIAL_HPP_

class Cliente;
#include "../Cliente.hpp"

#include "../../Utils/Escuchador.hpp"

class EscuchadorInfoPartidaInicial : public Escuchador{

	public:
		EscuchadorInfoPartidaInicial(int socket,Cliente* cliente);
		virtual ~EscuchadorInfoPartidaInicial();
		void escuchar();
		void casoError(int resultado)override;
		void casoSocketCerrado()override;
		void casoExitoso()override;

	private:
		info_partida_t info_partida;
		Cliente* cliente;

};



#endif /* SRC_CLIENT_ESCUCHADORES_ESCUCHADORINFOPARTIDAINICIAL_HPP_ */
