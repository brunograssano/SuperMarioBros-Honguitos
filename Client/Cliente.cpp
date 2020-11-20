#include "Cliente.hpp"

#include "../src/log/Log.hpp"

#include <thread>

Cliente::Cliente(char ip[LARGO_IP], int puerto){
	struct sockaddr_in serv_addr;
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
	int res = connect(socketCliente, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (res < 0){
		Log::getInstance()->huboUnErrorSDL("Falló la conexión: Abortamos.",to_string(errno));
		exit(-1);
	}
	escuchadores[INICIO] = new EscuchadorInformacionPartida(socketCliente, this);
	escuchadores[VERIFICACION] = new EscuchadorVerificacionCredenciales(socketCliente, this);
}

void Cliente::escuchar(){
	char tipoMensaje;
	int result;
	while(true){
		result = recv(socketCliente, &tipoMensaje, sizeof(char), MSG_WAITALL);
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
	this->seRecibioInformacionInicio = true;
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
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para escuchar la cantidad de jugadores en el servidor.");
		exit(-1); //TODO: Arreglar este exit.
	}

	esperarRecibirInformacionInicio();

	VentanaInicio* ventanaInicio =  new VentanaInicio();
	bool cerroVentana = false;
	while(!pasoVerificacion && !cerroVentana){
		try{
			ventanaInicio->obtenerEntrada(infoInicio.cantidadJugadoresActivos, this->infoInicio.cantidadJugadores);
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

	cout << "todo ok" << endl;

/*	EscuchadorSalaDeEspera* escuchador = new EscuchadorSalaDeEspera(this->socketCliente);

	pthread_t hiloEscuchar1;
	int resultadoCreateEscuchar1 = pthread_create(&hiloEscuchar1, NULL, EscuchadorSalaDeEspera::escuchar_helper, escuchador);
	if(resultadoCreateEscuchar1 != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para escuchar la cantidad de jugadores en el servidor.");
		exit(-1); //TODO: Arreglar este exit.
	}
	while(!cerroVentana){// TODO: aca va hasta que el server arranque la partida
		try{
			ventanaInicio->imprimirMensajeEspera(escuchador->getCantidadConectados(), this->infoEstadoPartida.cantidadJugadoresActivos);
		}
		catch(const std::exception& e){
			cerroVentana = true;
		}
	}
	delete ventanaInicio;
	delete escuchador;
	if(cerroVentana){
		close(socketCliente);
		delete Log::getInstance();
		exit(0);
	}
*/
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

void Cliente::enviarCredenciales(credencial_t credencial){
	const char* credencialesParsadas = (credencial.nombre + ";" +credencial.contrasenia).c_str();
	send(socketCliente, credencialesParsadas, strlen(credencialesParsadas), 0);
	return;
}


Cliente::~Cliente(){
	close(socketCliente);
}
