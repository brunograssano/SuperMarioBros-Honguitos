#include "ConexionCliente.hpp"

ConexionCliente::ConexionCliente(Servidor* servidor, int socket, string nombre){
	this->servidor = servidor;
	this->socket = socket;
	this->nombre = nombre;
}


int Read4Bytes(int socket,  char* buffer){
    int bytesRead = 0;
    int result;
    memset(buffer, 0, 5);
    while (bytesRead < 4){
        result = recv(socket, buffer, 4, MSG_DONTWAIT);
        if (result < 1 ){
            return bytesRead;
        }
        bytesRead += result;
    }
    return bytesRead;
}

void ConexionCliente::recibir(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	while(true){
		string mensaje;
		char buffer[5] = "";
		while(Read4Bytes(socket, buffer) > 0){
			if(!(strlen(buffer) == 0)){
				mensaje = mensaje + (string) buffer;
			}
		}
		if(mensaje.length() != 0){
			pthread_mutex_lock(&mutex);
			Log::getInstance()->mostrarMensajeDeInfo("Se escribió el mensaje: \"" + mensaje +
					"\" del cliente: " + nombre);
			pthread_mutex_unlock(&mutex);
		}
	}
}

void ConexionCliente::enviar(char* msg){}

ConexionCliente::~ConexionCliente(){
	close(socket);
}
