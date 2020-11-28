#include "mainServer.hpp"

using namespace std;

#include <SDL2/SDL.h>

#include "../Client/app/AplicacionCliente.hpp"
#include "lector/Lector.hpp"

#include "../Utils/Validaciones.hpp"
#include "../Server/Servidor.hpp"

#include <getopt.h>

ArchivoLeido* realizarConfiguracionesIniciales(char direccionLecturaComando[LARGO_ENTRADA], char nivelLogEntrada[LARGO_ENTRADA], list<string> &mensajesErrorOtroArchivo) {
	TipoLog* nivelLog;
	Lector* lector = new Lector();
	string direccionLecturaDefault = "resources/ArchivosXML/configuracionDefault.xml";
	ArchivoLeido* archivoLeido;

	if (strcmp(direccionLecturaComando, "") != 0) {
		archivoLeido = lector->leerArchivo(direccionLecturaComando);
		if (!archivoLeido->leidoCorrectamente) {
			mensajesErrorOtroArchivo = archivoLeido->mensajeError;
			delete archivoLeido;
			archivoLeido = lector->leerArchivo(direccionLecturaDefault);
		}
	} else {
		archivoLeido = lector->leerArchivo(direccionLecturaDefault);
	}

	if (strcmp(nivelLogEntrada, "") != 0) {
		nivelLog = determinarNivelLog(nivelLogEntrada);
		if (nivelLog != NULL) {
			archivoLeido->tipoLog = nivelLog;
		}
	}
	delete lector;

	return archivoLeido;
}


int mainServer( int cantidadArgumentos, char* argumentos[] ){

	char direccionLecturaComando[LARGO_ENTRADA] = "";
	char nivelLogEntrada[LARGO_ENTRADA] = "";
	char ipEntrada[LARGO_IP] = "";
	char puertoEntrada[LARGO_IP] = "";
	int puerto = 0;//5004;
	char ip[LARGO_IP] = "";//"127.0.0.1";
	ArchivoLeido* archivoLeido;
	list<string> mensajesErrorOtroArchivo;

	manejarEntrada(cantidadArgumentos,argumentos, direccionLecturaComando,nivelLogEntrada,ipEntrada, puertoEntrada);

	validarPuertoEIp(ipEntrada,puertoEntrada,ip, &puerto);

	archivoLeido = realizarConfiguracionesIniciales(direccionLecturaComando, nivelLogEntrada, mensajesErrorOtroArchivo);

	Servidor* server = new Servidor(archivoLeido, mensajesErrorOtroArchivo, puerto, ip);
	pthread_t hiloJuego;

	server->iniciarJuego(&hiloJuego);

	pthread_t hilo;
	int resultadoCreate = pthread_create(&hilo, NULL, Servidor::escuchar_helper, server);
	if(resultadoCreate!= 0){
		Log::getInstance()->huboUnError("Ocurrió un error al crear el hilo para escuchar, el codigo de error es: " + to_string(resultadoCreate));
		delete server;
		return -1;
	}else{
		Log::getInstance()->mostrarMensajeDeInfo("Se creó el hilo para escuchar: (" + to_string(hilo) +").");
	}

	server->intentarIniciarModelo();

	int resultadoJoin = pthread_join(hiloJuego, NULL);
	if(resultadoJoin != 0){
		Log::getInstance()->huboUnError("Ocurrió un error al juntar los hilos main y gameLoop, el codigo de error es: " + to_string(resultadoJoin));
		pthread_cancel(hiloJuego);
		delete server;
		return -1;
	}else{
		Log::getInstance()->mostrarMensajeDeInfo("Se juntaron los hilos main y gameLoop.");
	}

	delete server;
	return 0;
}
