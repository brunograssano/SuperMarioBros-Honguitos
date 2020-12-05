#include <thread>

#include "ConexionCliente.hpp"
#include "EscuchadoresServer/EscuchadorCredenciales.hpp"
#include "EscuchadoresServer/EscuchadorEntradaTeclado.hpp"

#include "EnviadoresServer/EnviadorEstadoCredencial.hpp"
#include "EnviadoresServer/EnviadorInfoVentanaInicio.hpp"
#include "EnviadoresServer/EnviadorRonda.hpp"
#include "EnviadoresServer/EnviadorMensajeLog.hpp"
#include "EnviadoresServer/EnviadorInfoPartida.hpp"
#include "EnviadoresServer/EnviadorCantidadConexion.hpp"

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

	enviadores[VERIFICACION] = new EnviadorEstadoCredencial(socket);
	enviadores[INICIO] = new EnviadorInfoVentanaInicio(socket);
	enviadores[RONDA] = new EnviadorRonda(socket);
	enviadores[MENSAJE_LOG] = new EnviadorMensajeLog(socket);
	enviadores[PARTIDA] = new EnviadorInfoPartida(socket);
	enviadores[ACTUALIZACION_JUGADORES] = new EnviadorCantidadConexion(socket);
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

void ConexionCliente::enviar(){
	char tipoMensaje;
	bool hayError = false;
	while(!terminoJuego && !hayError){
		while(!identificadoresMensajeAEnviar.empty()){
			tipoMensaje = identificadoresMensajeAEnviar.front();
			identificadoresMensajeAEnviar.pop();
			try{
				enviadores[tipoMensaje]->enviar();
			}catch(const std::exception& e){
				hayError = true;
			}
		}
	}

}

void ConexionCliente::recibirCredencial(string nombre, string contrasenia){
	this->nombre = nombre;
	this->contrasenia = contrasenia;
	recibioCredenciales = true;
}

void ConexionCliente::esperarCredenciales(){
	while(!recibioCredenciales){
	}
	recibioCredenciales = false;
}

void ConexionCliente::enviarActualizacionesDeRonda(){
	while(!terminoJuego){
	}
}


void ConexionCliente::ejecutar(){
	pthread_t hiloEscuchar;
	pthread_t hiloEnviar;
	int resultadoCreateEscuchar = pthread_create(&hiloEscuchar, NULL, ConexionCliente::escuchar_helper, this);
	if(resultadoCreateEscuchar != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para escuchar la informacion del cliente."); //TODO: Obtener IP!!
		exit(-1); //TODO: Arreglar este exit.
	}

	int resultadoCreateEnviar = pthread_create(&hiloEnviar, NULL, ConexionCliente::enviar_helper, this);
	if(resultadoCreateEnviar != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para enviar informacion del server al cliente."); //TODO: Obtener IP!!
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


////---------------------------------ENVIADORES---------------------------------////

void ConexionCliente::enviarVerificacion(bool esUsuarioValido){
	enviadores[VERIFICACION]->dejarInformacion(&esUsuarioValido);
	identificadoresMensajeAEnviar.push(VERIFICACION);
}

info_inicio_t ConexionCliente::crearInformacionInicio(){
	info_inicio_t info;
	info.cantidadJugadoresActivos = this->cantidadConexiones;
	info.cantidadJugadores = this->servidor->getMaximasConexiones();
	return info;
}

void ConexionCliente::enviarInformacionInicio(){
	info_inicio_t info_inicio = crearInformacionInicio();
	enviadores[INICIO]->dejarInformacion(&info_inicio);
	identificadoresMensajeAEnviar.push(INICIO);
}

void ConexionCliente::recibirInformacionRonda(info_ronda_t info_ronda){
	enviadores[RONDA]->dejarInformacion(&info_ronda);
	identificadoresMensajeAEnviar.push(RONDA);
}

void ConexionCliente::enviarMensajeLog(mensaje_log_t mensaje){
	enviadores[MENSAJE_LOG]->dejarInformacion(&mensaje);
	identificadoresMensajeAEnviar.push(MENSAJE_LOG);
}

void ConexionCliente::enviarInfoPartida(info_partida_t info_partida){
	enviadores[PARTIDA]->dejarInformacion(&info_partida);
	identificadoresMensajeAEnviar.push(PARTIDA);
}

void ConexionCliente::terminoElJuego(){
	terminoJuego = true;
}

void ConexionCliente::agregarIDJuego(int IDJugador){
	escuchadores[ENTRADA] = new EscuchadorEntradaTeclado(socket,IDJugador,servidor);
	puedeJugar = true;
	idPropio = IDJugador;
}

void ConexionCliente::actualizarCantidadConexiones(int cantConexiones){
	this->cantidadConexiones = cantConexiones;
	actualizacion_cantidad_jugadores_t actualizacion;
	actualizacion.cantidadJugadoresActivos = this->cantidadConexiones;
	enviadores[ACTUALIZACION_JUGADORES]->dejarInformacion(&actualizacion);
	identificadoresMensajeAEnviar.push(ACTUALIZACION_JUGADORES);
}

////---------------------------------DESTRUCTOR---------------------------------////

ConexionCliente::~ConexionCliente(){
	for(auto const& parClaveEscuchador:escuchadores){
		delete parClaveEscuchador.second;
	}
	for(auto const& parClaveEnviador:enviadores){
		delete parClaveEnviador.second;
	}
	escuchadores.clear();
	enviadores.clear();
}
