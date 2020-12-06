#include <thread>

#include "ConexionCliente.hpp"
#include "EscuchadoresServer/EscuchadorCredenciales.hpp"
#include "EscuchadoresServer/EscuchadorEntradaTeclado.hpp"

#include "EnviadoresServer/EnviadorEstadoCredencial.hpp"
#include "EnviadoresServer/EnviadorRonda.hpp"
#include "EnviadoresServer/EnviadorMensajeLog.hpp"
#include "EnviadoresServer/EnviadorInfoPartida.hpp"
#include "EnviadoresServer/EnviadorCantidadConexion.hpp"

ConexionCliente::ConexionCliente(Servidor* servidor, int socket, /*todo: sacar*/int cantidadConexiones,string ip, actualizacion_cantidad_jugadores_t informacionAMandar){
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
	enviadores[RONDA] = new EnviadorRonda(socket);
	enviadores[MENSAJE_LOG] = new EnviadorMensajeLog(socket);
	enviadores[PARTIDA] = new EnviadorInfoPartida(socket);
	enviadores[ACTUALIZACION_JUGADORES] = new EnviadorCantidadConexion(socket);
	this->informacionAMandar = informacionAMandar;
}

void ConexionCliente::escuchar(){
	char tipoMensaje;
	int resultado;
	bool hayError = false;
	while(!terminoJuego && !hayError){

		resultado = recv(socket, &tipoMensaje, sizeof(char), MSG_WAITALL);

		if(resultado<0){
			Log::getInstance()->huboUnErrorSDL("Ocurrio un error escuchando el caracter identificatorio del mensaje", to_string(errno));
			hayError = true;
		}else if(resultado == 0){
			Log::getInstance()->mostrarMensajeDeInfo("Se desconecto el socket que escucha al cliente: "+ to_string(errno));
			hayError = true;
		}else{
			try{
				escuchadores[tipoMensaje]->escuchar();
			}catch(const std::exception& e){
				hayError = true;
			}
		}
	}
	terminoJuego = true;
	servidor->agregarUsuarioDesconectado(this,nombre,contrasenia,idPropio);
}

void ConexionCliente::enviar(){
	char tipoMensaje;
	bool hayError = false;
	while(!terminoJuego && !hayError){
		if(!identificadoresMensajeAEnviar.empty()){
			tipoMensaje = identificadoresMensajeAEnviar.front();
			identificadoresMensajeAEnviar.pop();
			try{
				enviadores[tipoMensaje]->enviar();
			}catch(const std::exception& e){
				hayError = true;
			}
		}
	}
	terminoJuego = true;
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
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para escuchar la informacion del cliente.");
		return; // El hilo de ejecutar muere, y queda dando vueltas solamente el objeto ConexionCliente en la lista
	}

	int resultadoCreateEnviar = pthread_create(&hiloEnviar, NULL, ConexionCliente::enviar_helper, this);
	if(resultadoCreateEnviar != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para enviar informacion del server al cliente.");
		terminoJuego = true; // Muere el hilo de este cliente y el de escuchar, queda el cliente en la lista.
		return;
	}

	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	bool esUsuarioValido = false;

	actualizarCliente(informacionAMandar);
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

void ConexionCliente::actualizarCliente(actualizacion_cantidad_jugadores_t actualizacion){
	this->cantidadConexiones = actualizacion.cantidadJugadoresActivos;
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

	shutdown(socket, SHUT_RDWR);
	close(socket);
}
