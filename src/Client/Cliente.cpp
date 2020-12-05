#include "Cliente.hpp"

#include "../Utils/log/Log.hpp"
#include <thread>
#include "../Client/GameLoop.hpp"

#include "EnviadoresCliente/EnviadorEntrada.hpp"
#include "EnviadoresCliente/EnviadorCredenciales.hpp"

Cliente::Cliente(char ip[LARGO_IP], int puerto){
	struct sockaddr_in serv_addr;
	int resultado;

	socketCliente = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socketCliente < 0){
		Log::getInstance()->huboUnError("No se pudo crear el socket: Abortamos.");
		exit(-1);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(puerto);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0){
		Log::getInstance()->huboUnError("Dirección inválida / Dirección no soportada: Abortamos.");
		exit(-1);
	}
	resultado = connect(socketCliente, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (resultado < 0){
		Log::getInstance()->huboUnErrorSDL("Falló la conexión: Abortamos.",to_string(errno));
		exit(-1);
	}

	terminoJuego = false;
	empiezaElJuego = false;
	pasoVerificacion = false;
	seRecibioVerificacion = false;
	seRecibioInformacionInicio = false;
	cargoLaAplicacion = false;

	cantidadJugadoresActivos = 0;
	escuchadores[INICIO] = new EscuchadorInformacionPartida(socketCliente, this);
	escuchadores[VERIFICACION] = new EscuchadorVerificacionCredenciales(socketCliente, this);
	escuchadores[ACTUALIZACION_JUGADORES] = new EscuchadorActualizacionJugadores(socketCliente, this);
	escuchadores[MENSAJE_LOG] = new EscuchadorLog(socketCliente);
	escuchadores[PARTIDA] = new EscuchadorInfoPartidaInicial(socketCliente,this);
	escuchadores[RONDA] = new EscuchadorRonda(socketCliente, this);

	enviadores[CREDENCIAL] = new EnviadorCredenciales(socketCliente);
	enviadores[ENTRADA] = new EnviadorEntrada(socketCliente);

	ventanaInicio = nullptr;

}

void Cliente::escuchar(){
	char tipoMensaje;
	int resultado;
	bool hayError = false;

	while(!hayError && !terminoJuego){
		resultado = recv(socketCliente, &tipoMensaje, sizeof(char), MSG_WAITALL);

		if(resultado<0){
			Log::getInstance()->huboUnErrorSDL("Ocurrio un error escuchando el caracter identificatorio del mensaje",to_string(errno));
			hayError = true;
		}else if(resultado == 0){
			Log::getInstance()->huboUnErrorSDL("Se desconecto el socket que escucha al server", to_string(errno));
			hayError = true;
		}

		try{
			escuchadores[tipoMensaje]->escuchar();
		}catch(const std::exception& e){
			hayError = true;
		}
	}

	if(hayError){
		shutdown(socketCliente, SHUT_RDWR);
		close(socketCliente);
	}

}

void Cliente::enviar(){
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

void Cliente::empezarJuego(info_partida_t info_partida){
	empiezaElJuego = true;
	infoPartida = info_partida;
}

void Cliente::recibirVerificacionCredenciales(verificacion_t verificacion){
	this->pasoVerificacion = verificacion;
	this->seRecibioVerificacion = true;
}

void Cliente::recibirInformacionServidor(info_inicio_t info){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	this->infoInicio = info;
	this->cantidadJugadoresActivos = info.cantidadJugadoresActivos;
	this->seRecibioInformacionInicio = true;
	pthread_mutex_unlock(&mutex);
}

void Cliente::recibirInformacionActualizacion(actualizacion_cantidad_jugadores_t actualizacion){
	cantidadJugadoresActivos = actualizacion.cantidadJugadoresActivos;
	ventanaInicio->actualizarJugadores(actualizacion);
}
void Cliente::recibirInformacionRonda(info_ronda_t info_ronda){
	if(!cargoLaAplicacion){
		return;
	}
	App* aplicacion = App::getInstance();
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	aplicacion->agregarRonda(info_ronda);
	pthread_mutex_unlock(&mutex);
}

void Cliente::esperarRecibirInformacionInicio(){
	while(!seRecibioInformacionInicio){
	}//TODO: Mostrar una pantalla de espera al servidor, en caso de ser neceasrio.
}

void Cliente::esperarRecibirVerificacion(){
	while(!seRecibioVerificacion){
	}//TODO: Mostrar un mensaje de espera, en caso de ser necesario.
}

void Cliente::ejecutar(){
	pthread_t hiloEscuchar;
	int resultadoCreateEscuchar = pthread_create(&hiloEscuchar, NULL, Cliente::escuchar_helper, this);
	if(resultadoCreateEscuchar != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para escuchar la informacion del server.");
		exit(-1); //TODO: Arreglar este exit.
	}

	pthread_t hiloEnviar;
	int resultadoCreateEnviar = pthread_create(&hiloEnviar, NULL, Cliente::enviar_helper, this);
	if(resultadoCreateEnviar != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para enviar la informacion del cliente al server.");
		exit(-1); //TODO: Arreglar este exit.
	}

	esperarRecibirInformacionInicio();

	ventanaInicio =  new VentanaInicio();
	bool cerroVentana = false;
	while(!pasoVerificacion && !cerroVentana){
		try{
			ventanaInicio->obtenerEntrada(this->cantidadJugadoresActivos, this->infoInicio.cantidadJugadores);
			enviarCredenciales(ventanaInicio->obtenerCredenciales());
			esperarRecibirVerificacion();
			if(!pasoVerificacion){
				ventanaInicio->imprimirMensajeError();
				seRecibioVerificacion = false;
			}
		}
		catch(const std::exception& e){
			cerroVentana = true;
		}
	}

	if(cerroVentana){
		delete ventanaInicio;
		delete Log::getInstance();
		close(socketCliente);
		exit(0);
	}

	while(!cerroVentana && !empiezaElJuego){
		try{
			ventanaInicio->imprimirMensajeEspera(cantidadJugadoresActivos, infoInicio.cantidadJugadores);
		}
		catch(const std::exception& e){
			cerroVentana = true;
		}
	}
	delete ventanaInicio;
	if(cerroVentana){
		close(socketCliente);
		delete Log::getInstance();
		exit(0);
	}

	cargoLaAplicacion = inicializarAplicacion(infoPartida, this);
	if(!cargoLaAplicacion){
		close(socketCliente);
		delete Log::getInstance();
		exit(-1);
	}

	gameLoop();

	terminoJuego = true;
}

void Cliente::agregarEntrada(entrada_usuario_t entradaUsuario){
	enviadores[ENTRADA]->dejarInformacion(&entradaUsuario);
	identificadoresMensajeAEnviar.push(ENTRADA);
}

void Cliente::enviarCredenciales(credencial_t credenciales){
	enviadores[CREDENCIAL]->dejarInformacion(&credenciales);
	identificadoresMensajeAEnviar.push(CREDENCIAL);
}


Cliente::~Cliente(){
	if(terminoJuego){
		shutdown(socketCliente, SHUT_RDWR);
		close(socketCliente);
	}
	for(auto const& parClaveEscuchador:escuchadores){
		delete parClaveEscuchador.second;
	}
	for(auto const& parClaveEnviador:enviadores){
		delete parClaveEnviador.second;
	}
	escuchadores.clear();
	enviadores.clear();

}
