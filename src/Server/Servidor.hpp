#ifndef SRC_SERVER_SERVIDOR_HPP_
#define SRC_SERVER_SERVIDOR_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>

#include <thread>
#include <map>


#include "../Utils/log/Log.hpp"
#include "modelo/Juego.hpp"

class AplicacionServidor;
#include "../Server/AplicacionServidor.hpp"
#include "../Utils/Utils.hpp"
#include "lector/ArchivoLeido.hpp"

class ConexionCliente;
#include "ConexionCliente.hpp"


const int MAX_CONEXIONES = 4;

class Servidor{

	public:
		Servidor(ArchivoLeido* archivoLeido,list<string> mensajesErrorOtroArchivo, int puerto, char* ip);
		void* escuchar();
		void iniciarJuego(pthread_t* hiloJuego);
		static void *escuchar_helper(void* ptr){
			return((Servidor*) ptr)->escuchar();
		}
		~Servidor();

		int getMaximasConexiones(){return this->cantidadConexiones;}
		bool esUsuarioValido(usuario_t posibleUsuario,ConexionCliente* conexionClienteConPosibleUsuario);
		void intentarIniciarModelo();
		void encolarEntradaUsuario(entrada_usuario_id_t entradaUsuario);

	private:
		map<int,string> mapaIDNombre;
		Log* log;
		AplicacionServidor* aplicacionServidor;
		int socketServer;
		int cantidadConexiones;
		int cantUsuariosLogueados = 0;
		list<usuario_t> usuariosValidos;
		void escribirMensajesDeArchivoLeidoEnLog(list<string> mensajesError);

		bool terminoJuego;
		list<thread> conexionesConElServidor;
		list<ConexionCliente*> clientes;
		map<int,ConexionCliente*> clientesJugando;

};



#endif /* SRC_SERVER_SERVIDOR_HPP_ */
