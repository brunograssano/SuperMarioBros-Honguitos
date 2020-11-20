#ifndef CLIENT_ESCUCHADORES_ESCUCHADOR_HPP_
#define CLIENT_ESCUCHADORES_ESCUCHADOR_HPP_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../../src/Utils.hpp"

class Escuchador{

	public:
		virtual ~Escuchador(){};
		virtual void escuchar(){};
};



#endif /* CLIENT_ESCUCHADORES_ESCUCHADOR_HPP_ */
