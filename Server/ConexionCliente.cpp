#include "ConexionCliente.hpp"

#include "EscuchadoresServer/EscuchadorCredenciales.hpp"
#include "EscuchadoresServer/EscuchadorEntradaTeclado.hpp"

#include <thread>

ConexionCliente::ConexionCliente(Servidor* servidor, int socket, int cantidadConexiones){
	this->servidor = servidor;
	this->socket = socket;
	this->cantidadConexiones = cantidadConexiones;
	this->nombre = "";
	this->contrasenia = "";
	this->escuchadorEntradaTeclado = NULL;

	escuchadores[CREDENCIAL] = new EscuchadorCredenciales(socket,this);

	//ver a donde va el new EscuchadorEntradaTeclado(socket, id, servidor) y la llamada a escuchar;
}

void ConexionCliente::escuchar(){
	char tipoMensaje;
	int resultado;
	while(true){
		resultado = recv(socket, &tipoMensaje, sizeof(char), MSG_WAITALL);
		if(resultado<0){
			Log::getInstance()->huboUnErrorSDL("Ocurrio un error escuchando el caracter identificatorio del mensaje", to_string(errno));
			//Excepcion?
		}
		//if result = se desconecto el socket -> manejarlo
		escuchadores[tipoMensaje]->escuchar();
	}
}


void ConexionCliente::recibirCredencial(string nombre, string contrasenia){
	this->nombre = nombre;
	this->contrasenia = contrasenia;
	recibioCredenciales = true;
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
	send(socket, &verificacion , sizeof(verificacion_t), 0);
}

void ConexionCliente::esperarCredenciales(){
	while(!recibioCredenciales){
	}
	recibioCredenciales = false;
}


void ConexionCliente::ejecutar(){
	pthread_t hiloEscuchar;
	int resultadoCreateEscuchar = pthread_create(&hiloEscuchar, NULL, ConexionCliente::escuchar_helper, this);
	if(resultadoCreateEscuchar != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para escuchar la informacion del cliente."); //TODO: Obtener IP!!
		exit(-1); //TODO: Arreglar este exit.
	}

	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	bool esUsuarioValido = false;

	enviarInformacionInicio();

	esperarCredenciales();

	while(!esUsuarioValido){
		esUsuarioValido = servidor->esUsuarioValido({nombre,contrasenia});
		enviarVerificacion(esUsuarioValido);
		if(esUsuarioValido){
			pthread_mutex_lock(&mutex);
			Log::getInstance()->mostrarMensajeDeInfo("Se acepto el usuario: "+nombre+" con contrasenia: "+contrasenia);
			pthread_mutex_unlock(&mutex);
		}
		else{
			esperarCredenciales();
		}
	}

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
