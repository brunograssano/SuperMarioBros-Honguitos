#include "mainServer.hpp"

using namespace std;

#include "../Client/app/AplicacionCliente.hpp"
#include "lector/Lector.hpp"

#include "../Utils/Validaciones.hpp"
#include "../Server/Servidor.hpp"

ArchivoLeido* realizarConfiguracionesIniciales(char direccionLecturaComando[LARGO_ENTRADA], char nivelLogEntrada[LARGO_ENTRADA], list<string> &mensajesErrorOtroArchivo) {
	TipoLog* nivelLog;
	auto* lector = new Lector();
	string direccionLecturaDefault = "resources/ArchivosXML/configuracionDefault.xml";
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
		if (nivelLog != nullptr) {
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
	int puerto;
	char ip[LARGO_IP] = "";
	ArchivoLeido* archivoLeido;
	list<string> mensajesErrorOtroArchivo;

	manejarEntrada(cantidadArgumentos,argumentos, direccionLecturaComando,nivelLogEntrada,ipEntrada, puertoEntrada);

	validarPuertoEIp(ipEntrada,puertoEntrada,ip, &puerto);

	archivoLeido = realizarConfiguracionesIniciales(direccionLecturaComando, nivelLogEntrada, mensajesErrorOtroArchivo);

	auto* server = new Servidor(archivoLeido, mensajesErrorOtroArchivo, puerto, ip);

	server->ejecutar();

	delete server;

	return 0;
}
