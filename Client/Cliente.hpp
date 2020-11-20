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

#include <queue>
#include <map>

#include "EscuchadorSalaDeEspera.hpp"

#include "Escuchadores/Escuchador.hpp"
#include "../src/app/VentanaInicio/VentanaInicio.hpp"

#include "../src/Utils.hpp"

using namespace std;

const int LARGO_IP = 20;


class Cliente{

	public:
		Cliente(char ip[LARGO_IP], int puerto);
		~Cliente();
		void escucharMensaje(size_t bytes,string* buffer);
		static void* escuchar_helper(void* ptr){
			string a="PRUEBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
			((Cliente*) ptr)->escucharMensaje(1,&a);
			return NULL;
		}

		void enviar();
		void escuchar();
		static void* enviar_helper(void* ptr){
			((Cliente*) ptr)->enviar();
			return NULL;
		}
		void recibirInformacionServidor(int* cantidadUsuariosConectados, int* cantidadUsuariosMaximos);
		void ejecutar();
		void agregarEntrada(entrada_usuario_t entradaUsuario);
	private:
		queue<entrada_usuario_t> entradasUsuario;
		map<char,Escuchador*> escuchadores;
		bool enviarCredenciales(credencial_t credencial);
		bool recibirConfirmacion();
		int _Read4Bytes(char* buffer);
		int socketCliente;
};
#endif /* CLIENT_CLIENTE_HPP_ */
