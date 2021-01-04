
#include "ConexionCliente.hpp"

#include <utility>
#include "EscuchadoresServer/EscuchadorCredenciales.hpp"
#include "EscuchadoresServer/EscuchadorEntradaTeclado.hpp"

#include "EnviadoresServer/EnviadorEstadoCredencial.hpp"
#include "EnviadoresServer/EnviadorRonda.hpp"
#include "EnviadoresServer/EnviadorMensajeLog.hpp"
#include "EnviadoresServer/EnviadorInfoPartida.hpp"
#include "EnviadoresServer/EnviadorCantidadConexion.hpp"

#define SIN_JUGAR -1

ConexionCliente::ConexionCliente(Servidor* servidor, int socket, /*todo: sacar*/int cantidadConexiones,string ip, actualizacion_cantidad_jugadores_t informacionAMandar){
	this->servidor = servidor;
	this->socket = socket;
	this->ip = std::move(ip);
	this->cantidadConexiones = cantidadConexiones;
	this->nombre = "";
	this->contrasenia = "";
	puedeJugar = false;
	terminoJuego = false;
	recibioCredenciales = false;
	idPropio = SIN_JUGAR;
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
			Log::getInstance()->huboUnErrorSDL("Ocurrio un error escuchando el caracter identificatorio del mensaje en el cliente: " + this->ip, to_string(errno));
			hayError = true;
		}else if(resultado == 0){
			Log::getInstance()->mostrarMensajeDeInfo("Se desconecto el socket que escucha al cliente: " +this->ip+ " ---- "+ to_string(errno));
			hayError = true;
		}else{
			try{
				escuchadores[tipoMensaje]->escuchar();
			}catch(const std::exception& e){
				hayError = true;
			}
		}
	}
	servidor->agregarUsuarioDesconectado(this,nombre,contrasenia,idPropio);
	terminoJuego = true;
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

void ConexionCliente::recibirCredencial(string posibleNombre, string posibleContrasenia){
	this->nombre = std::move(posibleNombre);
	this->contrasenia = std::move(posibleContrasenia);
	recibioCredenciales = true;
}

void ConexionCliente::esperarCredenciales(){
	while(!recibioCredenciales && !terminoJuego){
	}
	recibioCredenciales = false;
}

void ConexionCliente::enviarActualizacionesDeRonda() const{
	while(!terminoJuego){
	}
}


void ConexionCliente::ejecutar(){
	pthread_t hiloEscuchar;
	pthread_t hiloEnviar;
	int resultadoCreateEscuchar = pthread_create(&hiloEscuchar, nullptr, ConexionCliente::escuchar_helper, this);
	if(resultadoCreateEscuchar != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para escuchar la informacion del cliente: " + this->ip);
		return; // El hilo de ejecutar muere, y queda dando vueltas solamente el objeto ConexionCliente en la lista
	}

	int resultadoCreateEnviar = pthread_create(&hiloEnviar, nullptr, ConexionCliente::enviar_helper, this);
	if(resultadoCreateEnviar != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para enviar informacion del servidor al cliente: " + this->ip);
		terminoJuego = true; // Muere el hilo de este cliente y el de escuchar, queda el cliente en la lista.
		return;
	}

	bool esUsuarioValido = false;

	actualizarCliente(informacionAMandar);
	esperarCredenciales();

	while(!esUsuarioValido){
		esUsuarioValido = servidor->esUsuarioValido({nombre,contrasenia,false},this);
		enviarVerificacion(esUsuarioValido);
		if(esUsuarioValido){
			Log::getInstance()->mostrarMensajeDeInfo("Se acepto el usuario: "+nombre+" con contrasenia: "+contrasenia + " del cliente: " + this->ip);
		}
		else{
			esperarCredenciales();
		}
	}

	enviarActualizacionesDeRonda();
}


////---------------------------------ENVIADORES---------------------------------////

void ConexionCliente::enviarVerificacion(bool esUsuarioValido){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	enviadores[VERIFICACION]->dejarInformacion(&esUsuarioValido);
	pthread_mutex_lock(&mutex);
	identificadoresMensajeAEnviar.push(VERIFICACION);
	pthread_mutex_unlock(&mutex);
}

void ConexionCliente::recibirInformacionRonda(info_ronda_t info_ronda){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	enviadores[RONDA]->dejarInformacion(&info_ronda);
	pthread_mutex_lock(&mutex);
	identificadoresMensajeAEnviar.push(RONDA);
	pthread_mutex_unlock(&mutex);
}

void ConexionCliente::enviarMensajeLog(mensaje_log_t mensaje){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	enviadores[MENSAJE_LOG]->dejarInformacion(&mensaje);
	pthread_mutex_lock(&mutex);
	identificadoresMensajeAEnviar.push(MENSAJE_LOG);
	pthread_mutex_unlock(&mutex);
}

void ConexionCliente::enviarInfoPartida(info_partida_t info_partida){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	enviadores[PARTIDA]->dejarInformacion(&info_partida);
	pthread_mutex_lock(&mutex);
	identificadoresMensajeAEnviar.push(PARTIDA);
	pthread_mutex_unlock(&mutex);
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
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	enviadores[ACTUALIZACION_JUGADORES]->dejarInformacion(&actualizacion);
	pthread_mutex_lock(&mutex);
	this->cantidadConexiones = actualizacion.cantidadJugadoresActivos;
	identificadoresMensajeAEnviar.push(ACTUALIZACION_JUGADORES);
	pthread_mutex_unlock(&mutex);
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

	int resultado = shutdown(socket, SHUT_RDWR);
	if(resultado<0){
		Log::getInstance()->huboUnErrorSDL("Hubo un problema al hacer el shutdown del socket del usuario: "+nombre,to_string(errno));
	}
	resultado = close(socket);
	if(resultado<0){
		Log::getInstance()->huboUnErrorSDL("Hubo un problema al hacer el close del socket del usuario: "+nombre,to_string(errno));
	}
}
