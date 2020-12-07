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
	string direccionLecturaDefault = "resources/ArchivosXML/configuracionInicial.xml";
	ArchivoLeido* archivoLeido;

	if (strcmp(direccionLecturaComando, "") != 0) {
		archivoLeido = lector->leerArchivo(direccionLecturaComando);
		if (!archivoLeido->leidoCorrectamente) {
			mensajesErrorOtroArchivo = archivoLeido->mensajeError;
			if(!archivoLeido->usuariosValidos.empty()){
				list<usuario_t> usuarios;
				usuarios.swap(archivoLeido->usuariosValidos);
				int cantidadConexiones = archivoLeido->cantidadConexiones;
				delete archivoLeido;
				archivoLeido = lector->leerArchivo(direccionLecturaDefault);
				archivoLeido->usuariosValidos.swap(usuarios);
				archivoLeido->cantidadConexiones = cantidadConexiones;
			}else{
				delete archivoLeido;
				archivoLeido = lector->leerArchivo(direccionLecturaDefault);
			}
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
	int puerto = 5004;
	char ip[LARGO_IP] = "127.0.0.1";
	ArchivoLeido* archivoLeido;
	list<string> mensajesErrorOtroArchivo;

	//manejarEntrada(cantidadArgumentos,argumentos, direccionLecturaComando,nivelLogEntrada,ipEntrada, puertoEntrada);

	//validarPuertoEIp(ipEntrada,puertoEntrada,ip, &puerto);

	archivoLeido = realizarConfiguracionesIniciales("resources/ArchivosXML/configuracionInicial.xml", nivelLogEntrada, mensajesErrorOtroArchivo);

	Servidor* server = new Servidor(archivoLeido, mensajesErrorOtroArchivo, puerto, ip);

	server->ejecutar();

	delete server;

	return 0;
}
