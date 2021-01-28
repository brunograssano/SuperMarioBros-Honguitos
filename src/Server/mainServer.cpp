#include "mainServer.hpp"

#include "Lector/Lector.hpp"
#include "../Utils/Validaciones.hpp"
#include "src/Server/Servidor/Servidor.hpp"
#include <string>

ArchivoLeido realizarConfiguracionesIniciales(char direccionLecturaComando[LARGO_ENTRADA], char nivelLogEntrada[LARGO_ENTRADA], std::list<std::string> &mensajesErrorOtroArchivo) {
	TipoLog* nivelLog;
    std::string direccionLecturaDefault = "resources/ArchivosXML/configuracionDefault.xml";
	ArchivoLeido archivoLeido;

	if (strcmp(direccionLecturaComando, "") != 0) {
		archivoLeido = Lector::leerArchivo(direccionLecturaComando);
		if (!archivoLeido.leidoCorrectamente) {
			mensajesErrorOtroArchivo = archivoLeido.mensajeError;
			if(!archivoLeido.usuariosValidos.empty()){
				std::list<usuario_t> usuarios;
				usuarios.swap(archivoLeido.usuariosValidos);
				int cantidadConexiones = archivoLeido.cantidadConexiones;
				archivoLeido = Lector::leerArchivo(direccionLecturaDefault);
				archivoLeido.usuariosValidos.swap(usuarios);
				archivoLeido.cantidadConexiones = cantidadConexiones;
			}else{
				archivoLeido = Lector::leerArchivo(direccionLecturaDefault);
			}
		}
	} else {
		archivoLeido = Lector::leerArchivo(direccionLecturaDefault);
	}

	if (strcmp(nivelLogEntrada, "") != 0) {
		nivelLog = determinarNivelLog(nivelLogEntrada);
		if (nivelLog != nullptr) {
			archivoLeido.tipoLog = nivelLog;
		}
	}

	return archivoLeido;
}


int mainServer( int cantidadArgumentos, char* argumentos[] ){

	char direccionLecturaComando[LARGO_ENTRADA] = "";
	char nivelLogEntrada[LARGO_ENTRADA] = "";
	char ipEntrada[LARGO_IP] = "";
	char puertoEntrada[LARGO_IP] = "";
	int puerto;
	char ip[LARGO_IP] = "";
	ArchivoLeido archivoLeido;
    std::list<std::string> mensajesErrorOtroArchivo;

	manejarEntrada(cantidadArgumentos,argumentos, direccionLecturaComando,nivelLogEntrada,ipEntrada, puertoEntrada);

	validarPuertoEIp(ipEntrada,puertoEntrada,ip, &puerto);

	archivoLeido = realizarConfiguracionesIniciales(direccionLecturaComando, nivelLogEntrada, mensajesErrorOtroArchivo);

	Servidor server(archivoLeido, mensajesErrorOtroArchivo, puerto, ip);

	server.ejecutar();

	return 0;
}
