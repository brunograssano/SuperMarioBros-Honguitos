#include "ConexionCliente.hpp"
#include "EscuchadoresServer/EscuchadorCredenciales.hpp"
#include <thread>
#include "EscuchadoresServer/EscuchadorCredenciales.hpp"
#include "EscuchadoresServer/EscuchadorEntradaTeclado.hpp"

ConexionCliente::ConexionCliente(Servidor* servidor, int socket, int cantidadConexiones,string ip){
	this->servidor = servidor;
	this->socket = socket;
	this->ip = ip;
	this->cantidadConexiones = cantidadConexiones;
	this->nombre = "";
	this->contrasenia = "";
	puedeJugar = false;
	terminoJuego = false;
	recibioCredenciales = false;
	idPropio = 0;
	escuchadores[CREDENCIAL] = new EscuchadorCredenciales(socket,this);
}

void ConexionCliente::escuchar(){
	char tipoMensaje;
	int resultado;
	bool hayError = false;
	while(!hayError){

		resultado = recv(socket, &tipoMensaje, sizeof(char), MSG_WAITALL);

		if(resultado<0){
			Log::getInstance()->huboUnErrorSDL("Ocurrio un error escuchando el caracter identificatorio del mensaje", to_string(errno));
			hayError = true;
		}else if(resultado == 0){
			Log::getInstance()->huboUnErrorSDL("Se desconecto el socket que escucha al cliente", to_string(errno));
			hayError = true;
		}else{
			try{
				escuchadores[tipoMensaje]->escuchar();
			}catch(const std::exception& e){
				hayError = true;
			}
		}
	}
	shutdown(socket, SHUT_RDWR);
	close(socket);
	servidor->agregarUsuarioDesconectado(this,nombre,contrasenia,idPropio);
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


void ConexionCliente::recibirInformacionRonda(info_ronda_t info_ronda){
	colaRondas.push(info_ronda);
}

void ConexionCliente::enviarActualizacionesDeRonda(){

	char caracterMensaje = RONDA;
	info_ronda_t ronda;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	while(!terminoJuego){
		if(!colaRondas.empty()){
			pthread_mutex_lock(&mutex);
			ronda = colaRondas.front();
			colaRondas.pop();
			send(socket, &caracterMensaje, sizeof(char), 0);
			send(socket, &ronda, sizeof(info_ronda_t), 0);
			pthread_mutex_unlock(&mutex);
		}
	}
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
		pthread_mutex_lock(&mutex);
		esUsuarioValido = servidor->esUsuarioValido({nombre,contrasenia},this);
		enviarVerificacion(esUsuarioValido);
		pthread_mutex_unlock(&mutex);
		if(esUsuarioValido){
			pthread_mutex_lock(&mutex);
			Log::getInstance()->mostrarMensajeDeInfo("Se acepto el usuario: "+nombre+" con contrasenia: "+contrasenia);
			pthread_mutex_unlock(&mutex);
		}
		else{
			esperarCredenciales();
		}
	}

	enviarActualizacionesDeRonda();
}

void ConexionCliente::enviarInfoPartida(info_partida_t info_partida){
	char caracterMensaje = MENSAJE_LOG;
	mensaje_log_t mensaje={0,0};
	mensaje.tipo = INFO;
	strcpy(mensaje.mensajeParaElLog,"Empieza el juego...");
	send(socket, &caracterMensaje, sizeof(char), 0);
	send(socket, &mensaje, sizeof(mensaje_log_t), 0);

	caracterMensaje = PARTIDA;
	send(socket, &caracterMensaje, sizeof(char), 0);
	send(socket, &info_partida, sizeof(info_partida_t), 0);
}

void ConexionCliente::terminoElJuego(){
	terminoJuego = true;
}

void ConexionCliente::agregarIDJuego(int IDJugador){
	escuchadores[ENTRADA] = new EscuchadorEntradaTeclado(socket,IDJugador,servidor);
	puedeJugar = true;
	idPropio = IDJugador;
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
	for(auto const& parClaveEscuchador:escuchadores){
		delete parClaveEscuchador.second;
	}
	escuchadores.clear();
}
