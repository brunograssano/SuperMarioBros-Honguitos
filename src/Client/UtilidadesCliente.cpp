#include "UtilidadesCliente.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../Utils/log/Log.hpp"

void salirCliente(string mensajeLog){ // Se puede juntar con el salir del servidor --> hacer un salir generico en algun archivo de utilidades general
	cout<< "No se pudo conectar al server, terminamos la aplicacion"<<endl;
	Log::getInstance()->huboUnError(mensajeLog);
	exit(-1);
}

int conectarAlServidor(char ip[LARGO_IP], int puerto){
	struct sockaddr_in serv_addr;

	int socketCliente = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socketCliente < 0){
		salirCliente("No se pudo crear el socket: Abortamos.");
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(puerto);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0){
		salirCliente("Dirección inválida / Dirección no soportada: Abortamos.");
	}

	if (connect(socketCliente, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		salirCliente("Falló la conexión al servidor. Abortamos.-------"+to_string(errno));
	}

	return socketCliente;
}

void cerrarSocketCliente(int socketCliente) {
	int resultado = shutdown(socketCliente, SHUT_RDWR);
	if (resultado < 0) {
		Log::getInstance()->huboUnErrorSDL("Ocurrio un error haciendo el shutdown del socket",to_string(errno));
	}
	resultado = close(socketCliente);
	if (resultado < 0) {
		Log::getInstance()->huboUnErrorSDL("Ocurrio un error haciendo el close del socket",to_string(errno));
	}
}
