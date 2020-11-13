#include "ConexionCliente.hpp"

ConexionCliente::ConexionCliente(Servidor* servidor, int socket, string nombre){
	this->servidor = servidor;
	this->socket = socket;
	this->nombre = nombre;
}


int ReadXBytes(int socket, unsigned int x, void* buffer){
    int bytesRead = 0;
    int result;
    while (bytesRead < x)
    {
        result = read(socket, buffer + bytesRead, x - bytesRead);
        if (result < 1 ){
//            break;
        }
        bytesRead += result;
    }
    return bytesRead;
}

void ConexionCliente::recibir(){
	while(true){
		char msg[5] = "";
		while(ReadXBytes(socket, 4, msg) > 0){
			if(!(strlen(msg) == 0)){
				Log::getInstance()->mostrarMensajeDeInfo("Se escribió el mensaje: " + (string) msg);
			}
		}
	}
}

void ConexionCliente::enviar(char* msg){}

ConexionCliente::~ConexionCliente(){
	close(socket);
}
