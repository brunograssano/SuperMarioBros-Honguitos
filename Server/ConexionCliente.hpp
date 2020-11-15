#ifndef SERVER_CONEXIONCLIENTE_HPP_
#define SERVER_CONEXIONCLIENTE_HPP_

class Servidor;
#include "Servidor.hpp"

using namespace std;
#include <thread>
#include <string>

#include "../src/log/Log.hpp"

class ConexionCliente {

	public:
		ConexionCliente(Servidor* servidor, int socket, string nombre);
		~ConexionCliente();

		void recibir();
		static void* recibir_helper(void* ptr){
			((ConexionCliente*) ptr)->recibir();
			return NULL;
		}

		void enviar(char* msg);

	private:
		string nombre;
		int socket;
		Servidor* servidor;
};


#endif /* SERVER_CONEXIONCLIENTE_HPP_ */
