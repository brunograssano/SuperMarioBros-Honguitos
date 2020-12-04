#ifndef SRC_UTILS_ESCUCHADOR_HPP_
#define SRC_UTILS_ESCUCHADOR_HPP_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Utils.hpp"

class Escuchador{

	public:
		virtual ~Escuchador(){};
		void escuchar(){
			int resultado = recv(socket, structPointer, bytes, MSG_WAITALL);
			if(resultado < 0){
				casoError(resultado);
			}else if(resultado == 0){
				casoSocketCerrado();
			}else{
				casoExitoso();
			}
		};

		virtual void casoError(int resultado){};
		virtual void casoSocketCerrado(){};
		virtual void casoExitoso(){};

	protected:
		int socket;
		void* structPointer;
		int bytes;
};

#endif /* SRC_UTILS_ESCUCHADOR_HPP_ */
