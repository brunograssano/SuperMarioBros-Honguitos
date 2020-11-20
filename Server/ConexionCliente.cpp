#include "ConexionCliente.hpp"

ConexionCliente::ConexionCliente(Servidor* servidor, int socket, int cantidadConexiones){
	this->servidor = servidor;
	this->socket = socket;
	this->cantidadConexiones = cantidadConexiones;
	this->nombre = "";
	this->contrasenia = "";
	this->escuchadorEntradaTeclado = NULL;
	//ver a donde va el new EscuchadorEntradaTeclado(socket, id, servidor) y la llamada a escuchar;
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
			Log::getInstance()->mostrarMensajeDeInfo("Se escribió el mensaje: \"" + mensaje +"\" del cliente: " + nombre);
			pthread_mutex_unlock(&mutex);
		}
	}
}

void ConexionCliente::enviar(char* msg){}


void ConexionCliente::recibirCredenciales(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	bool tengoCredenciales = false;
	string credenciales;
	while(!tengoCredenciales){
		char buffer[5] = "";
		while(Read4Bytes(socket, buffer) > 0){
			if(!(strlen(buffer) == 0)){
				credenciales = credenciales + (string) buffer;
				tengoCredenciales = true;
			}
		}
		if(credenciales.length() != 0){
			pthread_mutex_lock(&mutex);
			Log::getInstance()->mostrarMensajeDeInfo("Se escribió el mensaje: \"" + credenciales +"\" del cliente: " + nombre);
			pthread_mutex_unlock(&mutex);
		}
	}

	string limite = ";";
	size_t posLimite = credenciales.find(limite);
	nombre = credenciales.substr(0, posLimite);
	contrasenia = credenciales.substr(posLimite+1, credenciales.length());


}

info_inicio_t ConexionCliente::crearInformacionInicio(){
	info_inicio_t info;
	info.cantidadJugadoresActivos = this->cantidadConexiones;
	info.cantidadJugadores = this->servidor->getMaximasConexiones();
	return info;
}

void ConexionCliente::enviarInformacionInicio(){
	char caracterMensaje = INICIO;
	info_inicio_t info_inicio = crearInformacionInicio();
	send(socket, &caracterMensaje, sizeof(char), 0);
	send(socket, &info_inicio, sizeof(info_inicio_t), 0);
}

void ConexionCliente::enviarVerificacion(bool esUsuarioValido){
	char caracterMensaje = VERIFICACION;
	verificacion_t verificacion = esUsuarioValido;
	send(socket, &caracterMensaje, sizeof(char), 0);
	send(socket, &verificacion , sizeof(verificacion), 0);
}

void ConexionCliente::ejecutar(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	bool esUsuarioValido = false;

	enviarInformacionInicio();

	while(!esUsuarioValido){
		recibirCredenciales();
		esUsuarioValido = servidor->esUsuarioValido({nombre,contrasenia});
		enviarVerificacion(esUsuarioValido);
		if(esUsuarioValido){
			pthread_mutex_lock(&mutex);
			Log::getInstance()->mostrarMensajeDeInfo("Se acepto el usuario: "+nombre+" con contrasenia: "+contrasenia);
			pthread_mutex_unlock(&mutex);
		}
	}

	int anterior = -1;
	while(true){
		// System pause.
	}

	//escuchar para teclas
}

void ConexionCliente::enviarActualizacionCantidadConexiones(){
	actualizacion_cantidad_jugadores_t actualizacion;
	actualizacion.cantidadJugadoresActivos = this->cantidadConexiones;
	char caracterMensaje = ACTUALIZACION_JUGADORES;
	send(socket, &caracterMensaje, sizeof(char), 0);
	send(socket, &actualizacion, sizeof(actualizacion_cantidad_jugadores_t), 0);
}

void ConexionCliente::actualizarCantidadConexiones(int cantConexiones){
	this->cantidadConexiones = cantConexiones;
	enviarActualizacionCantidadConexiones();
}

ConexionCliente::~ConexionCliente(){
	delete escuchadorEntradaTeclado;
	close(socket);
}
