#ifndef SRC_CLIENT_ESCUCHADORES_ESCUCHADORINFOPARTIDAINICIAL_HPP_
#define SRC_CLIENT_ESCUCHADORES_ESCUCHADORINFOPARTIDAINICIAL_HPP_

#include <string>
#include "src/Utils/Socket.hpp"
#include "src/Utils/Escuchador.hpp"
class Cliente;
#include "../Cliente.hpp"
#include "src/Utils/Utils.hpp"

class EscuchadorInfoPartidaInicial : public Escuchador{

	public:
		EscuchadorInfoPartidaInicial(Socket* socket,Cliente* cliente);
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
