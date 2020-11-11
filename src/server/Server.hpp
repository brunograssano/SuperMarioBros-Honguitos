#ifndef SRC_SERVER_SERVER_HPP_
#define SRC_SERVER_SERVER_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <thread>

#include "../log/Log.hpp"
#include "../lector/ArchivoLeido.hpp"
#include "../modelo/Juego.hpp"

#include "ConexionServidor.hpp"

const int MAX_CONEXIONES = 4;

typedef struct usuario{
	string nombre;
	string contrasenia;
}usuario_t;

class Server{

	public:
		Server(ArchivoLeido* archivoLeido,list<string> mensajesErrorOtroArchivo, int puerto, int ip);
		void escuchar();
		~Server();

	private:
		int socketServer;
		int cantidadConexiones;
		list<usuario_t> usuariosValidos;
		void escribirMensajesDeArchivoLeidoEnLog(list<string> mensajesError);
		bool esUsuarioValido(usuario_t posibleUsuario);
		list<thread> conexionesConElServidor;

};



#endif /* SRC_SERVER_SERVER_HPP_ */
