#ifndef SRC_CLIENT_ESCUCHADORES_ESCUCHADORINFOPARTIDAINICIAL_HPP_
#define SRC_CLIENT_ESCUCHADORES_ESCUCHADORINFOPARTIDAINICIAL_HPP_

class Cliente;
#include "../Cliente.hpp"

#include "src/Utils/Escuchador.hpp"

class EscuchadorInfoPartidaInicial : public Escuchador{

	public:
		EscuchadorInfoPartidaInicial(int socket,Cliente* cliente);
		void casoError(int resultado)override;
		void casoSocketCerrado()override;
		void casoExitoso()override;
		bool recibioInformacionPartidaValida();

	private:
		info_partida_t info_partida;
		Cliente* cliente;
        std::string error = "";
};



#endif /* SRC_CLIENT_ESCUCHADORES_ESCUCHADORINFOPARTIDAINICIAL_HPP_ */
