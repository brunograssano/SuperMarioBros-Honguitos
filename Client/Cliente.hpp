#ifndef CLIENT_CLIENTE_HPP_
#define CLIENT_CLIENTE_HPP_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>


using namespace std;

const int LARGO_IP = 20;


class Cliente{

	public:
		Cliente(char ip[LARGO_IP], int puerto);
		~Cliente();
		void escuchar();
		static void* escuchar_helper(void* ptr){
			((Cliente*) ptr)->escuchar();
			return NULL;
		}

		void enviar();
		static void* enviar_helper(void* ptr){
			((Cliente*) ptr)->enviar();
			return NULL;
		}

	private:
		int _Read4Bytes(char* buffer);
		int socketCliente;
};
#endif /* CLIENT_CLIENTE_HPP_ */
