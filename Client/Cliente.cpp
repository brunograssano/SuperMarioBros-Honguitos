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
}


int Cliente::_Read4Bytes(char* buffer){
    int bytesRead = 0;
    int result;
    memset(buffer, 0, 5);
    while (bytesRead < 4){
        result = recv(socketCliente, buffer, 4, MSG_DONTWAIT);
        if (result < 1 ){
            return bytesRead;
        }
        bytesRead += result;
    }
    return bytesRead;
}

void Cliente::escucharMensaje(size_t bytes,string* buffer){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	char bufferTemporal[bytes+1]="";
	int result = recv(socketCliente, bufferTemporal, bytes, MSG_WAITALL);
	(*buffer) = bufferTemporal;

	pthread_mutex_lock(&mutex);
	Log::getInstance()->mostrarMensajeDeInfo("Se recibio el mensaje: "+ (*buffer));
	pthread_mutex_unlock(&mutex);
}


void Cliente::enviar(){
	int i = 0;
	while(i < 5){
		char msg[100 /*TODO: a cte*/] = "";
		scanf(" %[^\n]", msg);
		send(socketCliente, msg, strlen(msg), 0);
		i++;
	}
}

void Cliente::recibirInformacionServidor(int* cantConect, int* cantTot){
	recv(socketCliente, cantConect, sizeof(int), MSG_WAITALL);
	recv(socketCliente, cantTot, sizeof(int), MSG_WAITALL);
}

void Cliente::ejecutar(){

	int cantidadUsuariosConectados;
	int cantidadUsuariosMaximos;
	this->recibirInformacionServidor(&cantidadUsuariosConectados, &cantidadUsuariosMaximos);

	VentanaInicio* ventanaInicio =  new VentanaInicio();
	bool pasoVerificacion = false, cerroVentana = false;
	while(!pasoVerificacion && !cerroVentana){
		try{
			ventanaInicio->obtenerEntrada(cantidadUsuariosConectados, cantidadUsuariosMaximos);
			pasoVerificacion = enviarCredenciales(ventanaInicio->obtenerCredenciales());
			if(!pasoVerificacion){
				ventanaInicio->imprimirMensajeError();
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

	EscuchadorSalaDeEspera* escuchador = new EscuchadorSalaDeEspera(this->socketCliente);

	pthread_t hiloEscuchar;
	int resultadoCreateEscuchar = pthread_create(&hiloEscuchar, NULL, EscuchadorSalaDeEspera::escuchar_helper, escuchador);
	if(resultadoCreateEscuchar != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para escuchar la cantidad de jugadores en el servidor.");
		exit(-1); //TODO: Arreglar este exit.
	}
	while(!cerroVentana){// TODO: aca va hasta que el server arranque la partida
		try{
			ventanaInicio->imprimirMensajeEspera(escuchador->getCantidadConectados(), cantidadUsuariosMaximos);
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


bool Cliente::recibirConfirmacion(){
	bool resultado;
	int result = recv(socketCliente, &resultado, sizeof(bool), MSG_WAITALL);
	return resultado;
}

bool Cliente::enviarCredenciales(credencial_t credencial){
	const char* credencialesParsadas = (credencial.nombre + ";" +credencial.contrasenia).c_str();
	send(socketCliente, credencialesParsadas, strlen(credencialesParsadas), 0);
	return recibirConfirmacion();
}


Cliente::~Cliente(){
	close(socketCliente);
}
