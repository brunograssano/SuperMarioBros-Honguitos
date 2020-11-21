#ifndef SERVER_ESCUCHADORESSERVER_ESCUCHADORSERVER_HPP_
#define SERVER_ESCUCHADORESSERVER_ESCUCHADORSERVER_HPP_


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../../src/Utils.hpp"

class EscuchadorServer{
	public:
		virtual ~EscuchadorServer(){};
		virtual void escuchar(){};
};



#endif /* SERVER_ESCUCHADORESSERVER_ESCUCHADORSERVER_HPP_ */
