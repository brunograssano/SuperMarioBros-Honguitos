#include "Cliente.hpp"

#include "../src/log/Log.hpp"

#include <thread>

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
	escuchadores[INICIO] = new EscuchadorInformacionPartida(socketCliente, this);
	escuchadores[VERIFICACION] = new EscuchadorVerificacionCredenciales(socketCliente, this);
	escuchadores[ACTUALIZACION_JUGADORES] = new EscuchadorActualizacionJugadores(socketCliente, this);
	cantidadJugadoresActivos = 0;
	escuchadores[MENSAJE_LOG] = new EscuchadorLog(socketCliente); //TODO: CAMBIAR A DEFINE

}
void Cliente::escuchar(){
	char tipoMensaje;
	int resultado;
	while(true){
		resultado = recv(socketCliente, &tipoMensaje, sizeof(char), MSG_WAITALL);
		if(resultado<0){
			Log::getInstance()->huboUnErrorSDL("Ocurrio un error escuchando el caracter identificatorio del mensaje",to_string(errno));
			//Excepcion?
		}
		//if result = se desconecto el socket -> manejarlo
		escuchadores[tipoMensaje]->escuchar();
	}
}

void Cliente::enviar(){
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

void Cliente::recibirInformacionActualizacionCantidadJugadores(unsigned short cantidadJugadores){
	this->cantidadJugadoresActivos = cantidadJugadores;
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
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para escuchar la cantidad de jugadores en el servidor.");
		exit(-1); //TODO: Arreglar este exit.
	}

	esperarRecibirInformacionInicio();

	VentanaInicio* ventanaInicio =  new VentanaInicio();
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

	while(!cerroVentana){// TODO: aca va hasta que el server arranque la partida
		try{
			ventanaInicio->imprimirMensajeEspera(this->cantidadJugadoresActivos, this->infoInicio.cantidadJugadores);
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

	/*
	pthread_t hiloEscuchar;
	int resultadoCreateEscuchar = pthread_create(&hiloEscuchar, NULL, Cliente::escuchar_helper, this);
	if(resultadoCreateEscuchar != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para escuchar al servidor.");
		return;
	}

	pthread_t hiloEnviar;
	int resultadoCreateEnviar = pthread_create(&hiloEnviar, NULL, Cliente::enviar_helper, this);
	if(resultadoCreateEnviar != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para enviar al servidor.");
		return;
	}*/

	//gameLoop(informacion, nivelLog);// OBTENEMOS INFORMACION DEL SERVER ANTES

/*
	int resultadoJoinEnviar = pthread_join(hiloEnviar, NULL);

	if(resultadoJoinEnviar != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al enlazar el hilo \"enviar\" con el main.");
		return;
	}

	int resultadoJoinEscuchar = pthread_join(hiloEscuchar, NULL);
	if(resultadoJoinEscuchar != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al enlazar el hilo \"escuchar\" al main.");
		return;
	}*/

	delete Log::getInstance();
}
void Cliente::agregarEntrada(entrada_usuario_t entradaUsuario){
	entradasUsuario.push(entradaUsuario);
}

void Cliente::enviarCredenciales(credencial_t credencial){
	const char* credencialesParsadas = (credencial.nombre + ";" +credencial.contrasenia).c_str();
	send(socketCliente, credencialesParsadas, strlen(credencialesParsadas), 0);
	return;
}


Cliente::~Cliente(){
	close(socketCliente);

	for(auto const& parClaveEscuchador:escuchadores){
		delete parClaveEscuchador.second;
	}
	escuchadores.clear();

}
