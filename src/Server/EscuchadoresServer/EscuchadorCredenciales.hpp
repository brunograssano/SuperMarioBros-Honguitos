#ifndef SRC_SERVER_ESCUCHADORESSERVER_ESCUCHADORCREDENCIALES_HPP_
#define SRC_SERVER_ESCUCHADORESSERVER_ESCUCHADORCREDENCIALES_HPP_

#include "src/Utils/Socket.hpp"
#include "src/Server/Servidor/ConexionCliente.hpp"
#include "src/Utils/Escuchador.hpp"
#include "src/Utils/Utils.hpp"

class EscuchadorCredenciales: public Escuchador{

	public:
		EscuchadorCredenciales(Socket* socket, ConexionCliente* cliente);
		void casoError(int resultado)override;
		void casoSocketCerrado()override;
		void casoExitoso()override;

	private:
		ConexionCliente* conexionCliente;
		credencial_t credencial{};
};



#endif /* SRC_SERVER_ESCUCHADORESSERVER_ESCUCHADORCREDENCIALES_HPP_ */
