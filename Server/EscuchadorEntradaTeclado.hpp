
#ifndef SERVER_ESCUCHADORENTRADATECLADO_HPP_
#define SERVER_ESCUCHADORENTRADATECLADO_HPP_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Servidor.hpp"
#include "../src/Utils.hpp"

class EscuchadorEntradaTeclado{

	public:
		EscuchadorEntradaTeclado(int socket, int idJugador, Servidor* servidor);
		void escuchar();

	private:
		int socket;
		int idJugador;
		Servidor* servidor;

};



#endif /* SERVER_ESCUCHADORENTRADATECLADO_HPP_ */
