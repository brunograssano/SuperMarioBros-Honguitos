#ifndef SERVER_SERVIDOR_HPP_
#define SERVER_SERVIDOR_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <thread>

#include "../src/log/Log.hpp"
#include "../src/lector/ArchivoLeido.hpp"
#include "../src/modelo/Juego.hpp"

#include "ConexionServidor.hpp"

class ConexionCliente;
#include "ConexionCliente.hpp"


const int MAX_CONEXIONES = 4;

class Servidor{

	public:
		Servidor(ArchivoLeido* archivoLeido,list<string> mensajesErrorOtroArchivo, int puerto, char* ip);
		void* escuchar();
		static void *escuchar_helper(void* ptr){
			return((Servidor*) ptr)->escuchar();
		}
		~Servidor();

		bool esUsuarioValido(usuario_t posibleUsuario);

	private:
		Log* log;
		int socketServer;
		int cantidadConexiones;
		list<usuario_t> usuariosValidos;
		void escribirMensajesDeArchivoLeidoEnLog(list<string> mensajesError);

		list<thread> conexionesConElServidor;
		list<ConexionCliente*> clientes;

};



#endif /* SERVER_SERVIDOR_HPP_ */
