#ifndef SRC_UTILS_ENVIADOR_HPP_
#define SRC_UTILS_ENVIADOR_HPP_


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Utils.hpp"

class Enviador{
	public:
		virtual ~Enviador(){};
		virtual void enviar(){};
		virtual void dejarInformacion(void* informacion){};
	protected:
		int socket;
};


#endif /* SRC_UTILS_ENVIADOR_HPP_ */
