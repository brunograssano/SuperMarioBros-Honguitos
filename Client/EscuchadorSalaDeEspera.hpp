#ifndef CLIENT_ESCUCHADORSALADEESPERA_HPP_
#define CLIENT_ESCUCHADORSALADEESPERA_HPP_

#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


class EscuchadorSalaDeEspera{

	public:
		EscuchadorSalaDeEspera(int socket);
		void escuchar();
		static void* escuchar_helper(void* ptr){
			((EscuchadorSalaDeEspera*) ptr)->escuchar();
			return NULL;
		}
		int getCantidadConectados();
		~EscuchadorSalaDeEspera();

	private:
		int cantidadConectados;
		int socket;
};

#endif /* CLIENT_ESCUCHADORSALADEESPERA_HPP_ */
