#ifndef SRC_SERVER_ESCUCHADORESSERVER_ESCUCHADORSERVER_HPP_
#define SRC_SERVER_ESCUCHADORESSERVER_ESCUCHADORSERVER_HPP_


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../../Utils.hpp"

class EscuchadorServer{
	public:
		virtual ~EscuchadorServer(){};
		virtual void escuchar(){};
};



#endif /* SRC_SERVER_ESCUCHADORESSERVER_ESCUCHADORSERVER_HPP_ */
