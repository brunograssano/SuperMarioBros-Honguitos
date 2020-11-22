#ifndef SRC_CLIENT_ESCUCHADORES_ESCUCHADOR_HPP_
#define SRC_CLIENT_ESCUCHADORES_ESCUCHADOR_HPP_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../../Utils/Utils.hpp"

class Escuchador{

	public:
		virtual ~Escuchador(){};
		virtual void escuchar(){};
};



#endif /* SRC_CLIENT_ESCUCHADORES_ESCUCHADOR_HPP_ */
