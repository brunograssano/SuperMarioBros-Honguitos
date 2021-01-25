#ifndef SRC_SERVER_ESCUCHADORESSERVER_ESCUCHADORCREDENCIALES_HPP_
#define SRC_SERVER_ESCUCHADORESSERVER_ESCUCHADORCREDENCIALES_HPP_

#include "../../Utils/Escuchador.hpp"
#include "src/Server/Servidor/ConexionCliente.hpp"

class EscuchadorCredenciales: public Escuchador{

	public:
		EscuchadorCredenciales(int socket, ConexionCliente* cliente);
		void casoError(int resultado)override;
		void casoSocketCerrado()override;
		void casoExitoso()override;

	private:
		ConexionCliente* conexionCliente;
		credencial_t credencial{};
};



#endif /* SRC_SERVER_ESCUCHADORESSERVER_ESCUCHADORCREDENCIALES_HPP_ */
